#ifndef __PYRO_COMPONENT_INKPAPER_H__
#define __PYRO_COMPONENT_INKPAPER_H__

#include "Paper.h"

namespace Pyro
{

	namespace Components
	{

		// Represents a paper that can show an ink flooding on its surface.
		class InkPaper : public Paper
		{
			typedef Paper Super;

		public:
			// Create a paper with the given properties.
			// * size: the paper size.
			// * roundedCorner: if true, the paper has rounded corners.
			// * color: background color of the paper.
			static InkPaper * create(const cocos2d::Size &size, bool roundedCorner = false, const cocos2d::Color3B &color = cocos2d::Color3B::WHITE);

		public:
			InkPaper(void);
			virtual ~InkPaper(void);

			virtual void setContentSize(const cocos2d::Size &size) override;

		protected:
			virtual bool init(const cocos2d::Size &size, bool roundedCorner, const cocos2d::Color3B &color);

		public:
			// Returns the circle of the ink ripple.
			inline cocos2d::Node * getTouchCircle(void)
			{
				return touchCircle;
			}

			// Returns the surface of the ink ripple.
			inline cocos2d::Node * getTouchSurface(void)
			{
				return touchSurface;
			}

			// Applies the given color to touch circle and touch surface.
			inline void setTouchRippleColor(const cocos2d::Color3B &color)
			{
				touchCircle->setColor(color);
				touchSurface->setColor(color);
			}

			// Shows a touch ripple originating from the given position.
			// * localPosition: origin of the ripple, in paper coordinates.
			void showTouchRipple(const cocos2d::Vec2 &localPosition);

			// Stops the touch ripple animation and fades out the effect elements.
			void hideTouchRipple(bool keepCircle = false);

			float getRippleRemainingTime(void) const;

			bool isRippleClipped(void) const
			{
				return rippleClipped;
			}

			void setRippleClipped(bool clipped);

		protected:
			cocos2d::Node *touchCircle;
			cocos2d::Node *touchSurface;
			cocos2d::Node *rippleFrame;
			bool rippleClipped;
		};

	} //namespace Pyro::Components

} //namespace Pyro

#endif//__PYRO_COMPONENT_INKPAPER_H__
