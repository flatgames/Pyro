#ifndef __PYRO_SHADOW_BLUR_H__
#define __PYRO_SHADOW_BLUR_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Shadow
	{

		class Blur : public cocos2d::ActionInterval
		{
			typedef cocos2d::ActionInterval Super;

		public:
			static Blur * create(float duration, float fromRadius, float toRadius);

		public:
			Blur(void);
			virtual ~Blur(void);

			virtual cocos2d::ActionInterval * reverse(void) const override;

			virtual cocos2d::ActionInterval * clone(void) const override;

			virtual void startWithTarget(cocos2d::Node *target) override;

			virtual void update(float time) override;

		protected:
			virtual bool init(float duration, float fromRadius, float toRadius);

		protected:
			float _fromRadius;
			float _toRadius;
			float _radiusSpan;
		};

	} //namespace Pyro::Shadow

} //namespace Pyro

#endif//__PYRO_SHADOW_BLUR_H__
