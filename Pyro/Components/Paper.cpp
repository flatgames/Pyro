#include "Paper.h"
#include "Floreto/UI/NinePatchSprite.h"

#include "../Shadow/ShadowLayer.h"
#include "Helpers/NormalRectangle.h"
#include "Helpers/RoundedRectangle.h"

using namespace cocos2d;

namespace Pyro
{

	namespace Components
	{

		const char *Paper::CARD_LOW_FILENAME = "pyro/card-low.9.png";
		const char *Paper::CARD_MEDIUM_FILENAME = "pyro/card-medium.9.png";
		const char *Paper::CARD_HIGH_FILENAME = "pyro/card-high.9.png";

		SpriteFrame * Paper::getRoundedNinePatchFrame(Rect &insets)
		{
			const char *fileName;

			int dpi = cocos2d::Device::getDPI();
			float frameWidth = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize().width;
			float designWidth = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
			float pixelsPerPoint = frameWidth / designWidth;
			float pointsPerIn = dpi * pixelsPerPoint;

			if (pointsPerIn <= 120)
			{
				fileName = Paper::CARD_LOW_FILENAME;
				insets.setRect(2, 2, 4, 4);
			}
			else if (pointsPerIn <= 180)
			{
				fileName = Paper::CARD_MEDIUM_FILENAME;
				insets.setRect(3, 3, 10, 10);
			}
			else
			{
				fileName = Paper::CARD_HIGH_FILENAME;
				insets.setRect(4, 4, 8, 8);
			}

			auto spriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
			if (!spriteFrame)
			{
				auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(fileName);
				spriteFrame = cocos2d::SpriteFrame::createWithTexture(texture, cocos2d::Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
				cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, fileName);
			}

			return spriteFrame;
		}

		float Paper::getRoundedCornerRadius(void)
		{
			int dpi = cocos2d::Device::getDPI();
			float frameWidth = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize().width;
			float designWidth = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
			float pixelsPerPoint = frameWidth / designWidth;
			float pointsPerIn = dpi * pixelsPerPoint;

			if (pointsPerIn <= 120)
				return 2;
			else if (pointsPerIn <= 180)
				return 3;
			else
				return 4;
		}

		Paper * Paper::create(const Size &size, bool roundedCorner, const Color3B &color)
		{
			auto paper = new Paper();
			if (paper && paper->init(size, roundedCorner, color))
			{
				paper->autorelease();
				return paper;
			}
			CC_SAFE_DELETE(paper);
			return nullptr;
		}

		Paper::Paper(void)
			: roundedCorner(false), shapeNode(nullptr), shadowLayer(nullptr)
		{
		}

		Paper::~Paper(void)
		{
		}

		void Paper::setContentSize(const Size &size)
		{
			Super::setContentSize(size);

			this->shapeNode->setContentSize(size);
			this->shapeNode->setPosition(size.width / 2, size.height / 2);

			if (this->roundedCorner)
				this->backgroundNode->setContentSize(size);
			else
				static_cast<Sprite *>(this->backgroundNode)->setTextureRect(Rect(0, 0, size.width, size.height));
			this->backgroundNode->setPosition(size.width / 2, size.height / 2);

			if (this->shadowLayer)
			{
				this->shadowLayer->setContentSize(size);
				this->shadowLayer->setPosition(size.width / 2, size.height / 2);
			}
		}

		bool Paper::init(const Size &size, bool roundedCorner, const Color3B &color)
		{
			if (!Super::init())
				return false;

			if (roundedCorner)
				this->shapeNode = Helpers::RoundedRectangle::create(size);
			else
				this->shapeNode = Helpers::NormalRectangle::create(size);

			this->addChild(this->shapeNode, 1);
			this->shapeNode->setPosition(size.width / 2, size.height / 2);
			
			if (roundedCorner)
			{
				Rect insets;
				auto spriteFrame = Paper::getRoundedNinePatchFrame(insets);
				auto bgNode = Floreto::NinePatchSprite::createWithSpriteFrame(spriteFrame, insets);
				this->backgroundNode = bgNode;
			}
			else
			{
				auto bgNode = Sprite::create();
				bgNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				this->backgroundNode = bgNode;
			}
			this->backgroundNode->setColor(color);
			this->addChild(this->backgroundNode, 0);

			this->roundedCorner = roundedCorner;

			this->setContentSize(size);
			this->ignoreAnchorPointForPosition(false);
			this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			this->setCascadeColorEnabled(true);
			this->setCascadeOpacityEnabled(true);

			return true;
		}

		bool Paper::isShadowEnabled(void) const
		{
			return this->shadowLayer != nullptr;
		}

		void Paper::enableShadow(int depth)
		{
			if (this->shadowLayer == nullptr)
			{
				auto layer = Shadow::ShadowLayer::create(this->getContentSize(), depth);
				this->addChild(layer, -1);
				this->shadowLayer = layer;
			}
		}

		void Paper::disableShadow(void)
		{
			if (this->shadowLayer != nullptr)
			{
				this->shadowLayer->removeFromParent();
				this->shadowLayer = nullptr;
			}
		}

		int Paper::getShadowDepth(void) const
		{
			if (this->shadowLayer != nullptr)
				return this->shadowLayer->getDepth();
			else
				return 0;
		}

		void Paper::setShadowDepth(int depth)
		{
			if (this->shadowLayer != nullptr)
				this->shadowLayer->setDepth(depth);
		}

		void Paper::changeShadowDepth(int depth, float duration)
		{
			if (this->shadowLayer != nullptr)
				this->shadowLayer->changeDepth(depth, duration);
		}

	} //namespace Components

} //namespace Pyro
