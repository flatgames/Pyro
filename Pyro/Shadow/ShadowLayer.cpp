#include "ShadowLayer.h"
#include "ShadowConfig.h"
#include "ShadowSprite.h"
#include "Blur.h"

using namespace cocos2d;

namespace Pyro
{

	namespace Shadow
	{

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
			: currentDepth(0), topShadow(nullptr), bottomShadow(nullptr)
		{
		}

		ShadowLayer::~ShadowLayer(void)
		{
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
			if (!Super::init())
				return false;

			if (!ShadowLayer::configReady)
				ShadowLayer::initConfigs();

			auto shadowSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(SHADOW_FILENAME);
			if (!shadowSpriteFrame)
			{
				auto texture = Director::getInstance()->getTextureCache()->addImage(SHADOW_FILENAME);
				auto rect = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
				shadowSpriteFrame = SpriteFrame::createWithTexture(texture, rect);
				SpriteFrameCache::getInstance()->addSpriteFrame(shadowSpriteFrame, SHADOW_FILENAME);
			}

			auto topShadow = ShadowSprite::createWithSpriteFrame(shadowSpriteFrame, SHADOW_SPRITE_INSETS, SHADOW_ORG_BLUR_RADIUS);
			topShadow->setContentSize(size);
			topShadow->setPosition(size.width / 2, size.height / 2);

			auto bottomShadow = ShadowSprite::createWithSpriteFrame(shadowSpriteFrame, SHADOW_SPRITE_INSETS, SHADOW_ORG_BLUR_RADIUS);
			bottomShadow->setContentSize(size);
			bottomShadow->setPosition(size.width / 2, size.height / 2);

			this->addChild(topShadow, 2);
			this->addChild(bottomShadow, 1);

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

				this->topShadow->stopAllActions();
				this->topShadow->setPositionY(this->getContentSize().height / 2 - topConfig.OffsetY);
				this->topShadow->setBlurRadius(topConfig.BlurRadius);
				this->topShadow->setOpacity(topConfig.Opacity);

				this->bottomShadow->stopAllActions();
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

				this->topShadow->stopAllActions();
				this->topShadow->runAction(Spawn::create(
					MoveTo::create(duration, Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 - topConfig.OffsetY)),
					Blur::create(duration, -1, topConfig.BlurRadius),
					FadeTo::create(duration, topConfig.Opacity),
					nullptr));

				this->bottomShadow->stopAllActions();
				this->bottomShadow->runAction(Spawn::create(
					MoveTo::create(duration, Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 - bottomConfig.OffsetY)),
					Blur::create(duration, -1, bottomConfig.BlurRadius),
					FadeTo::create(duration, bottomConfig.Opacity),
					nullptr));
			}
		}

	} //namespace Pyro::Shadow

} //namespace Pyro
