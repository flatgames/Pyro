#ifndef __PYRO_SPAWNBUILDER_H__
#define __PYRO_SPAWNBUILDER_H__

#include "ActionBuilder.h"

namespace Pyro
{
	namespace Animations
	{
		class SpawnBuilder : public ActionBuilder
		{
		public:
			SpawnBuilder(cocos2d::Node *target)
				: ActionBuilder(target)
			{
			}

			SpawnBuilder(ActionBuilder *parent)
				: ActionBuilder(parent)
			{
			}

		public:
			virtual cocos2d::Action * create(void) override
			{
				return cocos2d::Spawn::create(ActionBuilder::_actions);
			}
		};
	}
}

#endif//__PYRO_SPAWNBUILDER_H__
