#ifndef __PYRO_REPEATBUILDER_H__
#define __PYRO_REPEATBUILDER_H__

#include "ActionBuilder.h"

namespace Pyro
{
	namespace Animations
	{
		class RepeatBuilder : public ActionBuilder
		{
		protected:
			unsigned int _times;
			bool _forever;
			bool _asSpawn;

		public:
			RepeatBuilder(cocos2d::Node *target)
				: ActionBuilder(target), _times(1), _forever(false), _asSpawn(false)
			{
			}

			RepeatBuilder(ActionBuilder *parent)
				: ActionBuilder(parent), _times(1), _forever(false), _asSpawn(false)
			{
			}

		public:
			RepeatBuilder & forever(void)
			{
				this->_forever = true;
				return *this;
			}

			RepeatBuilder & times(unsigned int times)
			{
				this->_times = times;
				this->_forever = false;
				return *this;
			}

			RepeatBuilder & asSequence(void)
			{
				this->_asSpawn = false;
				return *this;
			}

			RepeatBuilder & asSpawn(void)
			{
				this->_asSpawn = true;
				return *this;
			}

		public:
			virtual cocos2d::Action * create(void) override
			{
				cocos2d::ActionInterval *action;
				if (ActionBuilder::_actions.size() == 1)
				{
					action = static_cast<cocos2d::ActionInterval *>(ActionBuilder::_actions.at(0));
				}
				else
				{
					if (this->_asSpawn)
						action = cocos2d::Spawn::create(ActionBuilder::_actions);
					else
						action = cocos2d::Sequence::create(ActionBuilder::_actions);
				}

				if (this->_forever)
					return cocos2d::RepeatForever::create(action);
				else
					return cocos2d::Repeat::create(action, this->_times);
			}
		};
	}
}

#endif//__PYRO_REPEATBUILDER_H__
