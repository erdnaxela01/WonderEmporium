#ifndef __CORE_H
#define __CORE_H

#include "SystemVarying.h"
#include "Entity.h"

#include <vector>

namespace WE
{
    //this is the core class of the system
    //it will hold all the systems and invoke the appropriate callbacks
    class Core
    {
    public:
        //structors
        Core();
        virtual ~Core();

        //this will add a system to the system group
        template<typename system>
        void AddSystem(system* sys);

        //this will get called every loop
        void Loop();

        //returns a system based on the type asked for
        template<typename system>
        system* GetSystem();

        //say if the engine is exiting
        bool Exiting();

        //shuts down the engine
        void SetExit(bool b);
    private:
        //members
        std::vector<SystemVarying> m_Systems;
        std::vector<SystemCallback*> m_Callbacks;
        bool m_Exiting;

    };
    template<typename system>
    void Core::AddSystem(system* sys)
    {
        //get the callbacks from the system
        auto callbacks = sys->GetCallbacks();
        //reserve the space needed
        m_Callbacks.reserve(callbacks.size());
        //push back the callbacks into the callbacks vector
        for (uint32 i = 0; i < callbacks.size(); i++)
        {
            m_Callbacks.push_back(callbacks[i]);
        }
        //push back the system
        m_Systems.push_back(SystemVarying(sys));
    }


    template<typename system>
    system* Core::GetSystem()
    {
        //loop through all the systems
        for (int i = 0; i < m_Systems.size(); i++)
        {
            //if one of them matches the type return that one
            if (m_Systems[i].Match<system>())
            {
                return m_Systems[i].GetSystem<system>();
            }
        }
        return nullptr;
    }
}

#endif