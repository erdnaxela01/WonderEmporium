#ifndef __ENTITY_H
#define __ENTITY_H

#include "Component.h"

#include <vector>
#include <typeinfo>

namespace WE
{
    //this is the entity, it will hold components and doesnt do much more than that
    class Entity
    {
    public:
		//create an entity
		Entity(const char* name);

		virtual ~Entity();

        //this will add a component to the entity
        template<typename component>
        void AddComponent(component* c);

        //this will remove a component frrom the entity
        template<typename component>
        void RemoveComponent();

        //this will return the component of a specific type
        template<typename component>
        component* GetComponent();

        //this will check if the entity has any
        template<typename type>
        bool HasType();

		//return the name of the entity
		const char* Name();

        friend class Core;
    private:
        std::vector<Component> m_Components;
		std::string m_Name;
    };

    //this will check if the entity has any
    template<typename type>
    bool Entity::HasType()
    {
        for (unsigned int i = 0; i < m_Components.size(); i++)
        {
            if (m_Components[i].Match<type>())
            {
                return true;
            }
        }
        return false;
    }

    template<typename component>
    void Entity::AddComponent(component* c)
    {
        m_Components.push_back(Component(c));
        
    }

    template<typename component>
    void Entity::RemoveComponent()
    {
        //loop through all the components
        for (int i = 0; i < m_Components.size(); i++)
        {
            //if one of the components match swap it with the back and remove it
            if (m_Components[i].Match<component>())
            {
                std::swap(m_Components[i], m_Components.back());
                m_Components.pop_back();
				break;
            }
        }
    }

    template<typename component>
    component* Entity::GetComponent()
    {
        //loop through all the components
        for (unsigned int i = 0; i < m_Components.size(); i++)
        {
            //if the component matches return it
            if (m_Components[i].Match<component>())
            {
                return m_Components[i].GetComponent<component>();
            }
        }
        return nullptr;
    }
}
#endif