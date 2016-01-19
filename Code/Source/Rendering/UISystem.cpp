#include "UISytstem.h"

namespace WE
{
    UISystem::UISystem(Window* window) :
        m_Buffer(sizeof(float) * 4, UniformBuffer::Data({ std::make_pair("u_ScreenSize", sizeof(float) * 2), std::make_pair("u_ScreenPosition", sizeof(float) * 2 )}), "Screen"),
        m_ScreenSize(Config::WINDOW_SIZE), m_Window(window)
    {
        assert(window != nullptr);
    }

    UISystem::~UISystem()
    {

    }

    //return the loop callbacks
    std::vector<SystemCallback*> UISystem::GetCallbacks()
    {
        return{ new SystemCallback(&UISystem::Render, this) };
    }

    //notify about a new active scene
    void UISystem::NotifyActiveScene(Scene* scene)
    {
        //remove all the components
        for (int32 i = m_UIComponents.Size() - 1; i >= 0; i--)
        {
            m_UIComponents.PopBack();
        }

        ArrayList<Entity*>* entities = scene->GetEntities();

        //loop through and find all the ones with UI components
        for (uint32 i = 0; i < entities->Size(); i++)
        {
            if ((*entities)[i]->HasType<UIComponent>())
            {
                m_UIComponents.PushBack((*entities)[i]->GetComponent<UIComponent>());
            }
        }
    }

    //set the screen size
    void UISystem::SetScreenSize(vec2f size)
    {
        m_ScreenSize = size;
    }

    //return teh screen size
    vec2f UISystem::GetScreenSize()
    {
        return m_ScreenSize;
    }

    //render the UI
    void UISystem::Render()
    {
        //set up the buffer data and set the uniform buffer
        float arr[2];
        arr[0] = m_ScreenSize.x;
        arr[1] = m_ScreenSize.y;
        m_Buffer.SetUniform("u_ScreenSize", arr, 2, sizeof(float));
        for (uint32 i = 0; i < m_UIComponents.Size(); i++)
        {
            m_UIComponents[i]->Render(&m_Buffer);
        }
        m_Window->Display();
    }
}