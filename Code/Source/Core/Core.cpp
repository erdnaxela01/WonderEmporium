#include "Core.h"


namespace WE
{

    Core::Core() : m_Exiting(false)
    {
        Config::LoadConfig();
    }

    Core::~Core()
    {
		for (unsigned int i = 0; i < m_Callbacks.size(); i++)
		{
			
            SafeDelete(m_Callbacks[i]);
			
		}
    }

    void Core::Loop()
    {
        //loop through all the callbacks and call them
		for (unsigned int i = 0; i < m_Callbacks.size(); i++)
        {
            m_Callbacks[i]->Execute();
        }
    }

    bool Core::Exiting()
    {
        return m_Exiting;
    }

    void Core::SetExit(bool b)
    {
        m_Exiting = b;
    }
}