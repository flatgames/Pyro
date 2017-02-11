#ifndef __PYRO_COMPONENTS_HELPERS_NORMALRECTANGLE_H__
#define __PYRO_COMPONENTS_HELPERS_NORMALRECTANGLE_H__

#include <cocos2d.h>

namespace Pyro
{

	namespace Components
	{

		namespace Helpers
		{

			// Represents a clipping rectangle with square corners.
			class NormalRectangle : public cocos2d::Node
			{
				typedef cocos2d::Node Super;

			public:
				static NormalRectangle * create(const cocos2d::Size &size);

			public:
				NormalRectangle(void);

				virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) override;

			protected:
				bool init(const cocos2d::Size &size);

			protected:
				cocos2d::CustomCommand beforeVisitCmdScissor;
				cocos2d::CustomCommand afterVisitCmdScissor;
				float viewScaleX, viewScaleY;
			};

		} //namespace Helpers

	} //namespace Components

} //namespace Pyro

#endif//__PYRO_COMPONENTS_HELPERS_NORMALRECTANGLE_H__
