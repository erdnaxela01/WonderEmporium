#ifndef __INPUT_SYSTEM_H
#define __INPUT_SYSTEM_H

#include "Core\Entity.h"
#include "Core\SystemCallback.h"
#include "InputHandler.h"
#include "LLInputMap.h"
#include "Scene\Scene.h"

namespace WE
{
    //this is the input system, it will handle low level input, convert it to mid level input and send it to input handlers
    class InputSystem
    {
    public:
        //create
        InputSystem();
        //notify of a new component
        void NotifyActiveScene(Scene* scene);

        //give the core our callbacks
        std::vector<SystemCallback*> GetCallbacks();

        static LRESULT SendInput(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    private:
        ArrayList<InputHandler*> m_Handlers;
        LLInputMap m_Map;
    };
}


#endif //__INPUT_SYSTEM_H