#include "InkPaper.h"
#include "Floreto/UI/UIUtils.h"
#include "Floreto/UI/NinePatchSprite.h"

using namespace cocos2d;

namespace Pyro
{

	namespace Components
	{

#define CIRCLE_FILENAME "pyro/circle.png"

		class RippleProtocol
		{
		public:
			enum
			{
				tagCircleShowAction = 340,
				tagCircleHideAction = 350,
				tagSurfaceFocused = 440,
				tagSurfaceUnfocused = 450,
			};

		public:
			RippleProtocol(Node *frame)
				: frame(frame), circle(nullptr), surface(nullptr),
				circleSrcScale(1), circleDestScale(1), remainingAnimationTime(0),
				clipped(true)
			{
			}

		public:
			void showCircle(const Vec2 &localPoint)
			{
				auto circle = this->circle;

				auto action = Spawn::create(
					Sequence::create(
					FadeTo::create(0.1f, 48),
					FadeOut::create(0.3f),
					CallFunc::create([this](void)
				{
					this->frame->unscheduleUpdate();
				}),
					nullptr),
					EaseQuadraticActionOut::create(ScaleTo::create(0.4f, this->circleDestScale)),
					MoveTo::create(0.4f, Vec2(this->frame->getContentSize().width / 2, this->frame->getContentSize().height / 2)),
					nullptr);

				action->setTag(tagCircleShowAction);

				this->remainingAnimationTime = action->getDuration();
				if (circle->getActionByTag(tagCircleShowAction) == nullptr)
					this->frame->scheduleUpdate();

				circle->stopAllActions();
				circle->setOpacity(0);
				circle->setScale(this->circleSrcScale);
				circle->setPosition(localPoint);
				circle->runAction(action);
			}

			void hideCircle(void)
			{
				auto circle = this->circle;

				auto actionShow = circle->getActionByTag(tagCircleShowAction);
				auto actionHide = circle->getActionByTag(tagCircleHideAction);

				if (actionShow || actionHide)
				{
					if (actionShow)
						this->frame->unscheduleUpdate();

					auto action = FadeOut::create(0.3f);
					action->setTag(tagCircleHideAction);

					circle->stopAllActions();
					circle->runAction(action);
				}
			}

			void showSurface(void)
			{
				if (!clipped)
					return;

				const float RECT_OPACITY = 32.f;

				auto surface = this->surface;
				auto actionFocused = surface->getActionByTag(tagSurfaceFocused);
				if (actionFocused == nullptr)
				{
					actionFocused = FadeTo::create(0.1f, RECT_OPACITY);
					actionFocused->setTag(tagSurfaceFocused);

					surface->stopActionByTag(tagSurfaceUnfocused); //if any
					surface->setOpacity(0);
					surface->runAction(actionFocused);
				}
			}

			void hideSurface(void)
			{
				if (!clipped)
					return;

				const float RECT_OPACITY = 32.f;

				auto surface = this->surface;
				auto actionUnfocused = surface->getActionByTag(tagSurfaceUnfocused);
				if (actionUnfocused == nullptr)
				{
					if (this->remainingAnimationTime > 0.1f)
						actionUnfocused = Sequence::createWithTwoActions(
						FadeTo::create(this->remainingAnimationTime - 0.1f, RECT_OPACITY),
						FadeOut::create(0.3f));
					else
						actionUnfocused = FadeOut::create(0.1f);

					actionUnfocused->setTag(tagSurfaceUnfocused);

					surface->stopActionByTag(tagSurfaceFocused); //if any
					surface->runAction(actionUnfocused);
				}
			}

		public:
			Node *frame;
			Node *circle;
			Node *surface;

			float circleSrcScale;
			float circleDestScale;
			float remainingAnimationTime;

			bool clipped;
		};

		class NormalRipple : public Node
		{
			typedef Node Super;

		public:
			static NormalRipple * create(const Size &size)
			{
				auto ripple = new NormalRipple();
				if (ripple && ripple->init(size))
				{
					ripple->autorelease();
					return ripple;
				}
				CC_SAFE_DELETE(ripple);
				return nullptr;
			}

		public:
			NormalRipple(void)
				: protocol(RippleProtocol(this))
			{
			}

			void update(float dt) override
			{
				this->protocol.remainingAnimationTime -= dt;
			}

			void setContentSize(const Size &size) override
			{
				Super::setContentSize(size);
				static_cast<Sprite *>(this->protocol.surface)->setTextureRect(Rect(0, 0, size.width, size.height));
				this->protocol.surface->setPosition(size.width / 2, size.height / 2);

				auto circleSize = protocol.circle->getContentSize().width;
				auto smallerDim = std::min(size.width, size.height);
				protocol.circleSrcScale = smallerDim * 0.5f / circleSize;
				protocol.circleDestScale = sqrtf(size.width * size.width + size.height * size.height) / protocol.circle->getContentSize().width;
			}

		protected:
			bool init(const Size &size)
			{
				if (!Super::init())
					return false;

				auto &protocol = this->protocol;

				auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(CIRCLE_FILENAME);
				if (!spriteFrame)
				{
					auto texture = Director::getInstance()->getTextureCache()->addImage(CIRCLE_FILENAME);
					spriteFrame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
					SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, CIRCLE_FILENAME);
				}
				protocol.circle = Sprite::createWithSpriteFrame(spriteFrame);
				protocol.circle->setOpacity(0);
				this->addChild(protocol.circle, 1);

				auto circleSize = protocol.circle->getContentSize().width;
				auto smallerDim = std::min(size.width, size.height);
				protocol.circleSrcScale = smallerDim * 0.5f / circleSize;
				protocol.circleDestScale = sqrtf(size.width * size.width + size.height * size.height) / protocol.circle->getContentSize().width;

				protocol.surface = Floreto::UIUtils::createRectangle(size.width, size.height, Color3B::WHITE);
				protocol.surface->setOpacity(0);
				protocol.surface->setPosition(size.width / 2, size.height / 2);
				this->addChild(protocol.surface, 0);

				protocol.remainingAnimationTime = 0;

				this->setContentSize(size);
				this->ignoreAnchorPointForPosition(false);
				this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

				return true;
			}

		public:
			RippleProtocol protocol;
		};

		class RoundedRipple : public Node
		{
			typedef Node Super;

		public:
			static RoundedRipple * create(const Size &size)
			{
				auto ripple = new RoundedRipple();
				if (ripple && ripple->init(size))
				{
					ripple->autorelease();
					return ripple;
				}
				CC_SAFE_DELETE(ripple);
				return nullptr;
			}

		public:
			RoundedRipple(void)
				: protocol(RippleProtocol(this))
			{
			}

			void update(float dt) override
			{
				this->protocol.remainingAnimationTime -= dt;
			}

			void setContentSize(const Size &size) override
			{
				Super::setContentSize(size);
				this->protocol.surface->setContentSize(size);
				this->protocol.surface->setPosition(size.width / 2, size.height / 2);

				auto circleSize = protocol.circle->getContentSize().width;
				auto smallerDim = std::min(size.width, size.height);
				protocol.circleSrcScale = smallerDim * 0.5f / circleSize;
				protocol.circleDestScale = sqrtf(size.width * size.width + size.height * size.height) / protocol.circle->getContentSize().width;
			}

		protected:
			bool init(const Size &size)
			{
				if (!Super::init())
					return false;

				auto &protocol = this->protocol;

				auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(CIRCLE_FILENAME);
				if (!spriteFrame)
				{
					auto texture = Director::getInstance()->getTextureCache()->addImage(CIRCLE_FILENAME);
					spriteFrame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
					SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, CIRCLE_FILENAME);
				}
				protocol.circle = Sprite::createWithSpriteFrame(spriteFrame);
				protocol.circle->setOpacity(0);
				this->addChild(protocol.circle, 1);

				auto circleSize = protocol.circle->getContentSize().width;
				auto smallerDim = std::min(size.width, size.height);
				protocol.circleSrcScale = smallerDim * 0.5f / circleSize;
				protocol.circleDestScale = sqrtf(size.width * size.width + size.height * size.height) / protocol.circle->getContentSize().width;

				Rect insets;
				spriteFrame = Paper::getRoundedNinePatchFrame(insets);

				protocol.surface = Floreto::NinePatchSprite::createWithSpriteFrame(spriteFrame, insets);

				protocol.surface->setOpacity(0);
				protocol.surface->setPosition(size.width / 2, size.height / 2);
				this->addChild(protocol.surface, 0);

				protocol.remainingAnimationTime = 0;

				this->setContentSize(size);
				this->ignoreAnchorPointForPosition(false);
				this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

				return true;
			}

		public:
			RippleProtocol protocol;
		};

		InkPaper * InkPaper::create(const Size &size, bool roundedCorner, const Color3B &color)
		{
			auto paper = new InkPaper();
			if (paper && paper->init(size, roundedCorner, color))
			{
				paper->autorelease();
				return paper;
			}
			CC_SAFE_DELETE(paper);
			return nullptr;
		}

		InkPaper::InkPaper(void)
			: touchCircle(nullptr), touchSurface(nullptr), rippleFrame(nullptr)
		{
		}

		InkPaper::~InkPaper(void)
		{
		}

		void InkPaper::setContentSize(const Size &size)
		{
			Super::setContentSize(size);
			if (this->rippleFrame)
			{
				this->rippleFrame->setContentSize(size);
				this->rippleFrame->setPosition(size.width / 2, size.height / 2);
			}
		}

		bool InkPaper::init(const Size &size, bool roundedCorner, const Color3B &color)
		{
			if (!Super::init(size, roundedCorner, color))
				return false;

			if (roundedCorner)
			{
				auto ripple = RoundedRipple::create(size);
				this->touchCircle = ripple->protocol.circle;
				this->touchSurface = ripple->protocol.surface;
				this->rippleFrame = ripple;
			}
			else
			{
				auto ripple = NormalRipple::create(size);
				this->touchCircle = ripple->protocol.circle;
				this->touchSurface = ripple->protocol.surface;
				this->rippleFrame = ripple;
			}

			this->rippleFrame->setPosition(size.width / 2, size.height / 2);
			this->getContainer()->addChild(this->rippleFrame, 100);
			this->rippleClipped = true;

			return true;
		}

		void InkPaper::showTouchRipple(const Vec2 &localPosition)
		{
			if (this->roundedCorner)
			{
				static_cast<RoundedRipple *>(this->rippleFrame)->protocol.showCircle(localPosition);
				static_cast<RoundedRipple *>(this->rippleFrame)->protocol.showSurface();
			}
			else
			{
				static_cast<NormalRipple *>(this->rippleFrame)->protocol.showCircle(localPosition);
				static_cast<NormalRipple *>(this->rippleFrame)->protocol.showSurface();
			}
		}

		void InkPaper::hideTouchRipple(bool keepCircle)
		{
			if (this->roundedCorner)
			{
				if (!keepCircle)
					static_cast<RoundedRipple *>(this->rippleFrame)->protocol.hideCircle();
				static_cast<RoundedRipple *>(this->rippleFrame)->protocol.hideSurface();
			}
			else
			{
				if (!keepCircle)
					static_cast<NormalRipple *>(this->rippleFrame)->protocol.hideCircle();
				static_cast<NormalRipple *>(this->rippleFrame)->protocol.hideSurface();
			}
		}

		float InkPaper::getRippleRemainingTime(void) const
		{
			if (this->roundedCorner)
				return static_cast<RoundedRipple *>(this->rippleFrame)->protocol.remainingAnimationTime;
			else
				return static_cast<NormalRipple *>(this->rippleFrame)->protocol.remainingAnimationTime;
		}

		void InkPaper::setRippleClipped(bool clipped)
		{
			if (clipped == this->rippleClipped)
				return;

			this->rippleClipped = clipped;
			if (clipped)
			{
				this->rippleFrame->retain();
				this->rippleFrame->getParent()->removeChild(this->rippleFrame, false);
				this->getContainer()->addChild(this->rippleFrame, 100);
				this->rippleFrame->release();
			}
			else
			{
				this->rippleFrame->retain();
				this->rippleFrame->getParent()->removeChild(this->rippleFrame, false);
				this->getContainer()->getParent()->addChild(this->rippleFrame, this->getContainer()->getLocalZOrder() + 1);
				this->rippleFrame->release();
			}

			if (this->roundedCorner)
				static_cast<RoundedRipple *>(this->rippleFrame)->protocol.clipped = clipped;
			else
				static_cast<NormalRipple *>(this->rippleFrame)->protocol.clipped = clipped;
		}

	} //namespace Pyro::Components

} //namespace Pyro
