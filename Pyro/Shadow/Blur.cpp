#include "Blur.h"
#include "ShadowSprite.h"

using namespace cocos2d;

namespace Pyro
{
	namespace Shadow
	{

		Blur * Blur::create(float duration, float fromRadius, float toRadius)
		{
			auto action = new Blur();
			if (action && action->init(duration, fromRadius, toRadius))
			{
				action->autorelease();
				return action;
			}
			CC_SAFE_DELETE(action);
			return nullptr;
		}

		Blur::Blur(void)
			: _fromRadius(0), _toRadius(0)
		{
		}

		Blur::~Blur(void)
		{
		}

		ActionInterval * Blur::reverse(void) const
		{
			return Blur::create(_duration, _toRadius, _fromRadius);
		}

		ActionInterval * Blur::clone(void) const
		{
			return Blur::create(_duration, _fromRadius, _toRadius);
		}

		void Blur::startWithTarget(Node *target)
		{
			Super::startWithTarget(target);
			if (target)
			{
				if (_fromRadius < 0)
				{
					_fromRadius = static_cast<ShadowSprite *>(target)->getBlurRadius();
					_radiusSpan = _toRadius - _fromRadius;
				}
				else
				{
					static_cast<ShadowSprite *>(target)->setBlurRadius(_fromRadius);
				}
			}
		}

		void Blur::update(float time)
		{
			if (_target)
				static_cast<ShadowSprite *>(_target)->setBlurRadius(_fromRadius + _radiusSpan * time);
		}

		bool Blur::init(float duration, float fromRadius, float toRadius)
		{
			if (!Super::initWithDuration(duration))
				return false;

			_fromRadius = fromRadius;
			_toRadius = toRadius;
			_radiusSpan = toRadius - fromRadius;
			return true;
		}

	} //namespace Pyro::Shadow
} //namespace Pyro
