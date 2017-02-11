#ifndef __PYRO_SEQUENCEBUILDER_H__
#define __PYRO_SEQUENCEBUILDER_H__

#include "ActionBuilder.h"

namespace Pyro
{
	namespace Animations
	{
		class SequenceBuilder : public ActionBuilder
		{
		public:
			SequenceBuilder(cocos2d::Node *target)
				: ActionBuilder(target)
			{
			}

			SequenceBuilder(ActionBuilder *parent)
				: ActionBuilder(parent)
			{
			}

		public:
			virtual cocos2d::Action * create(void) override
			{
				return cocos2d::Sequence::create(ActionBuilder::_actions);
			}
		};
	}
}

#endif//__PYRO_SEQUENCEBUILDER_H__
