#ifndef __UI_SYSTEM_H
#define __UI_SYSTEM_H

#include "MyLibs\OpenGL\UniformBuffer.h"
#include "Core\SystemCallback.h"
#include "Scene\Scene.h"
#include "MyLibs\OpenGL\ShaderProgram.h"
#include "UIComponent.h"

namespace WE
{
    //this will use a forward rendering to draw things that are part of the ui
    class UISystem
    {
    public:
        UISystem(Window* window);

        virtual ~UISystem();

        //return the loop callbacks
        std::vector<SystemCallback*> GetCallbacks();

        //notify about a new active scene
        void NotifyActiveScene(Scene* scene);

        //set the screen size
        void SetScreenSize(vec2f size);

        //return teh screen size
        vec2f GetScreenSize();
    private:
        //render the UI
        void Render();

        UniformBuffer m_Buffer;
        vec2f m_ScreenSize;
        ArrayList<UIComponent*> m_UIComponents;
        Window* m_Window;
    };
}


#endif //__UI_SYSTEM_H