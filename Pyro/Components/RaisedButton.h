#ifndef __PYRO_COMPONENTS_RAISEDBUTTON_H__
#define __PYRO_COMPONENTS_RAISEDBUTTON_H__

#include "InkButton.h"

namespace Pyro
{

	namespace Components
	{

		class RaisedButton : public InkButton
		{
			typedef InkButton Super;

		public:
			struct CreateParams : public InkButton::CreateParams
			{
				int depth;

				CreateParams & withDepth(int depth)
				{
					this->depth = depth;
					return *this;
				}

				CreateParams & withSize(const cocos2d::Size &size)
				{
					this->size = size;
					return *this;
				}

				CreateParams & withPadding(float xPadding, float yPadding)
				{
					this->xPadding = xPadding;
					this->yPadding = yPadding;
					return *this;
				}

				CreateParams & withMinSize(float minWidth, float minHeight)
				{
					this->minWidth = minWidth;
					this->minHeight = minHeight;
					return *this;
				}

				CreateParams & withRoundedCorner(bool on)
				{
					this->roundedCorner = on;
					return *this;
				}

				CreateParams & withIcon(cocos2d::Node *icon)
				{
					this->icon = icon;
					return *this;
				}

				CreateParams & withText(const std::string &text)
				{
					this->text = text;
					return *this;
				}

				CreateParams & withFont(const std::string &font)
				{
					this->textFont = font;
					return *this;
				}

				CreateParams & withFontSize(int fontSize)
				{
					this->textFontSize = fontSize;
					return *this;
				}

				CreateParams & withTextColor(const cocos2d::Color3B &color)
				{
					this->textColor = color;
					return *this;
				}

				CreateParams & withPaperColor(const cocos2d::Color3B &color)
				{
					this->paperColor = color;
					return *this;
				}

				CreateParams & withRippleClipped(bool clipped)
				{
					this->rippleClipped = clipped;
					return *this;
				}

				CreateParams & withRippleFromCenter(bool fromCenter)
				{
					this->rippleFromCenter = fromCenter;
					return *this;
				}

				CreateParams(void)
					: depth(0)
				{
				}

				CreateParams(const cocos2d::Size &size, bool roundedCorner, int depth,
					const std::string &text, const std::string &textFont, float textFontSize,
					const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, bool paperVisible,
					bool rippleClipped, bool rippleFromCenter)
					: InkButton::CreateParams(size, roundedCorner, text, textFont, textFontSize, textColor,
					paperColor, paperVisible, rippleClipped, rippleFromCenter),
					depth(depth)
				{
				}

				CreateParams(float xPadding, float yPadding, float minWidth, float minHeight, bool roundedCorner, int depth,
					const std::string &text, const std::string &textFont, float textFontSize,
					const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, bool paperVisible,
					bool rippleClipped, bool rippleFromCenter)
					: InkButton::CreateParams(xPadding, yPadding, minWidth, minHeight, roundedCorner, text, textFont, textFontSize, textColor,
					paperColor, paperVisible, rippleClipped, rippleFromCenter),
					depth(depth)
				{
				}
			};

		public:
			// Creates a paper button with the given properties.
			// * size: the paper size.
			// * roundedCorner: if true, the paper has rounded corners.
			// * depth: the depth of the shadow layer.
			// * color: background color of the paper.
			// * icon: a node used as the icon (or title) of the button.
			// * callback: touch event listener for the button.
			static RaisedButton * create(const cocos2d::Size &size, bool roundedCorner, int depth,
				const cocos2d::Color3B &color, cocos2d::Node *icon, const Callback &callback);

			// Creates a paper button with the given properties.
			// * size: the paper size.
			// * roundedCorner: if true, the paper has rounded corners.
			// * depth: the depth of the shadow layer.
			// * text: the text printed on the paper.
			// * textFont: the font used for the button text.
			// * textFontSize: size of the text font, measured in pt.
			// * textColor: color of the button text.
			// * paperColor: color of the button background.
			// * callback: touch event listener for the button.
			static RaisedButton * create(const cocos2d::Size &size, bool roundedCorner, int depth,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);

			// Creates a paper button with the given properties.
			// * roundedCorner: if true, the paper has rounded corners.
			// * depth: the depth of the shadow layer.
			// * xPadding: horizontal padding from button edge to text.
			// * yPadding: vertical padding from button edge to text.
			// * text: the text printed on the paper.
			// * textFont: the font used for the button text.
			// * textFontSize: size of the text font, measured in pt.
			// * textColor: color of the button text.
			// * paperColor: color of the button background.
			// * callback: touch event listener for the button.
			static RaisedButton * create(bool roundedCorner, int depth, float xPadding, float yPadding,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);

			// Creates a paper button with the given create-params.
			static RaisedButton * create(const CreateParams &params, const Callback &callback);

		public:
			RaisedButton(void);
			virtual ~RaisedButton(void);

		protected:
			virtual bool init(const cocos2d::Size &size, bool roundedCorner, int depth,
				const cocos2d::Color3B &color, cocos2d::Node *icon, const Callback &callback);
			virtual bool init(const cocos2d::Size &size, bool roundedCorner, int depth,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);
			virtual bool init(bool roundedCorner, int depth, float xPadding, float yPadding,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);

			virtual bool init(const CreateParams &params, const Callback &callback);

		protected:
			bool onTouch(Floreto::Button *, cocos2d::Touch *, Floreto::TouchPhase);

		protected:
			int defaultDepth;
		};

	} //namespace Pyro::Components

} //namespace Pyro

#endif//__PYRO_COMPONENTS_RAISEDBUTTON_H__
