#ifndef __PYRO_SHADOW_SHADOWLAYERNEW_H__
#define __PYRO_SHADOW_SHADOWLAYERNEW_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Shadow
	{

		struct ShadowConfig;

		// Represents the shadow layer of a paper components.
		// THIS CLASS IS FOR INTERNAL USE ONLY
		class ShadowLayer : public cocos2d::SpriteBatchNode
		{
			typedef cocos2d::SpriteBatchNode Super;

		protected:
			class PseudoNode;

		public:
			static ShadowLayer * create(const cocos2d::Size &size, int depth);

		protected:
			static void initConfigs(void);

		public:
			ShadowLayer(void);
			virtual ~ShadowLayer(void);

			virtual void onExit(void) override;
			virtual void update(float dt) override;
			virtual void setContentSize(const cocos2d::Size &size) override;

		protected:
			virtual bool init(const cocos2d::Size &size, int depth);

		public:
			virtual int getDepth(void) const;
			virtual void setDepth(int depth);
			virtual void changeDepth(int depth, float duration);

		protected:
			int currentDepth;
			PseudoNode *topShadow;
			PseudoNode *bottomShadow;
			bool animating;

		protected:
			static const int MAX_SHADOW_CONFIG;
			static bool configReady;
			static ShadowConfig topShadowConfigs[];
			static ShadowConfig bottomShadowConfigs[];
		};

	} //namespace Pyro::Shadow

} //namespace Pyro

#endif//__PYRO_SHADOW_SHADOWLAYERNEW_H__
