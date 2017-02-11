#ifndef __PYRO_COMPONENTS_HELPERS_ROUNDEDRECTANGLE_H__
#define __PYRO_COMPONENTS_HELPERS_ROUNDEDRECTANGLE_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Components
	{

		namespace Helpers
		{

			// Represents a clipping rectangle with rounded corners.
			class RoundedRectangle : public cocos2d::ClippingNode
			{
				typedef cocos2d::ClippingNode Super;

			public:
				static RoundedRectangle * create(const cocos2d::Size &size);

			public:
				RoundedRectangle(void);

				void setContentSize(const cocos2d::Size &size) override;

				bool isUsingNinePatch(void) const;
				void setUsingNinePatch(bool value);

			protected:
				bool init(const cocos2d::Size &size);
				void createDrawNode(bool reuse);

			protected:
				bool usingNinePatch;
			};

		} //namespace Helpers

	} //namespace Components

} //namespace Pyro

#endif//__PYRO_COMPONENTS_HELPERS_ROUNDEDRECTANGLE_H__
