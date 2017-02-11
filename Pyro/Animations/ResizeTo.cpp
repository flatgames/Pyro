#include "ResizeTo.h"

using namespace cocos2d;

namespace Pyro
{
	namespace Animations
	{

		ResizeTo * ResizeTo::create(float duration, const Size &size)
		{
			auto action = new ResizeTo();
			if (action && action->init(duration, size))
			{
				action->autorelease();
				return action;
			}
			CC_SAFE_DELETE(action);
			return nullptr;
		}

		ResizeTo::ResizeTo(void)
		{
		}

		ResizeTo::~ResizeTo(void)
		{
		}

		ActionInterval * ResizeTo::reverse(void) const
		{
			return ResizeTo::create(_duration, _fromSize);
		}

		ActionInterval * ResizeTo::clone(void) const
		{
			return ResizeTo::create(_duration, _toSize);
		}

		void ResizeTo::startWithTarget(Node *target)
		{
			Super::startWithTarget(target);
			if (target)
			{
				_fromSize = target->getContentSize();
				_sizeSpan = _toSize - _fromSize;
			}
		}

		void ResizeTo::update(float time)
		{
			if (_target)
				_target->setContentSize(_fromSize + _sizeSpan * time);
		}

		bool ResizeTo::init(float duration, const Size &size)
		{
			if (!Super::initWithDuration(duration))
				return false;

			_toSize = size;
			return true;
		}

	} //namespace Pyro::Animations
} //namespace Pyro
