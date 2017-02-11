#include "Common.h"
#include <cocos2d.h>

namespace Pyro
{
	const char *Common::RESOURCES_FILE = "pyrores.plist";
	
	void Common::initResources(void)
	{
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Common::RESOURCES_FILE);
	}
}
