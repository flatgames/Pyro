#ifndef __PYRO_SHADOW_SHADOWSPRITE_H__
#define __PYRO_SHADOW_SHADOWSPRITE_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Shadow
	{

		// Represents a shadow sublayer.
		// THIS CLASS IS FOR INTERNAL USE ONLY.
		class ShadowSprite : public cocos2d::SpriteBatchNode
		{
			typedef cocos2d::SpriteBatchNode Super;

		public:
			static ShadowSprite * createWithFile(const std::string &filename, const cocos2d::Rect &insets, float orgBlurRadius);
			static ShadowSprite * createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame, const cocos2d::Rect &insets, float orgBlurRadius);
			static ShadowSprite * createWithSpriteFrameName(const std::string &spriteFrameName, const cocos2d::Rect &insets, float orgBlurRadius);

		public:
			ShadowSprite(void);
			virtual ~ShadowSprite(void);

			virtual void setContentSize(const cocos2d::Size &size) override;

		public:
			virtual float getBlurRadius(void) const;
			virtual void setBlurRadius(float blurRadius);

		protected:
			virtual bool initWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame, const cocos2d::Rect &insets, float orgBlurRadius);

		protected:
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

	} //namespace Pyro::Shadow

} //namespace Pyro

#endif//__PYRO_SHADOW_SHADOWSPRITE_H__
