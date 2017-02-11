#ifndef __PYRO_COMPONENTS_PAPER_H__
#define __PYRO_COMPONENTS_PAPER_H__

#include <cocos2d.h>

namespace Pyro
{
	namespace Shadow
	{
		class ShadowLayer;
	}

	namespace Components
	{

		// Base class of all paper components.
		class Paper : public cocos2d::Node
		{
			typedef cocos2d::Node Super;

		public:
			static cocos2d::SpriteFrame * getRoundedNinePatchFrame(cocos2d::Rect &insets);
			static float getRoundedCornerRadius(void);

		public:
			// Create a paper with the given properties.
			// * size: the paper size.
			// * roundedCorner: if true, the paper has rounded corners.
			// * color: background color of the paper.
			static Paper * create(const cocos2d::Size &size, bool roundedCorner = false, const cocos2d::Color3B &color = cocos2d::Color3B::WHITE);

		public:
			Paper(void);
			virtual ~Paper(void);

			virtual void setContentSize(const cocos2d::Size &size) override;

		protected:
			virtual bool init(const cocos2d::Size &size, bool roundedCorner, const cocos2d::Color3B &color);

		public:
			// Returns true if the paper has rounded corners.
			inline bool hasRoundedCorner(void) const
			{
				return roundedCorner;
			}

			// Returns the container node of the paper.
			// For proper clipping, all inner components should be added as the children of this node.
			inline cocos2d::Node * getContainer(void)
			{
				return shapeNode;
			}

			// Returns the node used as the paper surface.
			inline cocos2d::Node * getBackground(void)
			{
				return backgroundNode;
			}

			// Returns true if the paper has a shadow layer.
			bool isShadowEnabled(void) const;

			// If the paper does not have a shadow layer, create one with the given depth.
			// * depth: shadow depth, should be from 1 to 5.
			void enableShadow(int depth);

			// If the paper has a shadow layer, removes it.
			void disableShadow(void);

			// Returns the current depth of the shadow layer.
			// If the paper does not have a shadow layer, returns 0.
			int getShadowDepth(void) const;

			// Immediately sets the current depth of the shadow layer.
			// * depth: should be from 1 to 5.
			// If the paper does not have a shadow layer, this method does nothing.
			void setShadowDepth(int depth);

			// Runs an action on the shadow layer to change its depth.
			// If the paper does not have a shadow layer, this method does nothing.
			void changeShadowDepth(int depth, float duration);

		protected:
			bool roundedCorner;
			cocos2d::Node *shapeNode;
			cocos2d::Node *backgroundNode;
			Shadow::ShadowLayer *shadowLayer;

		public:
			static const char *CARD_LOW_FILENAME;
			static const char *CARD_MEDIUM_FILENAME;
			static const char *CARD_HIGH_FILENAME;
		};

	} //namespace Pyro::Components

} //namespace Pyro

#endif//__PYRO_COMPONENTS_PAPER_H__
