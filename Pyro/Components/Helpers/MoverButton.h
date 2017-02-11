#ifndef __MOVERBUTTON_H__
#define __MOVERBUTTON_H__

#include "Floreto/UI/Button.h"

namespace Pyro
{

	namespace Components
	{

		namespace Helpers
		{

			// Acts as a sensor for the dragging gesture on a given target.
			class MoverButton : public Floreto::Button
			{
				typedef Floreto::Button Super;

			public:
				enum class Orientation
				{
					Both,
					Vertical,
					Horizontal
				};

			public:
				static MoverButton * create(void);
				static MoverButton * create(cocos2d::Node *target);

			public:
				MoverButton(void);

			protected:
				virtual bool init(cocos2d::Node *target);
				bool onTouch(Floreto::Button *button, cocos2d::Touch *touch, Floreto::TouchPhase phase);

			public:
				cocos2d::Node * getTarget(void)
				{
					return target;
				}

				void setTarget(cocos2d::Node *target)
				{
					this->target = target;
					if (target)
						this->setContentSize(target->getContentSize());
				}

				Orientation getOrientation(void) const
				{
					return orientation;
				}

				void setOrientation(Orientation orientation)
				{
					this->orientation = orientation;
				}
			
			protected:
				cocos2d::Node *target;
				bool active;
				Orientation orientation;
			};

		} //namespace Helpers

	} //namespace Components

} //namespace Pyro

#endif//__MOVERBUTTON_H__
