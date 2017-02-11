#include "InkButton.h"
#include "Floreto/UI/Button.h"

using namespace cocos2d;

namespace Pyro
{

	namespace Components
	{

		InkButton * InkButton::create(const Size &size, bool roundedCorner, const Color3B &color, Node *icon, const Callback &callback)
		{
			auto button = new InkButton();
			if (button && button->init(size, roundedCorner, color, icon, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		InkButton * InkButton::create(const Size &size, bool roundedCorner, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			auto button = new InkButton();
			if (button && button->init(size, roundedCorner, text, textFont, textFontSize, textColor, paperColor, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		InkButton * InkButton::create(bool roundedCorner, float xPadding, float yPadding, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			auto button = new InkButton();
			if (button && button->init(roundedCorner, xPadding, yPadding, text, textFont, textFontSize, textColor, paperColor, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		InkButton * InkButton::create(const CreateParams &params, const Callback &callback)
		{
			auto button = new InkButton();
			if (button && button->init(params, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		InkButton::InkButton(void)
			: icon(nullptr), button(nullptr), touchOut(false), callback(nullptr)
		{
		}

		InkButton::~InkButton(void)
		{
		}

		void InkButton::setContentSize(const cocos2d::Size &size)
		{
			Super::setContentSize(size);
			if (this->icon)
				this->icon->setPosition(size.width / 2, size.height / 2);
			if (this->button)
			{
				this->button->setContentSize(size);
				this->button->setPosition(size.width / 2, size.height / 2);
			}
		}

		bool InkButton::init(const Size &size, bool roundedCorner, const Color3B &color, Node *icon, const Callback &callback)
		{
			if (!Super::init(size, roundedCorner, color))
				return false;

			icon->setPosition(size.width / 2, size.height / 2);
			this->addChild(icon, 0);

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(InkButton::onTouch, this);
			auto button = Floreto::Button::create(delegate, false);
			button->setContentSize(size);
			button->setPosition(size.width / 2, size.height / 2);
			this->addChild(button, 100);
			
			this->icon = icon;
			this->button = button;
			this->callback = callback;

			return true;
		}

		bool InkButton::init(const Size &size, bool roundedCorner, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			if (!Super::init(size, roundedCorner, paperColor))
				return false;

			Label *icon;
			if (textFontSize > 0)
			{
				icon = Label::createWithTTF(text, textFont, textFontSize);
			}
			else
			{
				icon = Label::createWithBMFont(textFont, text);
				icon->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
			}

			icon->setColor(textColor);
			icon->setPosition(size.width / 2, size.height / 2);
			this->addChild(icon, 0);

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(InkButton::onTouch, this);
			auto button = Floreto::Button::create(delegate, false);
			button->setContentSize(size);
			button->setPosition(size.width / 2, size.height / 2);
			this->addChild(button, 100);

			this->icon = icon;
			this->button = button;
			this->callback = callback;

			return true;
		}

		bool InkButton::init(bool roundedCorner, float xPadding, float yPadding, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			Label *icon;
			if (textFontSize > 0)
			{
				icon = Label::createWithTTF(text, textFont, textFontSize);
			}
			else
			{
				icon = Label::createWithBMFont(textFont, text);
				icon->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
			}

			auto size = Size(icon->getContentSize().width + xPadding * 2, icon->getContentSize().height + yPadding * 2);

			if (!Super::init(size, roundedCorner, paperColor))
				return false;

			icon->setColor(textColor);
			icon->setPosition(size.width / 2, size.height / 2);
			this->addChild(icon, 0);

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(InkButton::onTouch, this);
			auto button = Floreto::Button::create(delegate, false);
			button->setContentSize(size);
			button->setPosition(size.width / 2, size.height / 2);
			this->addChild(button, 100);

			this->icon = icon;
			this->button = button;
			this->callback = callback;

			return true;
		}

		bool InkButton::init(const CreateParams &params, const Callback &callback)
		{
			Node *icon;
			if (params.icon)
			{
				icon = params.icon;
			}
			else
			{
				if (params.textFontSize > 0)
				{
					icon = Label::createWithTTF(params.text, params.textFont, params.textFontSize);
				}
				else
				{
					icon = Label::createWithBMFont(params.textFont, params.text);
					static_cast<Label *>(icon)->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
				}
			}

			Size size;

			if (params.xPadding > 0)
			{
				size = Size(icon->getContentSize().width + params.xPadding * 2, icon->getContentSize().height + params.yPadding * 2);
				if (size.width < params.minWidth)
					size.width = params.minWidth;
				if (size.height < params.minHeight)
					size.height = params.minHeight;
			}
			else
			{
				size = params.size;
			}

			if (!Super::init(size, params.roundedCorner, params.paperColor))
				return false;

			icon->setColor(params.textColor);
			icon->setPosition(size.width / 2, size.height / 2);
			this->addChild(icon, 0);

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(InkButton::onTouch, this);
			auto button = Floreto::Button::create(delegate, false);
			button->setContentSize(size);
			button->setPosition(size.width / 2, size.height / 2);
			this->addChild(button, 100);

			this->icon = icon;
			this->button = button;
			this->callback = callback;
			this->setRippleClipped(params.rippleClipped);
			this->rippleFromCenter = params.rippleFromCenter;

			this->setTouchRippleColor(params.textColor);
			this->getBackground()->setVisible(params.paperVisible);

			return true;
		}

		void InkButton::setRippleFromCenter(bool fromCenter)
		{
			this->rippleFromCenter = fromCenter;
		}

		bool InkButton::isTouchEnabled(void) const
		{
			return this->button->isTouchEnabled();
		}

		void InkButton::setTouchEnabled(bool enabled)
		{
			this->button->setTouchEnabled(enabled);
		}

		bool InkButton::onTouch(Floreto::Button *button, Touch *touch, Floreto::TouchPhase phase)
		{
			switch (phase)
			{
				case Floreto::TouchPhase::Began:
				{
					this->touchOut = false;

					if (this->rippleFromCenter)
					{
						this->showTouchRipple(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
					}
					else
					{
						auto localPosition = this->convertToNodeSpace(touch->getLocation());
						this->showTouchRipple(localPosition);
					}

					this->callback(this, touch->getLocation(), Floreto::TouchPhase::Began);

					return true;
				}
				case Floreto::TouchPhase::Moved:
				{
					if (button->isInsideBounds(touch) == false && !this->touchOut)
					{
						this->touchOut = true;
						this->hideTouchRipple();
						this->callback(this, touch->getLocation(), Floreto::TouchPhase::Dismissed);
					}
					else
					{
						this->callback(this, touch->getLocation(), Floreto::TouchPhase::Moved);
					}
					break;
				}
				case Floreto::TouchPhase::Ended:
				case Floreto::TouchPhase::Cancelled:
				{
					if (button->isInsideBounds(touch) && !this->touchOut)
					{
						this->hideTouchRipple(true /*keepCircle*/);
						this->callback(this, touch->getLocation(), Floreto::TouchPhase::Ended);
					}
					break;
				}
				case Floreto::TouchPhase::Dismissed:
				{
					this->hideTouchRipple();
					this->callback(this, touch->getLocation(), Floreto::TouchPhase::Dismissed);
					break;
				}
			}

			return false;
		}

	} //namespace Pyro::Components

} //namespace Pyro
