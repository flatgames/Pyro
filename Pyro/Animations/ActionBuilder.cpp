#include "ActionBuilder.h"
#include "SequenceBuilder.h"
#include "SpawnBuilder.h"
#include "RepeatBuilder.h"

namespace Pyro
{
	namespace Animations
	{
		SequenceBuilder ActionBuilder::beginSequence(void)
		{
			return SequenceBuilder(this);
		}

		SpawnBuilder ActionBuilder::beginSpawn(void)
		{
			return SpawnBuilder(this);
		}

		RepeatBuilder ActionBuilder::beginRepeat(void)
		{
			return RepeatBuilder(this);
		}
	}
}
