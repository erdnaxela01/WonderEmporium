#include "SystemVarying.h"


namespace WE
{

    SystemVarying::~SystemVarying()
    {
        
        SafeDelete(m_PlaceHolder);
            
        
    }


    std::vector<SystemCallback*> SystemVarying::GetCallbacks()
    {
        return m_PlaceHolder->GetCallbacks();
    }

    SystemVarying::SystemVarying(SystemVarying&& system)
    {
        m_PlaceHolder = system.m_PlaceHolder;
        system.m_PlaceHolder = nullptr;
    }
}
