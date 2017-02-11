#include "MoverButton.h"

using namespace cocos2d;

namespace Pyro
{

	namespace Components
	{

		namespace Helpers
		{

			MoverButton * MoverButton::create(void)
			{
				return MoverButton::create(nullptr);
			}

			MoverButton * MoverButton::create(cocos2d::Node *target)
			{
				auto button = new MoverButton();
				if (button && button->init(target))
				{
					button->autorelease();
					return button;
				}
				CC_SAFE_DELETE(button);
				return nullptr;
			}

			MoverButton::MoverButton(void)
				: target(nullptr), active(false), orientation(Orientation::Both)
			{
			}

			bool MoverButton::init(cocos2d::Node *target)
			{
				Floreto::Button::SingleTouchDelegate delegate = CC_CALLBACK_3(MoverButton::onTouch, this);
				if (!Super::init(nullptr, delegate, nullptr, false, false))
					return false;

				this->setTarget(target);
				return true;
			}

			bool MoverButton::onTouch(Floreto::Button *button, cocos2d::Touch *touch, Floreto::TouchPhase phase)
			{
				switch (phase)
				{
					case Floreto::TouchPhase::Began:
					{
						this->active = true;
						return true;
					}
					case Floreto::TouchPhase::Moved:
					{
						if (this->active)
						{
							auto diff = touch->getDelta();
							auto pos = this->target->getPosition();
							if (orientation == Orientation::Vertical)
								pos.y += diff.y;
							else if (orientation == Orientation::Horizontal)
								pos.x += diff.x;
							else
								pos += diff;
							this->target->setPosition(pos);
						}
						break;
					}
					case Floreto::TouchPhase::Ended:
					case Floreto::TouchPhase::Cancelled:
					case Floreto::TouchPhase::Dismissed:
					{
						this->active = false;
						break;
					}
					default:
					{
						break;
					}
				}

				return false;
			}

		} //namespace Helpers

	} //namespace Components

} //namespace Pyro

