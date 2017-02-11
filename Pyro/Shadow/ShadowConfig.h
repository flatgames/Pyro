#ifndef __PYRO_SHADOW_SHADOWCONFIG_H__
#define __PYRO_SHADOW_SHADOWCONFIG_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Shadow
	{

		struct ShadowConfig
		{
			ShadowConfig(void)
				: Level(0), BlurRadius(0), OffsetY(0), Opacity(0)
			{
			}

			ShadowConfig(int level, float blurRadius, float offsetY, GLubyte opacity)
				: Level(level), BlurRadius(blurRadius), OffsetY(offsetY), Opacity(opacity)
			{
			}

			int Level;
			float BlurRadius;
			float OffsetY;
			GLubyte Opacity;
		};

	} //namespace Pyro::Shadow

} //namespace Pyro

#endif//__PYRO_SHADOW_SHADOWCONFIG_H__
