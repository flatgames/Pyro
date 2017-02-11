#ifndef __PYRO_ANIMATIONS_RESIZETO_H__
#define __PYRO_ANIMATIONS_RESIZETO_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Animations
	{

		class ResizeTo : public cocos2d::ActionInterval
		{
			typedef cocos2d::ActionInterval Super;

		public:
			static ResizeTo * create(float duration, const cocos2d::Size &size);

		public:
			ResizeTo(void);
			virtual ~ResizeTo(void);

			virtual cocos2d::ActionInterval * reverse(void) const override;

			virtual cocos2d::ActionInterval * clone(void) const override;

			virtual void startWithTarget(cocos2d::Node *target) override;

			virtual void update(float time) override;

		protected:
			virtual bool init(float duration, const cocos2d::Size &size);

		protected:
			cocos2d::Size _fromSize;
			cocos2d::Size _toSize;
			cocos2d::Size _sizeSpan;
		};

	} //namespace Pyro::Animations

} //namespace Pyro

#endif//__PYRO_ANIMATIONS_RESIZETO_H__
