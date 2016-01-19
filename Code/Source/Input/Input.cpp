#include "Input.h"

namespace WE
{
    Data::Data() :m_PlaceHolder(nullptr)
    {

    }

    Data::~Data()
    {
        
        SafeDelete(m_PlaceHolder);
           
        
    }

    Data::Data(Data&& d)
    {
        m_PlaceHolder = d.m_PlaceHolder;
        d.m_PlaceHolder = nullptr;
    }

    Data& Data::operator=(Data&& d)
    {
        m_PlaceHolder = d.m_PlaceHolder;
        d.m_PlaceHolder = nullptr;
        return *this;
    }

    Data::PlaceHolder::~PlaceHolder()
    {

    }
}