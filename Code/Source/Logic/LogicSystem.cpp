#include "LogicSystem.h"

namespace WE
{
    LogicSystem::LogicSystem()
    {
        m_Timer.SetInterval(1.0f / Config::s_LogicFPS);
    }

    LogicSystem::~LogicSystem()
    {

    }

    //return the update logic 
    std::vector<SystemCallback*> LogicSystem::GetCallbacks()
    {
        return{ New SystemCallback(&LogicSystem::UpdateLogic, this) };
    }

    //tell the system about a new scene
    void LogicSystem::NotifyActiveScene(Scene* scene)
    {
        ArrayList<Entity*>* entities = scene->GetEntities();

        //remove all the components
        for (int32 i = m_Logic.Size() - 1; i >= 0; i--)
        {
            m_Logic.PopBack();
        }

        //loop through all the entities and add the ones with logic components
        for (int32 i = 0; i < entities->Size(); i++)
        {
            if ((*entities)[i]->HasType<LogicComponent>())
            {
                m_Logic.PushBack((*entities)[i]->GetComponent<LogicComponent>());
            }
        }
    }

    //update the logic components
    void LogicSystem::UpdateLogic()
    {
        //if its time to update run through all the components and update them
        if (m_Timer.PassedInterval())
        {
            for (uint32 i = 0; i < m_Logic.Size(); i++)
            {
                m_Logic[i]->Update(m_Timer.GetInterval());
            }
        }
    }
}