#include "Entity.h"
#include "Core.h"

namespace WE
{

	Entity::Entity(const char* name) :m_Name(name)
	{
        
	}

    Entity::~Entity() 
    {
        
    }

	const char* Entity::Name()
	{
		return m_Name.c_str();
	}
}