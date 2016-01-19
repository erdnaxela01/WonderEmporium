#ifndef __SCENE_H
#define __SCENE_H

#include "Core\Entity.h"

namespace WE
{
    //this will hold entities in order for the systems to be able to use them
	class Scene
	{
	public:
		//set the name of the scene
		Scene(const char* name);

		virtual~Scene() {};

		//return all the entities
		ArrayList<Entity*>* GetEntities();

		//add an entity to the scene
		void AddEntity(Entity* entity);

		//remove an entity from the scene
		void RemoveEntity(Entity* entity);
		
		//get the name of the scene
		std::string Name();

		//must be overriden
		virtual void LoadContent() = 0;

        //find an entity, gets done in Linear time
        bool Find(std::string name, Entity*& entity);

	private:
		friend class SceneManagerSystem;

		const std::string m_Name;

		ArrayList<Entity*> m_Entities;

		static SceneManagerSystem* s_Manager;

		bool m_Loaded;

	};
}


#endif //__SCENE_H