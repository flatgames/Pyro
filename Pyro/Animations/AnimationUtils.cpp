#include "AnimationUtils.h"

using namespace cocos2d;

namespace Pyro
{
	namespace Animations
	{
		ActionInterval * AnimationUtils::create_xFromTo(Node *node, float from, float to, float time, int tag)
		{
			auto action = MoveTo::create(time, Vec2(to, node->getPositionY()));
			action->setTag(tag);

			node->setPositionX(from);
			return action;
		}

		ActionInterval * AnimationUtils::create_yFromTo(Node *node, float from, float to, float time, int tag)
		{
			auto action = MoveTo::create(time, Vec2(node->getPositionX(), to));
			action->setTag(tag);

			node->setPositionY(from);
			return action;
		}

		ActionInterval * AnimationUtils::create_xyFromTo(Node *node, const Vec2 &from, const Vec2 &to, float time, int tag)
		{
			auto action = MoveTo::create(time, to);
			action->setTag(tag);

			node->setPosition(from);
			return action;
		}

		ActionInterval * AnimationUtils::create_fadeOut(Node *node, float time, int tag)
		{
			auto action = FadeOut::create(time);
			action->setTag(tag);

			node->setOpacity(255);
			return action;
		}

		ActionInterval * AnimationUtils::create_fadeIn(Node *node, float time, int tag)
		{
			auto action = FadeIn::create(time);
			action->setTag(tag);

			node->setOpacity(0);
			return action;
		}

		ActionInterval * AnimationUtils::create_fadeFromTo(Node *node, GLubyte from, GLubyte to, float time, int tag)
		{
			auto action = FadeTo::create(time, to);
			action->setTag(tag);

			node->setOpacity(from);
			return action;
		}

		ActionInterval * AnimationUtils::create_scaleFromTo(Node *node, float from, float to, float time, int tag)
		{
			auto action = ScaleTo::create(time, to);
			action->setTag(tag);

			node->setScale(from);
			return action;
		}

		ActionInterval * AnimationUtils::create_scaleFromTo(Node *node, const Vec2 &from, const Vec2 &to, float time, int tag)
		{
			auto action = ScaleTo::create(time, to.x, to.y);
			action->setTag(tag);

			node->setScale(from.x, from.y);
			return action;
		}

		ActionInterval * AnimationUtils::create_tintFromTo(Node *node, const Color3B &from, const Color3B &to, float time, int tag)
		{
			auto action = TintTo::create(time, to.r, to.g, to.b);
			action->setTag(tag);

			node->setColor(from);
			return action;
		}
	}
}
