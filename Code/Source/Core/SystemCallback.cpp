#include "SystemCallback.h"

namespace WE
{

    SystemCallback::~SystemCallback()
    {
        //delete the callback
        
        SafeDelete(m_Callback);
            
    }

    void SystemCallback::Execute()
    {
        //call the callback
        m_Callback->Execute();
    }

    SystemCallback::SystemCallback(SystemCallback&& sys)
    {
        //set the system callback to null and take it
        this->m_Callback = sys.m_Callback;
        sys.m_Callback = nullptr;
    }
}