#ifndef __PYRO_COMPONENTS_INKBUTTON_H__
#define __PYRO_COMPONENTS_INKBUTTON_H__

#include "InkPaper.h"
#include "Floreto/UI/TouchPhase.h"
#include "Floreto/UI/Button.h"
#include "Floreto/UI/TouchProtocol.h"

namespace Pyro
{

	namespace Components
	{

		// Represents an ink paper that acts like a button.
		class InkButton : public InkPaper, public Floreto::TouchProtocol
		{
			typedef InkPaper Super;

		public:
			// The parameters given to create function.
			// If textFontSize is not positive, then textFont indicates a FNT (bitmap font) file.
			// Otherwise textFont indicates a TTF file.
			struct CreateParams
			{
				cocos2d::Size size;
				float xPadding;
				float yPadding;
				float minWidth;
				float minHeight;
				bool roundedCorner;
				cocos2d::Node *icon;
				std::string text;
				std::string textFont;
				float textFontSize;
				cocos2d::Color3B textColor;
				cocos2d::Color3B paperColor;
				bool paperVisible;
				bool rippleClipped;
				bool rippleFromCenter;

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
					this->icon = nullptr;
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

				CreateParams & withPaperVisible(bool visible)
				{
					this->paperVisible = visible;
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
					: xPadding(-1), yPadding(-1), minWidth(0), minHeight(0),
					roundedCorner(false), icon(nullptr), textFontSize(0), paperVisible(true),
					rippleClipped(true), rippleFromCenter(false)
				{
				}

				CreateParams(const cocos2d::Size &size, bool roundedCorner,
					const std::string &text, const std::string &textFont, float textFontSize,
					const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, bool paperVisible,
					bool rippleClipped, bool rippleFromCenter)
					: size(size), roundedCorner(roundedCorner),
					text(text), textFont(textFont), textFontSize(textFontSize),
					textColor(textColor), paperColor(paperColor), paperVisible(paperVisible),
					rippleClipped(rippleClipped), rippleFromCenter(rippleFromCenter)
				{
					xPadding = -1;
					yPadding = -1;
					minWidth = 0;
					minHeight = 0;
					icon = nullptr;
				}

				CreateParams(float xPadding, float yPadding, float minWidth, float minHeight, bool roundedCorner,
					const std::string &text, const std::string &textFont, float textFontSize,
					const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, bool paperVisible,
					bool rippleClipped, bool rippleFromCenter)
					: xPadding(xPadding), yPadding(yPadding), minWidth(minWidth), minHeight(minHeight), roundedCorner(roundedCorner),
					text(text), textFont(textFont), textFontSize(textFontSize),
					textColor(textColor), paperColor(paperColor), paperVisible(paperVisible),
					rippleClipped(rippleClipped), rippleFromCenter(rippleFromCenter)
				{
					size.setSize(0, 0);
					icon = nullptr;
				}
			};

		public:
			// Button callback signature.
			typedef std::function<void(InkButton *, const cocos2d::Vec2 &, Floreto::TouchPhase)> Callback;

		public:
			// Creates a paper button with the given properties.
			// * size: the paper size.
			// * roundedCorner: if true, the paper has rounded corners.
			// * color: background color of the paper.
			// * icon: a node used as the icon (or title) of the button.
			// * callback: touch event listener for the button.
			static InkButton * create(const cocos2d::Size &size, bool roundedCorner, const cocos2d::Color3B &color, cocos2d::Node *icon, const Callback &callback);

			// Creates a paper button with the given properties.
			// * size: the paper size.
			// * roundedCorner: if true, the paper has rounded corners.
			// * text: the text printed on the paper.
			// * textFont: the font used for the button text.
			// * textFontSize: size of the text font, measured in pt.
			// * textColor: color of the button text.
			// * paperColor: color of the button background.
			// * callback: touch event listener for the button.
			static InkButton * create(const cocos2d::Size &size, bool roundedCorner,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);

			// Creates a paper button with the given properties.
			// * roundedCorner: if true, the paper has rounded corners.
			// * xPadding: horizontal padding from button edge to text.
			// * yPadding: vertical padding from button edge to text.
			// * text: the text printed on the paper.
			// * textFont: the font used for the button text.
			// * textFontSize: size of the text font, measured in pt.
			// * textColor: color of the button text.
			// * paperColor: color of the button background.
			// * callback: touch event listener for the button.
			static InkButton * create(bool roundedCorner, float xPadding, float yPadding,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);

			// Creates a paper button with the given create-params.
			static InkButton * create(const CreateParams &params, const Callback &callback);

		public:
			InkButton(void);
			virtual ~InkButton(void);

			virtual void setContentSize(const cocos2d::Size &size) override;

		public:
			inline cocos2d::Node * getIcon(void)
			{
				return this->icon;
			}

			inline Floreto::Button * getButton(void)
			{
				return this->button;
			}

			virtual bool isRippleFromCenter(void) const
			{
				return this->rippleFromCenter;
			}

			virtual void setRippleFromCenter(bool fromCenter);

		public:
			virtual bool isTouchEnabled(void) const override;
			virtual void setTouchEnabled(bool enabled) override;

		protected:
			virtual bool init(const cocos2d::Size &size, bool roundedCorner, const cocos2d::Color3B &color, cocos2d::Node *icon, const Callback &callback);
			virtual bool init(const cocos2d::Size &size, bool roundedCorner,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);
			virtual bool init(bool roundedCorner, float xPadding, float yPadding,
				const std::string &text, const std::string &textFont, int textFontSize,
				const cocos2d::Color3B &textColor, const cocos2d::Color3B &paperColor, const Callback &callback);

			virtual bool init(const CreateParams &params, const Callback &callback);

		protected:
			bool onTouch(Floreto::Button *, cocos2d::Touch *, Floreto::TouchPhase);

		protected:
			cocos2d::Node *icon;
			Floreto::Button *button;
			bool touchOut;
			Callback callback;
			bool rippleFromCenter;
		};

	} //namespace Pyro::Components

} //namespace Pyro

#endif//__PYRO_COMPONENTS_INKBUTTON_H__
