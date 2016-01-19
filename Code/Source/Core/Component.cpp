#include "Component.h"

namespace WE
{


    //destroy the vaying
    Component::~Component()
    {
        
        SafeDelete(m_PlaceHolder);
           
        
    }

    //can only move it
    Component::Component(Component&& c)
    {
        //set the other component value to null
        m_PlaceHolder = c.m_PlaceHolder;
        c.m_PlaceHolder = nullptr;
    }

    void* Component::GetAddress()
    {
        return m_PlaceHolder->GetAddress();
    }

    
}
