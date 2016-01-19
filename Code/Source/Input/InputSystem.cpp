#include "InputSystem.h"
#include "MyLibs\OpenGL\Window.h"
#include "Scene\Scene.h"


namespace WE
{
    static InputSystem* s_Input;

    InputSystem::InputSystem()
    {
        //set the send input callback
        SetEventCallback(&InputSystem::SendInput);
        s_Input = this;

        //load the map
        m_Map.LoadMap(Config::INPUT_SYSTEM_LL_PATH);


    }
    //notify of a new component
    void InputSystem::NotifyActiveScene(Scene* scene)
    {

		//remove all the components
		ArrayList<Entity*>* entities = scene->GetEntities();

		for (int i = m_Handlers.Size() - 1; i >= 0; i--)
		{
			m_Handlers.PopBack();
		}
		for (uint32 i = 0; i < entities->Size(); i++)
		{

			Entity* entity = (*entities)[i];
			InputHandler* hand = entity->GetComponent<InputHandler>();
			//if there is an input handler add it to the handlers
			//make sure we dont add it twice
			if (hand != nullptr)
			{
				m_Handlers.PushBack(hand);
			}

		}
    }


    //give the core our callbacks
    std::vector<SystemCallback*> InputSystem::GetCallbacks()
    {
        return{};
    }

    LRESULT InputSystem::SendInput(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Input in;
        //convert the input
        switch (uMsg)
        {
        case WM_KEYDOWN:
            in.name = s_Input->m_Map.Convert(wParam);
            in.data.Create(new std::string("KeyDown"));
            break;
        case WM_KEYUP:
            in.name = s_Input->m_Map.Convert(wParam);
            in.data.Create(new std::string("KeyUp"));
            break;
        }
        if (in.name != "")
        {
            //send the input to all the input handlers
            for (uint32 i = 0; i < s_Input->m_Handlers.Size(); i++)
            {
                s_Input->m_Handlers[i]->ReceiveInput(std::move(in));
            }
        }
        //return the default
        return DefaultEventHandling(hWnd, uMsg, wParam, lParam);
    }

}