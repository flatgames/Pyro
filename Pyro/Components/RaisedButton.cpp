#include "RaisedButton.h"
#include "Floreto/UI/Button.h"

using namespace cocos2d;

namespace Pyro
{

	namespace Components
	{

		RaisedButton * RaisedButton::create(const Size &size, bool roundedCorner, int depth, const Color3B &color, Node *icon, const Callback &callback)
		{
			auto button = new RaisedButton();
			if (button && button->init(size, roundedCorner, depth, color, icon, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		RaisedButton * RaisedButton::create(const Size &size, bool roundedCorner, int depth, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			auto button = new RaisedButton();
			if (button && button->init(size, roundedCorner, depth, text, textFont, textFontSize, textColor, paperColor, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		RaisedButton * RaisedButton::create(bool roundedCorner, int depth, float xPadding, float yPadding, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			auto button = new RaisedButton();
			if (button && button->init(roundedCorner, depth, xPadding, yPadding, text, textFont, textFontSize, textColor, paperColor, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		RaisedButton * RaisedButton::create(const CreateParams &params, const Callback &callback)
		{
			auto button = new RaisedButton();
			if (button && button->init(params, callback))
			{
				button->autorelease();
				return button;
			}
			CC_SAFE_DELETE(button);
			return nullptr;
		}

		RaisedButton::RaisedButton(void)
			: defaultDepth(0)
		{
		}

		RaisedButton::~RaisedButton(void)
		{
		}

		bool RaisedButton::init(const Size &size, bool roundedCorner, int depth, const Color3B &color, Node *icon, const Callback &callback)
		{
			if (!Super::init(size, roundedCorner, color, icon, callback))
				return false;

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(RaisedButton::onTouch, this);
			Super::button->setSingleTouchDelegate(delegate, true);

			this->defaultDepth = depth;
			this->enableShadow(depth);

			return true;
		}

		bool RaisedButton::init(const Size &size, bool roundedCorner, int depth, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			if (!Super::init(size, roundedCorner, text, textFont, textFontSize, textColor, paperColor, callback))
				return false;

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(RaisedButton::onTouch, this);
			Super::button->setSingleTouchDelegate(delegate, true);

			this->defaultDepth = depth;
			this->enableShadow(depth);

			return true;
		}

		bool RaisedButton::init(bool roundedCorner, int depth, float xPadding, float yPadding, const std::string &text, const std::string &textFont, int textFontSize, const Color3B &textColor, const Color3B &paperColor, const Callback &callback)
		{
			if (!Super::init(roundedCorner, xPadding, yPadding, text, textFont, textFontSize, textColor, paperColor, callback))
				return false;

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(RaisedButton::onTouch, this);
			Super::button->setSingleTouchDelegate(delegate, true);

			this->defaultDepth = depth;
			this->enableShadow(depth);

			return true;
		}

		bool RaisedButton::init(const CreateParams &params, const Callback &callback)
		{
			if (!Super::init(params, callback))
				return false;

			Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(RaisedButton::onTouch, this);
			Super::button->setSingleTouchDelegate(delegate, true);

			this->defaultDepth = params.depth;
			this->enableShadow(params.depth);

			return true;
		}

		bool RaisedButton::onTouch(Floreto::Button *button, Touch *touch, Floreto::TouchPhase phase)
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

					this->changeShadowDepth(this->defaultDepth + 1, 0.1f);

					this->callback(this, touch->getLocation(), Floreto::TouchPhase::Began);

					return true;
				}
				case Floreto::TouchPhase::Moved:
				{
					if (button->isInsideBounds(touch) == false && !this->touchOut)
					{
						this->touchOut = true;
						this->hideTouchRipple();
						this->changeShadowDepth(this->defaultDepth, 0.5f);
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
						this->changeShadowDepth(this->defaultDepth, 0.5f);
						this->callback(this, touch->getLocation(), Floreto::TouchPhase::Ended);
					}
					break;
				}
				case Floreto::TouchPhase::Dismissed:
				{
					this->hideTouchRipple();
					this->changeShadowDepth(this->defaultDepth, 0.5f);
					this->callback(this, touch->getLocation(), Floreto::TouchPhase::Dismissed);
					break;
				}
			}

			return false;
		}

	} //namespace Pyro::Components

} //namespace Pyro
