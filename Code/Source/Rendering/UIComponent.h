#ifndef __UI_COMPONENT_H
#define __UI_COMPONENT_H

#include "MyLibs\OpenGL\UniformBuffer.h"
#include "MyLibs\OpenGL\ShaderProgram.h"

namespace WE
{
    //this will be used to render things in the ui as a ui element
    class UIComponent
    {
    public:
        UIComponent(const char* vert = "UIShader.vert", const char* frag = "UIShader.frag");

        virtual ~UIComponent();

        //set the normalized screen position of the ui object
        void SetScreenPosition(vec2f position);

        //get the normalized screen position of the object
        vec2f GetScreenPosition();

        //render the ui ob=ject
        virtual void Render(UniformBuffer* buffer);


    protected:
        ShaderProgram m_Program;
    private:
        vec2f m_ScreenPosition;
    };
}

#endif //__UI_COMPONENT_H