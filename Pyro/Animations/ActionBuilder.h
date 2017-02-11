#ifndef __PYRO_ACTIONBUILDER_H__
#define __PYRO_ACTIONBUILDER_H__

#include <cocos2d.h>
#include "ResizeTo.h"

namespace Pyro
{
	namespace Animations
	{
		class SequenceBuilder;
		class SpawnBuilder;
		class RepeatBuilder;

		class ActionBuilder
		{
		protected:
			cocos2d::Node *_target;
			cocos2d::Vector<cocos2d::FiniteTimeAction *> _actions;

			ActionBuilder *_parent;

		public:
			ActionBuilder(cocos2d::Node *target)
				: _target(target), _parent(nullptr)
			{
			}

			ActionBuilder(ActionBuilder *parent)
				: _target(parent->_target), _parent(parent)
			{
			}

			virtual ~ActionBuilder(void)
			{
			}

		public: // virtual methods
			virtual cocos2d::Action * create(void) = 0;

			template<typename T>
			T * createAs(void)
			{
				return static_cast<T *>(this->create());
			}

			virtual void run(int tag = 0, bool stopLast = false)
			{
				auto action = this->create();
				action->setTag(tag);

				if (stopLast)
					this->_target->stopActionByTag(tag);

				this->_target->runAction(action);
			}

		public: // opacity
			ActionBuilder & fadeTo(float duration, GLubyte opacity)
			{
				this->_actions.pushBack(cocos2d::FadeTo::create(duration, opacity));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & fadeTo(float duration, GLubyte opacity)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::FadeTo::create(duration, opacity)));
				return *this;
			}

			ActionBuilder & fadeIn(float duration)
			{
				this->_actions.pushBack(cocos2d::FadeIn::create(duration));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & fadeIn(float duration)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::FadeIn::create(duration)));
				return *this;
			}

			ActionBuilder & fadeOut(float duration)
			{
				this->_actions.pushBack(cocos2d::FadeOut::create(duration));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & fadeOut(float duration)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::FadeOut::create(duration)));
				return *this;
			}

		public: // tint
			ActionBuilder & tintTo(float duration, const cocos2d::Color3B &color)
			{
				this->_actions.pushBack(cocos2d::TintTo::create(duration, color.r, color.g, color.b));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & tintTo(float duration, const cocos2d::Color3B &color)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::TintTo::create(duration, color.r, color.g, color.b)));
				return *this;
			}

			ActionBuilder & tintTo(float duration, GLubyte red, GLubyte green, GLubyte blue)
			{
				this->_actions.pushBack(cocos2d::TintTo::create(duration, red, green, blue));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & tintTo(float duration, GLubyte red, GLubyte green, GLubyte blue)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::TintTo::create(duration, red, green, blue)));
				return *this;
			}

			ActionBuilder & tintBy(float duration, const cocos2d::Color3B &color)
			{
				this->_actions.pushBack(cocos2d::TintBy::create(duration, color.r, color.g, color.b));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & tintBy(float duration, const cocos2d::Color3B &color)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::TintBy::create(duration, color.r, color.g, color.b)));
				return *this;
			}

			ActionBuilder & tintBy(float duration, GLubyte red, GLubyte green, GLubyte blue)
			{
				this->_actions.pushBack(cocos2d::TintBy::create(duration, red, green, blue));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & tintBy(float duration, GLubyte red, GLubyte green, GLubyte blue)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::TintBy::create(duration, red, green, blue)));
				return *this;
			}

		public: // position
			ActionBuilder & moveTo(float duration, float x, float y)
			{
				this->_actions.pushBack(cocos2d::MoveTo::create(duration, cocos2d::Vec2(x, y)));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & moveTo(float duration, float x, float y)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::MoveTo::create(duration, cocos2d::Vec2(x, y))));
				return *this;
			}

			ActionBuilder & moveBy(float duration, float dx, float dy)
			{
				this->_actions.pushBack(cocos2d::MoveBy::create(duration, cocos2d::Vec2(dx, dy)));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & moveBy(float duration, float dx, float dy)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::MoveBy::create(duration, cocos2d::Vec2(dx, dy))));
				return *this;
			}

			ActionBuilder & moveXBy(float duration, float dx)
			{
				this->_actions.pushBack(cocos2d::MoveBy::create(duration, cocos2d::Vec2(dx, 0)));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & moveXBy(float duration, float dx)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::MoveBy::create(duration, cocos2d::Vec2(dx, 0))));
				return *this;
			}

			ActionBuilder & moveYBy(float duration, float dy)
			{
				this->_actions.pushBack(cocos2d::MoveBy::create(duration, cocos2d::Vec2(0, dy)));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & moveYBy(float duration, float dy)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::MoveBy::create(duration, cocos2d::Vec2(0, dy))));
				return *this;
			}

			ActionBuilder & place(float x, float y)
			{
				this->_actions.pushBack(cocos2d::Place::create(cocos2d::Vec2(x, y)));
				return *this;
			}

		public: // scale
			ActionBuilder & scaleTo(float duration, float scale)
			{
				this->_actions.pushBack(cocos2d::ScaleTo::create(duration, scale));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & scaleTo(float duration, float scale)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::ScaleTo::create(duration, scale)));
				return *this;
			}

			ActionBuilder & scaleTo(float duration, float scaleX, float scaleY)
			{
				this->_actions.pushBack(cocos2d::ScaleTo::create(duration, scaleX, scaleY));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & scaleTo(float duration, float scaleX, float scaleY)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::ScaleTo::create(duration, scaleX, scaleY)));
				return *this;
			}

			ActionBuilder & scaleBy(float duration, float scale)
			{
				this->_actions.pushBack(cocos2d::ScaleBy::create(duration, scale));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & scaleBy(float duration, float scale)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::ScaleBy::create(duration, scale)));
				return *this;
			}

			ActionBuilder & scaleBy(float duration, float scaleX, float scaleY)
			{
				this->_actions.pushBack(cocos2d::ScaleBy::create(duration, scaleX, scaleY));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & scaleBy(float duration, float scaleX, float scaleY)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::ScaleBy::create(duration, scaleX, scaleY)));
				return *this;
			}

			ActionBuilder & scaleXBy(float duration, float scaleX)
			{
				this->_actions.pushBack(cocos2d::ScaleBy::create(duration, scaleX, 1));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & scaleXBy(float duration, float scaleX)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::ScaleBy::create(duration, scaleX, 1)));
				return *this;
			}

			ActionBuilder & scaleYBy(float duration, float scaleY)
			{
				this->_actions.pushBack(cocos2d::ScaleBy::create(duration, 1, scaleY));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & scaleYBy(float duration, float scaleY)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(cocos2d::ScaleBy::create(duration, 1, scaleY)));
				return *this;
			}

		public: // timing
			ActionBuilder & repeatForever(cocos2d::ActionInterval *action)
			{
				this->_actions.pushBack(cocos2d::RepeatForever::create(action));
				return *this;
			}

			ActionBuilder & repeat(unsigned int times, cocos2d::FiniteTimeAction *action)
			{
				this->_actions.pushBack(cocos2d::Repeat::create(action, times));
				return *this;
			}

			ActionBuilder & delay(float duration)
			{
				this->_actions.pushBack(cocos2d::DelayTime::create(duration));
				return *this;
			}

		public: // miscellaneous
			ActionBuilder & resizeTo(float duration, const cocos2d::Size &size)
			{
				this->_actions.pushBack(ResizeTo::create(duration, size));
				return *this;
			}

			template<typename EasingAction>
			ActionBuilder & resizeTo(float duration, const cocos2d::Size &size)
			{
				static_assert(std::is_convertible<EasingAction *, cocos2d::ActionEase *>::value, "EasingAction must be an ActionEase.");
				this->_actions.pushBack(EasingAction::create(ResizeTo::create(duration, size)));
				return *this;
			}

			ActionBuilder & show(void)
			{
				this->_actions.pushBack(cocos2d::Show::create());
				return *this;
			}

			ActionBuilder & hide(void)
			{
				this->_actions.pushBack(cocos2d::Hide::create());
				return *this;
			}

			ActionBuilder & removeSelf(void)
			{
				this->_actions.pushBack(cocos2d::RemoveSelf::create());
				return *this;
			}

			ActionBuilder & call(const std::function<void(void)> &func)
			{
				this->_actions.pushBack(cocos2d::CallFunc::create(func));
				return *this;
			}

			ActionBuilder & with(cocos2d::FiniteTimeAction *action)
			{
				this->_actions.pushBack(action);
				return *this;
			}

		public: // branching
			SequenceBuilder beginSequence(void);
			SpawnBuilder beginSpawn(void);
			RepeatBuilder beginRepeat(void);

			ActionBuilder & endSequence(void)
			{
				return this->done();
			}

			ActionBuilder & endSpawn(void)
			{
				return this->done();
			}

			ActionBuilder & endRepeat(void)
			{
				return this->done();
			}

			ActionBuilder & done(void)
			{
				return this->_parent->with(this->createAs<cocos2d::FiniteTimeAction>());
			}
		};
	}
}

#endif//__PYRO_ACTIONBUILDER_H__
