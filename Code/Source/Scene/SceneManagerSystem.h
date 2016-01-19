#ifndef __SCENE_MANAGER_SYSTEM_H
#define __SCENE_MANAGER_SYSTEM_H

#include "Core\SystemCallback.h"
#include "Scene.h"
#include "SceneObserver.h"
#include <stack>
#include<map>

namespace WE
{
    //this will handle all the scenes giving them the option to add, remove and push and pop scenes
	class SceneManagerSystem
	{
	public:
		SceneManagerSystem();

		virtual ~SceneManagerSystem();

		//adds a scene to the active scene stack
		void PushScene(std::string name);

		//removes the top scene from the active scene stack
		void PopScene();
		
		//returns the top scene of the stack
		Scene& GetActiveScene();

		//returns a scene with the specified name
		Scene& GetScene(std::string name);

		//refreshes the scene of all its components
		void RefreshScene();

		//adds a scene observer to the scene manager
		template<typename type>
		void AddObserver(type* obs);

		//removes a scene observer from the scene mamager
		template<typename type>
		void RemoveObserver(type* obs);
		
		//adds a scene to the scenes pool
		void AddScene(Scene* scene);

		//removes a scene form the scenes pool
		void RemoveScene(Scene* scene);

		//does nothing
		std::vector<SystemCallback*> GetCallbacks();
		//notify all the observers
		void NotifyObservers();
	private:

		std::stack<Scene*> m_ActiveScenes;
		std::map<std::string, Scene*> m_Scenes;
		ArrayList<SceneObserver*, 15> m_Observers;

	};


	//adds a scene observer to the scene manager
	template<typename type>
	void SceneManagerSystem::AddObserver(type* obs)
	{
		m_Observers.PushBack(New SceneObserver(obs));
	}

	//removes a scene observer from the scene mamager
	template<typename type>
	void SceneManagerSystem::RemoveObserver(type* obs)
	{
		//loop through all the observers and if one matches the address remove it and delete it
		for (int i = 0; i < m_Observers.Size(); i++)
		{
			if (m_Observers[i]->GetAddress() == obs)
			{
				SafeDelete(m_Observers.Back());
				m_Observers.PopBack();
			}
		}
	}
}

#endif //__SCENE_MANAGER_SYSTEM_H