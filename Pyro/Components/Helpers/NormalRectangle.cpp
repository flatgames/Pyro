#include "NormalRectangle.h"

namespace Pyro
{

	namespace Components
	{

		namespace Helpers
		{

			NormalRectangle * NormalRectangle::create(const cocos2d::Size &size)
			{
				auto ripple = new NormalRectangle();
				if (ripple && ripple->init(size))
				{
					ripple->autorelease();
					return ripple;
				}
				CC_SAFE_DELETE(ripple);
				return nullptr;
			}

			NormalRectangle::NormalRectangle(void)
			{
			}

			void NormalRectangle::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags)
			{
				if (this->_transformDirty || (parentFlags & FLAGS_DIRTY_MASK))
				{
					viewScaleX = 1;
					viewScaleY = 1;
					for (Node *node = this; node; node = node->getParent())
					{
						viewScaleX *= node->getScaleX();
						viewScaleY *= node->getScaleY();
					}
				}

				beforeVisitCmdScissor.init(_globalZOrder);
				beforeVisitCmdScissor.func = [this]()
				{
					cocos2d::Vec2 org = this->convertToWorldSpace(cocos2d::Vec2::ZERO);
					cocos2d::Size siz = this->getContentSize();

					glEnable(GL_SCISSOR_TEST);
					auto glview = cocos2d::Director::getInstance()->getOpenGLView();
					glview->setScissorInPoints(org.x, org.y, siz.width * this->viewScaleX, siz.height * this->viewScaleY);
				};
				renderer->addCommand(&beforeVisitCmdScissor);

				cocos2d::Node::visit(renderer, parentTransform, parentFlags);

				afterVisitCmdScissor.init(_globalZOrder);
				afterVisitCmdScissor.func = []()
				{
					glDisable(GL_SCISSOR_TEST);
				};
				renderer->addCommand(&afterVisitCmdScissor);
			}

			bool NormalRectangle::init(const cocos2d::Size &size)
			{
				if (!Super::init())
					return false;

				this->setContentSize(size);
				this->ignoreAnchorPointForPosition(false);
				this->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);

				this->viewScaleX = 1;
				this->viewScaleY = 1;

				return true;
			}

		} //namespace Helpers

	} //namespace Components

} //namespace Pyro
