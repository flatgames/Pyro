#include "ShadowSprite.h"

using namespace cocos2d;

namespace Pyro
{
	
	namespace Shadow
	{

		ShadowSprite * ShadowSprite::createWithFile(const std::string &filename, const Rect &insets, float orgBlurRadius)
		{
			auto texture = Director::getInstance()->getTextureCache()->addImage(filename);
			if (!texture)
				return nullptr;

			auto size = texture->getContentSize();
			auto spriteFrame = SpriteFrame::createWithTexture(texture, Rect(0, 0, size.width, size.height));

			return ShadowSprite::createWithSpriteFrame(spriteFrame, insets, orgBlurRadius);
		}

		ShadowSprite * ShadowSprite::createWithSpriteFrame(SpriteFrame *spriteFrame, const Rect &insets, float orgBlurRadius)
		{
			auto sprite = new ShadowSprite();
			if (sprite && sprite->initWithSpriteFrame(spriteFrame, insets, orgBlurRadius))
			{
				sprite->autorelease();
				return sprite;
			}

			CC_SAFE_DELETE(sprite);
			return nullptr;
		}

		ShadowSprite * ShadowSprite::createWithSpriteFrameName(const std::string &spriteFrameName, const Rect &insets, float orgBlurRadius)
		{
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
			return ShadowSprite::createWithSpriteFrame(spriteFrame, insets, orgBlurRadius);
		}

		ShadowSprite::ShadowSprite(void)
			: topLeft(nullptr), topCenter(nullptr), topRight(nullptr),
			middleLeft(nullptr), middleCenter(nullptr), middleRight(nullptr),
			bottomLeft(nullptr), bottomCenter(nullptr), bottomRight(nullptr),
			orgBlurRadius(0), currentBlurRadius(0)
		{
		}

		ShadowSprite::~ShadowSprite(void)
		{
		}

		void ShadowSprite::setContentSize(const Size &size)
		{
			float width = size.width - this->currentBlurRadius;
			float height = size.height - this->currentBlurRadius;
			if (width <= 0)
				width = 1;
			if (height <= 0)
				height = 1;

			Super::setContentSize(Size(width, height));
			this->formalSize = size;

			float xScale = width / insets.size.width;
			float yScale = height / insets.size.height;

			this->topLeft->setPosition(0, height);
			this->topCenter->setPosition(width / 2, height);
			this->topCenter->setScaleX(xScale);
			this->topRight->setPosition(width, height);

			this->middleLeft->setPosition(0, height / 2);
			this->middleLeft->setScaleY(yScale);
			this->middleCenter->setPosition(width / 2, height / 2);
			this->middleCenter->setScale(xScale, yScale);
			this->middleRight->setPosition(width, height / 2);
			this->middleRight->setScaleY(yScale);

			this->bottomLeft->setPosition(0, 0);
			this->bottomCenter->setPosition(width / 2, 0);
			this->bottomCenter->setScaleX(xScale);
			this->bottomRight->setPosition(width, 0);
		}

		float ShadowSprite::getBlurRadius(void) const
		{
			return this->currentBlurRadius;
		}

		void ShadowSprite::setBlurRadius(float blurRadius)
		{
			if (blurRadius != this->currentBlurRadius)
			{
				this->currentBlurRadius = blurRadius;

				float ratio = blurRadius / this->orgBlurRadius;

				this->topLeft->setScale(ratio);
				this->topCenter->setScaleY(ratio);
				this->topRight->setScale(ratio);

				this->middleLeft->setScaleX(ratio);
				this->middleRight->setScaleX(ratio);

				this->bottomLeft->setScale(ratio);
				this->bottomCenter->setScaleY(ratio);
				this->bottomRight->setScale(ratio);

				this->setContentSize(this->formalSize);
			}
		}

		bool ShadowSprite::initWithSpriteFrame(SpriteFrame *spriteFrame, const Rect &insets, float orgBlurRadius)
		{
			CCASSERT(spriteFrame != nullptr, "ArgumentNullException");

			auto texture = spriteFrame->getTexture();
			auto rect = spriteFrame->getRect();

			if (!Super::initWithTexture(texture, 9))
				return false;

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

			this->addChild(topLeft, 0);
			this->addChild(topCenter, 0);
			this->addChild(topRight, 0);
			this->addChild(middleLeft, 0);
			this->addChild(middleCenter, 0);
			this->addChild(middleRight, 0);
			this->addChild(bottomLeft, 0);
			this->addChild(bottomCenter, 0);
			this->addChild(bottomRight, 0);

			this->setContentSize(rect.size);
			this->setCascadeColorEnabled(true);
			this->setCascadeOpacityEnabled(true);
			this->ignoreAnchorPointForPosition(false);
			this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

			return true;
		}

	} //namespace Pyro::Shadow

} //namespace Pyro
