#ifndef __PYRO_ANIMATIONUTILS_H__
#define __PYRO_ANIMATIONUTILS_H__

#include <cocos2d.h>

namespace Pyro
{
	namespace Animations
	{
		class AnimationUtils
		{
		private:
			static cocos2d::ActionInterval * create_xFromTo(cocos2d::Node *node, float from, float to, float time, int tag = 0);
			static cocos2d::ActionInterval * create_yFromTo(cocos2d::Node *node, float from, float to, float time, int tag = 0);
			static cocos2d::ActionInterval * create_xyFromTo(cocos2d::Node *node, const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, float time, int tag = 0);

			static cocos2d::ActionInterval * create_fadeOut(cocos2d::Node *node, float time, int tag = 0);
			static cocos2d::ActionInterval * create_fadeIn(cocos2d::Node *node, float time, int tag = 0);
			static cocos2d::ActionInterval * create_fadeFromTo(cocos2d::Node *node, GLubyte from, GLubyte to, float time, int tag = 0);

			static cocos2d::ActionInterval * create_scaleFromTo(cocos2d::Node *node, float from, float to, float time, int tag = 0);
			static cocos2d::ActionInterval * create_scaleFromTo(cocos2d::Node *node, const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, float time, int tag = 0);

			static cocos2d::ActionInterval * create_tintFromTo(cocos2d::Node *node, const cocos2d::Color3B &from, const cocos2d::Color3B &to, float time, int tag = 0);

			static cocos2d::Action * ifDelay(float delay, cocos2d::ActionInterval *action, int tag)
			{
				cocos2d::Action *result;
				if (delay > 0)
					result = cocos2d::Sequence::createWithTwoActions(cocos2d::DelayTime::create(delay), action);
				else
					result = action;

				result->setTag(tag);
				return result;
			}

			template<typename EasingClass>
			static cocos2d::Action * ifDelay(float delay, cocos2d::ActionInterval *action, int tag)
			{
				cocos2d::Action *result;
				if (delay > 0)
					result = cocos2d::Sequence::createWithTwoActions(cocos2d::DelayTime::create(delay), EasingClass::create(action));
				else
					result = EasingClass::create(action);

				result->setTag(tag);
				return result;
			}

		public:
			static void xFromTo(cocos2d::Node *node, float from, float to, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_xFromTo(node, from, to, time), tag));
			}

			template<typename EasingClass>
			static void xFromTo(cocos2d::Node *node, float from, float to, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_xFromTo(node, from, to, time), tag));
			}

			static void yFromTo(cocos2d::Node *node, float from, float to, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_yFromTo(node, from, to, time), tag));
			}

			template<typename EasingClass>
			static void yFromTo(cocos2d::Node *node, float from, float to, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_yFromTo(node, from, to, time), tag));
			}

			static void xyFromTo(cocos2d::Node *node, const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_xyFromTo(node, from, to, time), tag));
			}

			template<typename EasingClass>
			static void xyFromTo(cocos2d::Node *node, const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_xyFromTo(node, from, to, time), tag));
			}

			static void fadeOut(cocos2d::Node *node, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_fadeOut(node, time), tag));
			}

			template<typename EasingClass>
			static void fadeOut(cocos2d::Node *node, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_fadeOut(node, time), tag));
			}

			static void fadeIn(cocos2d::Node *node, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_fadeIn(node, time), tag));
			}

			template<typename EasingClass>
			static void fadeIn(cocos2d::Node *node, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_fadeIn(node, time), tag));
			}

			static void fadeFromTo(cocos2d::Node *node, GLubyte from, GLubyte to, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_fadeFromTo(node, from, to, time), tag));
			}

			template<typename EasingClass>
			static void fadeFromTo(cocos2d::Node *node, GLubyte from, GLubyte to, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_fadeFromTo(node, from, to, time), tag));
			}

			static void scaleFromTo(cocos2d::Node *node, float from, float to, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_scaleFromTo(node, from, to, time), tag));
			}

			template<typename EasingClass>
			static void scaleFromTo(cocos2d::Node *node, float from, float to, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_scaleFromTo(node, from, to, time), tag));
			}

			static void scaleFromTo(cocos2d::Node *node, const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_scaleFromTo(node, from, to, time), tag));
			}

			template<typename EasingClass>
			static void scaleFromTo(cocos2d::Node *node, const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_scaleFromTo(node, from, to, time), tag));
			}

			static void tintFromTo(cocos2d::Node *node, const cocos2d::Color3B &from, const cocos2d::Color3B &to, float time, float delay = -1.f, int tag = 0)
			{
				node->runAction(ifDelay(delay, create_tintFromTo(node, from, to, time), tag));
			}

			template<typename EasingClass>
			static void tintFromTo(cocos2d::Node *node, const cocos2d::Color3B &from, const cocos2d::Color3B &to, float time, float delay = -1.f, int tag = 0)
			{
				static_assert(std::is_convertible<EasingClass *, cocos2d::ActionEase *>::value, "EasingClass must be an easing action.");
				node->runAction(ifDelay<EasingClass>(delay, create_tintFromTo(node, from, to, time), tag));
			}

			static void stopByTag(cocos2d::Node *node, int tag)
			{
				node->stopActionByTag(tag);
			}

			static void runWithDelay(cocos2d::Node *node, float delay, const std::function<void(void)> &runnable, int tag = 0)
			{
				auto action = cocos2d::Sequence::createWithTwoActions(
					cocos2d::DelayTime::create(delay),
					cocos2d::CallFunc::create(runnable));
				action->setTag(tag);

				node->runAction(action);
			}
		};

		class AnimatingElement
		{
		public:
			const int tagAnimatingAction = 19734658;

		protected:
			bool _isAnimating;

		public:
			AnimatingElement(void) :_isAnimating(false) { }

		protected:
			inline cocos2d::Action * startAnimating(float duration, cocos2d::Node *actionNode)
			{
				this->_isAnimating = true;

				auto action = cocos2d::Sequence::createWithTwoActions(
					cocos2d::DelayTime::create(duration),
					cocos2d::CallFunc::create(CC_CALLBACK_0(AnimatingElement::setAnimating, this, false)));
				action->setTag(tagAnimatingAction);

				this->setAnimating(true);
				actionNode->runAction(action);

				return action;
			}

		public:
			inline bool isAnimating(void) const
			{
				return _isAnimating;
			}

			inline void setAnimating(bool value)
			{
				_isAnimating = value;
			}
		};
	}
}

#endif//__PYRO_ANIMATIONUTILS_H__
