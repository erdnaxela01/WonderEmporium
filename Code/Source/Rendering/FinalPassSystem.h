#ifndef __FINAL_PASS_SYSTEM_H
#define __FINAL_PASS_SYSTEM_H

#include "MyLibs\OpenGL\DeferedRenderer.h"
#include "MyLibs\OpenGL\Window.h"
#include "Core\SystemVarying.h"

namespace WE
{
    //this class will finalize all the rendering
    class FinalPassSystem
    {
    public:
        //pass all the dependancies
        FinalPassSystem(DeferedRenderer* renderer);

        //return the render callback
        std::vector<SystemCallback*> GetCallbacks();

    private:
        //render the final pass
        void Render();

        DeferedRenderer* m_Renderer;
    };
}

#endif //__FINAL_PASS_H