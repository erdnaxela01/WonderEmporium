#include "LightingSystem.h"

namespace WE
{
    //set the renderer
    LightingSystem::LightingSystem(DeferedRenderer* renderer) :m_Renderer(renderer)
    {

    }

    //notify the lighting system of a new scene
    void LightingSystem::NotifyActiveScene(Scene* scene)
    {
        //remove all the ligths
        for (int32 i = m_Lights.Size() - 1; i >= 0; i--)
        {
            m_Lights.PopBack();
        }

        ArrayList<Entity*>* entities = scene->GetEntities();

        //loop through all the lights and add the ones with a light component
        for (uint32 i = 0; i < entities->Size(); i++)
        {
            if ((*entities)[i]->HasType<LightComponent>())
            {
                m_Lights.PushBack((*entities)[i]->GetComponent<LightComponent>());
            }
        }
    }

    //return the callbacks of the system
    std::vector<SystemCallback*> LightingSystem::GetCallbacks()
    {
        return{ New SystemCallback(&LightingSystem::Render, this) };
    }


    void LightingSystem::Render()
    {
        //make sure the lights will work and render the lights
        m_Renderer->LightingPass();
        for (uint32 i = 0; i < m_Lights.Size(); i++)
        {
            m_Lights[i]->Render(m_Renderer);
        }
    }
}