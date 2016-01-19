#ifndef __LIGHTING_SYSTEM_H
#define __LIGHTING_SYSTEM_H

#include "MyLibs\OpenGL\DeferedRenderer.h"
#include "LightComponent.h"
#include "Scene\Scene.h"
#include "Core\Core.h"

namespace WE
{
    //this will render all the light components
    //it is a system that gets passed to the core
    class LightingSystem
    {
    public:
        //set the renderer
        LightingSystem(DeferedRenderer* renderer);

        //notify the lighting system of a new scene
        void NotifyActiveScene(Scene* scene);

        //return the callbacks of the system
        std::vector<SystemCallback*> GetCallbacks();


    private:
        void Render();

        ArrayList<LightComponent*, 20> m_Lights;
        DeferedRenderer* m_Renderer;

    };
}

#endif //__LIGHTING_SYSTEM_H