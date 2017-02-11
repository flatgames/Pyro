#ifndef __PYRO_COMPONENT_HELPERS_BATCHEDNINEPATCHSPRITE_H__
#define __PYRO_COMPONENT_HELPERS_BATCHEDNINEPATCHSPRITE_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Components
	{

		namespace Helpers
		{

			class BatchedNinePatchSprite : public cocos2d::SpriteBatchNode
			{
			public:
				static BatchedNinePatchSprite * createWithFile(const std::string &filename, const cocos2d::Rect &insets);
				static BatchedNinePatchSprite * createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame, const cocos2d::Rect &insets);
				static BatchedNinePatchSprite * createWithSpriteFrameName(const std::string &spriteFrameName, const cocos2d::Rect &insets);

			public:
				BatchedNinePatchSprite(void);
				virtual ~BatchedNinePatchSprite(void);

				virtual void setContentSize(const cocos2d::Size &size) override;

			protected:
				virtual bool initWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame, const cocos2d::Rect &insets);

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
			};

		} //namespace Helpers

	} //namespace Components

} //namespace Pyro

#endif//__PYRO_COMPONENT_HELPERS_BATCHEDNINEPATCHSPRITE_H__
