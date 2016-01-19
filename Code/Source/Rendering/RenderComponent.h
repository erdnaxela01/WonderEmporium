#ifndef __RENDER_COMPONENT_H
#define __RENDER_COMPONENT_H

#include "RenderState.h"
#include "MyLibs\OpenGL\Model.h"

namespace WE
{

    //this is the base class for a rendering components
	class RenderComponent
	{
	public:
        
		virtual ~RenderComponent() {};

		//render a sprite
        virtual void Render(RenderState* state) = 0;

		//set the state of the render component
        virtual void SetState(RenderState* state) = 0;

	private:

	};
}

#endif //__RENDER_COMPONENT_H