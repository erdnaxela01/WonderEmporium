#ifndef __LIGHT_COMPONENT_H
#define __LIGHT_COMPONENT_H

#include "MyLibs\OpenGL\ShaderProgram.h"
#include "Movement\TransformComponent.h"
#include "MyLibs\OpenGL\DeferedRenderer.h"
#include "Core\Entity.h"

namespace WE
{
    //this is the base class for lights
    //the render function must be implemented
    class LightComponent
    {
    public:
        LightComponent(const char* vert, const char* frag);

        //enable the light
        void Enable();

        //disable the light
        void Disable();

        //render the light
        virtual void Render(DeferedRenderer* renderer) = 0;


    protected:
        ShaderProgram m_Program;

    private:
        bool m_Enabled;
    };
}


#endif //__LIGHT_COMPONENT_H