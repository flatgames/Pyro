#include "RoundedRectangle.h"
#include "../Paper.h"
#include "Floreto/UI/NinePatchSprite.h"

namespace Pyro
{

	namespace Components
	{

		namespace Helpers
		{

			RoundedRectangle * RoundedRectangle::create(const cocos2d::Size &size)
			{
				auto ripple = new RoundedRectangle();
				if (ripple && ripple->init(size))
				{
					ripple->autorelease();
					return ripple;
				}
				CC_SAFE_DELETE(ripple);
				return nullptr;
			}

			RoundedRectangle::RoundedRectangle(void)
			{
			}

			void RoundedRectangle::setContentSize(const cocos2d::Size &size)
			{
				Super::setContentSize(size);
				if (this->usingNinePatch)
				{
					this->getStencil()->setContentSize(size);
					this->getStencil()->setPosition(size.width / 2, size.height / 2);
				}
				else
				{
					this->createDrawNode(true);
				}
			}

			bool RoundedRectangle::init(const cocos2d::Size &size)
			{
				if (!Super::init())
					return false;

				{
					ClippingNode::setContentSize(size);
					this->usingNinePatch = false;
					this->setUsingNinePatch(true);
				}

				this->setContentSize(size);
				this->ignoreAnchorPointForPosition(false);
				this->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);

				return true;
			}

			void RoundedRectangle::createDrawNode(bool reuse)
			{
				auto drawNode = reuse
					? static_cast<cocos2d::DrawNode *>(this->getStencil())
					: cocos2d::DrawNode::create();

				if (reuse)
				{
					drawNode->clear();
				}
				else
				{
					this->setStencil(drawNode);
					drawNode->setContentSize(this->getContentSize());
					drawNode->setAnchorPoint(cocos2d::Vec2::ZERO);
				}

				auto radius = Paper::getRoundedCornerRadius();
				auto size = this->getContentSize();

				cocos2d::Vec2 vertices[8];
				vertices[0].set(0, size.height - radius);
				vertices[1].set(radius, size.height);
				vertices[2].set(size.width - radius, size.height);
				vertices[3].set(size.width, size.height - radius);
				vertices[4].set(size.width, radius);
				vertices[5].set(size.width - radius, 0);
				vertices[6].set(radius, 0);
				vertices[7].set(0, radius);
				drawNode->drawPolygon(vertices, 8, cocos2d::Color4F::WHITE, 0, cocos2d::Color4F::WHITE);

				//top left
				drawNode->drawCubicBezier(
					vertices[0],
					cocos2d::Vec2(vertices[0].x, vertices[0].y + radius * 0.5f),
					cocos2d::Vec2(vertices[1].x - radius * 0.5f, vertices[1].y),
					vertices[1],
					3,
					cocos2d::Color4F::WHITE);

				//top right
				drawNode->drawCubicBezier(
					vertices[2],
					cocos2d::Vec2(vertices[2].x + radius * 0.5f, vertices[2].y),
					cocos2d::Vec2(vertices[3].x, vertices[3].y + radius * 0.5f),
					vertices[3],
					3,
					cocos2d::Color4F::WHITE);

				//bottom right
				drawNode->drawCubicBezier(
					vertices[4],
					cocos2d::Vec2(vertices[4].x, vertices[4].y - radius * 0.5f),
					cocos2d::Vec2(vertices[5].x + radius * 0.5f, vertices[5].y),
					vertices[5],
					3,
					cocos2d::Color4F::WHITE);

				//bottom left
				drawNode->drawCubicBezier(
					vertices[5],
					cocos2d::Vec2(vertices[5].x - radius * 0.5f, vertices[3].y),
					cocos2d::Vec2(vertices[6].x, vertices[6].y - radius * 0.5f),
					vertices[6],
					3,
					cocos2d::Color4F::WHITE);
			}

			bool RoundedRectangle::isUsingNinePatch(void) const
			{
				return this->usingNinePatch;
			}

			void RoundedRectangle::setUsingNinePatch(bool value)
			{
				if (this->usingNinePatch == value)
					return;

				this->usingNinePatch = value;
				if (this->usingNinePatch)
				{
					cocos2d::Rect insets;
					auto spriteFrame = Paper::getRoundedNinePatchFrame(insets);

					auto stencil = Floreto::NinePatchSprite::createWithSpriteFrame(spriteFrame, insets);
					this->setStencil(stencil);
					this->setAlphaThreshold(0.2f);
				}
				else
				{
					this->createDrawNode(false);
				}
			}

		} //namespace Helpers

	} //namespace Components

} //namespace Pyro
