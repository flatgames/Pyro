#ifndef __PYRO_SHADOW_SHADOWLAYER_H__
#define __PYRO_SHADOW_SHADOWLAYER_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Shadow
	{

		class ShadowSprite;
		struct ShadowConfig;

		// Represents the shadow layer of a paper components.
		// THIS CLASS IS FOR INTERNAL USE ONLY
		class ShadowLayer : public cocos2d::Node
		{
			typedef cocos2d::Node Super;

		public:
			static ShadowLayer * create(const cocos2d::Size &size, int depth);

		protected:
			static void initConfigs(void);

		public:
			ShadowLayer(void);
			virtual ~ShadowLayer(void);

			virtual void setContentSize(const cocos2d::Size &size) override;

		protected:
			virtual bool init(const cocos2d::Size &size, int depth);

		public:
			virtual int getDepth(void) const;
			virtual void setDepth(int depth);
			virtual void changeDepth(int depth, float duration);

		protected:
			int currentDepth;
			ShadowSprite *topShadow;
			ShadowSprite *bottomShadow;

		protected:
			static const int MAX_SHADOW_CONFIG;
			static bool configReady;
			static ShadowConfig topShadowConfigs[];
			static ShadowConfig bottomShadowConfigs[];
		};

	} //namespace Pyro::Shadow

} //namespace Pyro

#endif//__PYRO_SHADOW_SHADOWLAYER_H__
