#include "Scene.h"
#include "SceneManagerSystem.h"


namespace WE
{
	SceneManagerSystem* Scene::s_Manager = nullptr;

	//set the name of the scene
	Scene::Scene(const char* name) :m_Loaded(false), m_Name(name)
	{
	}

	//return all the entities
	ArrayList<Entity*>* Scene::GetEntities()
	{
		return &m_Entities;
	}

	//add an entity to the scene
	void Scene::AddEntity(Entity* entity)
	{
		m_Entities.PushBack(entity);
	}

	//remove an entity from the scene
	void Scene::RemoveEntity(Entity* entity)
	{
		//loop through the entities and find the ones that match
		for (int i = 0; i < m_Entities.Size(); i++)
		{
			if (m_Entities[i] == entity)
			{
				std::swap(m_Entities[i], m_Entities.Back());
				m_Entities.PopBack();
			}
		}
		s_Manager->NotifyObservers();
	}

	//get the name of the scene
	std::string Scene::Name()
	{
		return m_Name;
	}

    bool Scene::Find(std::string name, Entity*& entity)
    {
        //loop through and find the entity
        for (uint32 i = 0; i < m_Entities.Size(); i++)
        {
            if (m_Entities[i]->Name() == name)
            {
                entity = m_Entities[i];
                return true;
            }
        }

        return false;
    }
}