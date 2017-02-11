#include "ShadowLayer.h"
#include "ShadowConfig.h"

using namespace cocos2d;

namespace Pyro
{

	namespace Shadow
	{

		class ShadowLayer::PseudoNode
		{
		public:
			static PseudoNode * create(Node *actualParent, SpriteFrame *spriteFrame, const Rect &insets, float orgBlurRadius)
			{
				auto node = new PseudoNode();
				node->init(actualParent, spriteFrame, insets, orgBlurRadius);
				return node;
			}

		public:
			PseudoNode(void)
				: actualParent(nullptr), animating(false),
				anchorPoint(Vec2::ANCHOR_MIDDLE), position(Vec2::ZERO), scale(Vec2::ONE), contentSize(Vec2::ZERO),
				topLeft(nullptr), topCenter(nullptr), topRight(nullptr),
				middleLeft(nullptr), middleCenter(nullptr), middleRight(nullptr),
				bottomLeft(nullptr), bottomCenter(nullptr), bottomRight(nullptr),
				orgBlurRadius(0), currentBlurRadius(0)
			{
			}

		public:
			void animate(float duration, const Vec2 &toPosition, GLubyte toOpacity, float toBlurRadius)
			{
				this->animating = true;
				this->animationDuration = duration;
				this->animationAcct = 0;

				this->orgPosition = this->position;
				this->positionSpan = toPosition - this->orgPosition;

				this->orgOpacity = this->opacity;
				this->opacitySpan = toOpacity - this->orgOpacity;

				this->orgAnimBlurRadius = this->currentBlurRadius;
				this->blueRadiusSpan = toBlurRadius - this->orgAnimBlurRadius;
			}

			void stopAnimation(void)
			{
				this->animating = false;
			}

			bool update(float dt)
			{
				if (!this->animating)
					return false;

				this->animationAcct += dt;
				if (this->animationAcct >= this->animationDuration)
					this->animating = false;

				float ratio = this->animationAcct / this->animationDuration;
				if (ratio < 0)
					ratio = 0;
				else if (ratio > 1)
					ratio = 1;

				Vec2 p = this->positionSpan * ratio;
				this->setPosition(this->orgPosition + p);

				int o = this->opacitySpan * ratio;
				o = this->orgOpacity + o;
				if (o < 0)
					o = 0;
				else if (o > 255)
					o = 255;
				this->setOpacity((GLubyte)o);

				float r = this->blueRadiusSpan * ratio;
				this->setBlurRadius(this->orgAnimBlurRadius + r);

				return this->animating;
			}

		public:
			const Vec2 & getAnchorPoint(void) const
			{
				return this->anchorPoint;
			}

			void setAnchorPoint(const Vec2 &p)
			{
				this->anchorPoint = p;
				this->setContentSize(this->formalSize);
			}

			const Vec2 & getPosition(void) const
			{
				return this->position;
			}

			void setPosition(const Vec2 &p)
			{
				this->position = p;
				this->setContentSize(this->formalSize);
			}

			void setPosition(float x, float y)
			{
				this->position.setPoint(x, y);
				this->setContentSize(this->formalSize);
			}

			void setPositionX(float x)
			{
				this->position.x = x;
				this->setContentSize(this->formalSize);
			}

			void setPositionY(float y)
			{
				this->position.y = y;
				this->setContentSize(this->formalSize);
			}

			float getScale(void) const
			{
				return this->scale.x;
			}

			void setScale(float scale)
			{
				this->scale.setPoint(scale, scale);
				this->setContentSize(this->formalSize);
			}

			void setScaleX(float scaleX)
			{
				this->scale.x = scaleX;
				this->setContentSize(this->formalSize);
			}

			void setScaleY(float scaleY)
			{
				this->scale.y = scaleY;
				this->setContentSize(this->formalSize);
			}

			const Size & getContentSize(void) const
			{
				return this->contentSize;
			}

			void setContentSize(const cocos2d::Size &size)
			{
				float width = size.width - this->currentBlurRadius;
				float height = size.height - this->currentBlurRadius;
				if (width <= 0)
					width = 1;
				if (height <= 0)
					height = 1;

				this->contentSize.setSize(width, height);
				this->formalSize = size;

				float xScale = width / insets.size.width;
				float yScale = height / insets.size.height;

				this->setChildPosition(topLeft, 0, height);
				this->setChildPosition(topCenter, width / 2, height);
				this->setChildScaleX(topCenter, xScale);
				this->setChildPosition(topRight, width, height);

				this->setChildPosition(middleLeft, 0, height / 2);
				this->setChildScaleY(middleLeft, yScale);
				this->setChildPosition(middleCenter, width / 2, height / 2);
				this->setChildScale(middleCenter, xScale, yScale);
				this->setChildPosition(middleRight, width, height / 2);
				this->setChildScaleY(middleRight, yScale);

				this->setChildPosition(bottomLeft, 0, 0);
				this->setChildPosition(bottomCenter, width / 2, 0);
				this->setChildScaleX(bottomCenter, xScale);
				this->setChildPosition(bottomRight, width, 0);
			}

			GLubyte getOpacity(void) const
			{
				return this->opacity;
			}

			void setOpacity(GLubyte opacity)
			{
				this->opacity = opacity;

				this->topLeft->setOpacity(opacity);
				this->topCenter->setOpacity(opacity);
				this->topRight->setOpacity(opacity);
				this->middleLeft->setOpacity(opacity);
				this->middleCenter->setOpacity(opacity);
				this->middleRight->setOpacity(opacity);
				this->bottomLeft->setOpacity(opacity);
				this->bottomCenter->setOpacity(opacity);
				this->bottomRight->setOpacity(opacity);
			}

		public:
			float getBlurRadius(void) const
			{
				return this->currentBlurRadius;
			}

			void setBlurRadius(float blurRadius)
			{
				if (blurRadius != this->currentBlurRadius)
				{
					this->currentBlurRadius = blurRadius;

					float ratio = blurRadius / this->orgBlurRadius;

					this->setChildScale(topLeft, ratio, ratio);
					this->setChildScaleY(topCenter, ratio);
					this->setChildScale(topRight, ratio, ratio);

					this->setChildScaleX(middleLeft, ratio);
					this->setChildScaleX(middleRight, ratio);

					this->setChildScale(bottomLeft, ratio, ratio);
					this->setChildScaleY(bottomCenter, ratio);
					this->setChildScale(bottomRight, ratio, ratio);

					this->setContentSize(this->formalSize);
				}
			}

		public:
			bool init(Node *actualParent, SpriteFrame *spriteFrame, const Rect &insets, float orgBlurRadius)
			{
				CCASSERT(spriteFrame != nullptr, "ArgumentNullException");

				this->actualParent = actualParent;

				auto texture = spriteFrame->getTexture();
				auto rect = spriteFrame->getRect();

				float leftPadding = insets.origin.x,
					rightPadding = rect.size.width - insets.size.width - insets.origin.x,
					topPadding = rect.size.height - insets.size.height - insets.origin.y,
					bottomPadding = insets.origin.y;

				Rect frameRect;

				// top left
				frameRect.origin.setPoint(rect.origin.x, rect.origin.y);
				frameRect.size.setSize(leftPadding, topPadding);
				this->topLeft = Sprite::createWithTexture(texture, frameRect);
				this->topLeft->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);

				// top center
				frameRect.origin.setPoint(rect.origin.x + leftPadding, rect.origin.y);
				frameRect.size.setSize(insets.size.width, topPadding);
				this->topCenter = Sprite::createWithTexture(texture, frameRect);
				this->topCenter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

				// top right
				frameRect.origin.setPoint(rect.origin.x + leftPadding + insets.size.width, rect.origin.y);
				frameRect.size.setSize(rightPadding, topPadding);
				this->topRight = Sprite::createWithTexture(texture, frameRect);
				this->topRight->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

				// middle left
				frameRect.origin.setPoint(rect.origin.x, rect.origin.y + topPadding);
				frameRect.size.setSize(leftPadding, insets.size.height);
				this->middleLeft = Sprite::createWithTexture(texture, frameRect);
				this->middleLeft->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);

				// middle center
				frameRect.origin.setPoint(rect.origin.x + leftPadding, rect.origin.y + topPadding);
				frameRect.size.setSize(insets.size.width, insets.size.height);
				this->middleCenter = Sprite::createWithTexture(texture, frameRect);
				this->middleCenter->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

				// middle right
				frameRect.origin.setPoint(rect.origin.x + leftPadding + insets.size.width, rect.origin.y + topPadding);
				frameRect.size.setSize(rightPadding, insets.size.height);
				this->middleRight = Sprite::createWithTexture(texture, frameRect);
				this->middleRight->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

				// bottom left
				frameRect.origin.setPoint(rect.origin.x, rect.origin.y + topPadding + insets.size.height);
				frameRect.size.setSize(leftPadding, bottomPadding);
				this->bottomLeft = Sprite::createWithTexture(texture, frameRect);
				this->bottomLeft->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);

				// bottom center
				frameRect.origin.setPoint(rect.origin.x + leftPadding, rect.origin.y + topPadding + insets.size.height);
				frameRect.size.setSize(insets.size.width, bottomPadding);
				this->bottomCenter = Sprite::createWithTexture(texture, frameRect);
				this->bottomCenter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

				// bottom right
				frameRect.origin.setPoint(rect.origin.x + leftPadding + insets.size.width, rect.origin.y + topPadding + insets.size.height);
				frameRect.size.setSize(rightPadding, bottomPadding);
				this->bottomRight = Sprite::createWithTexture(texture, frameRect);
				this->bottomRight->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

				this->insets = insets;
				this->orgBlurRadius = orgBlurRadius;
				this->currentBlurRadius = orgBlurRadius;

				this->leftPadding = leftPadding;
				this->rightPadding = rightPadding;
				this->topPadding = topPadding;
				this->bottomPadding = bottomPadding;

				this->addChild(topLeft);
				this->addChild(topCenter);
				this->addChild(topRight);
				this->addChild(middleLeft);
				this->addChild(middleCenter);
				this->addChild(middleRight);
				this->addChild(bottomLeft);
				this->addChild(bottomCenter);
				this->addChild(bottomRight);

				this->setContentSize(rect.size);

				return true;
			}

		private:
			void addChild(Node *child)
			{
				this->actualParent->addChild(child);
			}

			void setChildPosition(Node *child, float x, float y)
			{
				child->setPosition(
					this->position.x + (x - this->contentSize.width * this->anchorPoint.x) * this->scale.x,
					this->position.y + (y - this->contentSize.height * this->anchorPoint.y) * this->scale.y);
			}

			void setChildScale(Node *child, float scaleX, float scaleY)
			{
				child->setScale(scaleX * this->scale.x, scaleY * this->scale.y);
			}

			void setChildScaleX(Node *child, float scaleX)
			{
				child->setScaleX(scaleX * this->scale.x);
			}

			void setChildScaleY(Node *child, float scaleY)
			{
				child->setScaleY(scaleY * this->scale.y);
			}

		private:
			Node *actualParent;
			bool animating;
			float animationDuration;
			float animationAcct;

			Vec2 orgPosition;
			Vec2 positionSpan;

			GLubyte orgOpacity;
			int opacitySpan;

			float orgAnimBlurRadius;
			float blueRadiusSpan;

		private:
			Vec2 anchorPoint;
			Vec2 position;
			Vec2 scale;
			Size contentSize;
			GLubyte opacity;

		private:
			cocos2d::Rect insets;
			float leftPadding, rightPadding, topPadding, bottomPadding;

			cocos2d::Sprite *topLeft;
			cocos2d::Sprite *topCenter;
			cocos2d::Sprite *topRight;
			cocos2d::Sprite *middleLeft;
			cocos2d::Sprite *middleCenter;
			cocos2d::Sprite *middleRight;
			cocos2d::Sprite *bottomLeft;
			cocos2d::Sprite *bottomCenter;
			cocos2d::Sprite *bottomRight;

			float orgBlurRadius;
			float currentBlurRadius;
			cocos2d::Size formalSize;
		};

#define SHADOW_FILENAME "pyro/shadow.9.png"
#define SHADOW_ORG_BLUR_RADIUS 4
#define SHADOW_SPRITE_INSETS Rect(8, 8, 8, 8)

#define OPACITY_PERCENT(__p__) (255 * __p__ / 100)

#define TOPSHADOW_BLURRADIUS 4, 6, 11, 16, 20
#define TOPSHADOW_OFFSETY 2, 5, 8, 10, 18
#define TOPSHADOW_OPACITY 15, 16, 18, 24, 32

#define BOTTOMSHADOW_BLURADIUS 3, 8, 12, 12, 19
#define BOTTOMSHADOW_OFFSETY 2, 5, 9, 12, 15
#define BOTTOMSHADOW_OPACITY 20, 22, 24, 25, 30

		const int ShadowLayer::MAX_SHADOW_CONFIG = 5;

		bool ShadowLayer::configReady = false;

		ShadowConfig ShadowLayer::topShadowConfigs[ShadowLayer::MAX_SHADOW_CONFIG];

		ShadowConfig ShadowLayer::bottomShadowConfigs[ShadowLayer::MAX_SHADOW_CONFIG];

		ShadowLayer * ShadowLayer::create(const Size &size, int depth)
		{
			auto layer = new ShadowLayer();
			if (layer && layer->init(size, depth))
			{
				layer->autorelease();
				return layer;
			}
			CC_SAFE_DELETE(layer);
			return nullptr;
		}

		void ShadowLayer::initConfigs(void)
		{
			float designWidth = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
			float ratio = 1;
			if (designWidth <= 720)
				ratio = 0.75f;
			else if (designWidth <= 960)
				ratio = 1;
			else
				ratio = 1.5f;

			{
				auto &configs = ShadowLayer::topShadowConfigs;

				float blurRadius[ShadowLayer::MAX_SHADOW_CONFIG] = { TOPSHADOW_BLURRADIUS };
				float offsetY[ShadowLayer::MAX_SHADOW_CONFIG] = { TOPSHADOW_OFFSETY };
				GLubyte opacity[ShadowLayer::MAX_SHADOW_CONFIG] = { TOPSHADOW_OPACITY };

				for (int i = 0; i < ShadowLayer::MAX_SHADOW_CONFIG; ++i)
				{
					auto config = ShadowConfig(i + 1, blurRadius[i] * ratio, offsetY[i] * ratio, OPACITY_PERCENT(opacity[i]));
					configs[i] = config;
				}
			}

			{
				auto &configs = ShadowLayer::bottomShadowConfigs;

				float blurRadius[ShadowLayer::MAX_SHADOW_CONFIG] = { BOTTOMSHADOW_BLURADIUS };
				float offsetY[ShadowLayer::MAX_SHADOW_CONFIG] = { BOTTOMSHADOW_OFFSETY };
				GLubyte opacity[ShadowLayer::MAX_SHADOW_CONFIG] = { BOTTOMSHADOW_OPACITY };

				for (int i = 0; i < ShadowLayer::MAX_SHADOW_CONFIG; ++i)
				{
					auto config = ShadowConfig(i + 1, blurRadius[i] * ratio, offsetY[i] * ratio, OPACITY_PERCENT(opacity[i]));
					configs[i] = config;
				}
			}

			ShadowLayer::configReady = true;
		}

		ShadowLayer::ShadowLayer(void)
			: currentDepth(0), topShadow(nullptr), bottomShadow(nullptr), animating(false)
		{
		}

		ShadowLayer::~ShadowLayer(void)
		{
		}

		void ShadowLayer::onExit(void)
		{
			this->unscheduleUpdate();
			Super::onExit();
		}

		void ShadowLayer::update(float dt)
		{
			bool animating = this->topShadow->update(dt);
			animating = this->bottomShadow->update(dt) || animating;

			if (!animating)
			{
				this->animating = false;
				this->unscheduleUpdate();
			}
		}

		void ShadowLayer::setContentSize(const Size &size)
		{
			Super::setContentSize(size);
			this->topShadow->setContentSize(size);
			this->bottomShadow->setContentSize(size);

			const auto &topConfig = ShadowLayer::topShadowConfigs[this->currentDepth - 1];
			const auto &bottomConfig = ShadowLayer::bottomShadowConfigs[this->currentDepth - 1];

			this->topShadow->setPosition(size.width / 2, size.height / 2 - topConfig.OffsetY);
			this->bottomShadow->setPosition(size.width / 2, size.height / 2 - bottomConfig.OffsetY);
		}

		bool ShadowLayer::init(const Size &size, int depth)
		{
			if (!ShadowLayer::configReady)
				ShadowLayer::initConfigs();

			Texture2D *texture;

			auto shadowSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(SHADOW_FILENAME);
			if (!shadowSpriteFrame)
			{
				texture = Director::getInstance()->getTextureCache()->addImage(SHADOW_FILENAME);
				auto rect = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
				shadowSpriteFrame = SpriteFrame::createWithTexture(texture, rect);
				SpriteFrameCache::getInstance()->addSpriteFrame(shadowSpriteFrame, SHADOW_FILENAME);
			}
			else
			{
				texture = shadowSpriteFrame->getTexture();
			}

			if (!Super::initWithTexture(texture, 18))
				return false;

			auto topShadow = PseudoNode::create(this, shadowSpriteFrame, SHADOW_SPRITE_INSETS, SHADOW_ORG_BLUR_RADIUS);
			topShadow->setContentSize(size);
			topShadow->setPosition(size.width / 2, size.height / 2);

			auto bottomShadow = PseudoNode::create(this, shadowSpriteFrame, SHADOW_SPRITE_INSETS, SHADOW_ORG_BLUR_RADIUS);
			bottomShadow->setContentSize(size);
			bottomShadow->setPosition(size.width / 2, size.height / 2);

			this->currentDepth = 0;
			this->topShadow = topShadow;
			this->bottomShadow = bottomShadow;

			if (depth < 1)
				depth = 1;
			else if (depth > ShadowLayer::MAX_SHADOW_CONFIG)
				depth = ShadowLayer::MAX_SHADOW_CONFIG;

			this->setContentSize(size);
			this->ignoreAnchorPointForPosition(false);
			this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			this->setPosition(size.width / 2, size.height / 2);
			this->setCascadeColorEnabled(true);
			this->setCascadeOpacityEnabled(true);

			this->setDepth(depth);

			return true;
		}

		int ShadowLayer::getDepth(void) const
		{
			return this->currentDepth;
		}

		void ShadowLayer::setDepth(int depth)
		{
			if (depth < 1)
				depth = 1;
			else if (depth > ShadowLayer::MAX_SHADOW_CONFIG)
				depth = ShadowLayer::MAX_SHADOW_CONFIG;

			if (this->currentDepth != depth)
			{
				this->currentDepth = depth;

				const auto &topConfig = ShadowLayer::topShadowConfigs[depth - 1];
				const auto &bottomConfig = ShadowLayer::bottomShadowConfigs[depth - 1];

				this->topShadow->stopAnimation();
				this->topShadow->setPositionY(this->getContentSize().height / 2 - topConfig.OffsetY);
				this->topShadow->setBlurRadius(topConfig.BlurRadius);
				this->topShadow->setOpacity(topConfig.Opacity);

				this->bottomShadow->stopAnimation();
				this->bottomShadow->setPositionY(this->getContentSize().height / 2 - bottomConfig.OffsetY);
				this->bottomShadow->setBlurRadius(bottomConfig.BlurRadius);
				this->bottomShadow->setOpacity(bottomConfig.Opacity);
			}
		}

		void ShadowLayer::changeDepth(int depth, float duration)
		{
			if (depth < 1)
				depth = 1;
			else if (depth > ShadowLayer::MAX_SHADOW_CONFIG)
				depth = ShadowLayer::MAX_SHADOW_CONFIG;

			if (this->currentDepth != depth)
			{
				this->currentDepth = depth;

				const auto &topConfig = ShadowLayer::topShadowConfigs[depth - 1];
				const auto &bottomConfig = ShadowLayer::bottomShadowConfigs[depth - 1];

				this->topShadow->stopAnimation();
				this->topShadow->animate(duration,
					Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 - topConfig.OffsetY),
					topConfig.Opacity,
					topConfig.BlurRadius);

				this->bottomShadow->stopAnimation();
				this->bottomShadow->animate(duration,
					Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 - bottomConfig.OffsetY),
					bottomConfig.Opacity,
					bottomConfig.BlurRadius);

				if (!this->animating)
				{
					this->scheduleUpdate();
					this->animating = true;
				}
			}
		}

	} //namespace Pyro::Shadow

} //namespace Pyro
