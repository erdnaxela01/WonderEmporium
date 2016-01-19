#include "SceneManagerSystem.h"
#include "Scene.h"
#include "SceneObserver.h"

namespace WE
{
	SceneManagerSystem::SceneManagerSystem()
	{
		Scene::s_Manager = this;
	}

	SceneManagerSystem::~SceneManagerSystem()
	{
		for (auto i : m_Scenes)
		{
            SafeDelete(i.second);
		}
        
        for (uint32 i = 0; i < m_Observers.Size(); i++)
        {
            SafeDelete(m_Observers[i]);
        }
	}

	//adds a scene to the active scene stack
	void SceneManagerSystem::PushScene(std::string name)
	{
		//add the scene with the specific name
		m_ActiveScenes.push(m_Scenes.at(name));
		if (m_ActiveScenes.top()->m_Loaded == false)
		{
			m_ActiveScenes.top()->LoadContent();
			m_ActiveScenes.top()->m_Loaded = true;
		}
		NotifyObservers();
	}

	//removes the top scene from the active scene stack
	void SceneManagerSystem::PopScene()
	{
		if (m_ActiveScenes.empty())
		{
			return;
		}
		//remove the active scene
		m_ActiveScenes.pop();
		NotifyObservers();
		
	}

	//returns the top scene of the stack
	Scene& SceneManagerSystem::GetActiveScene()
	{
		return *m_ActiveScenes.top();
	}

	//returns a scene with the specified name
	Scene& SceneManagerSystem::GetScene(std::string name)
	{
		return *m_Scenes.at(name);
	}

	//refreshes the scene of all its components
	void SceneManagerSystem::RefreshScene()
	{
		NotifyObservers();
	}

	//adds a scene to the scenes pool
	void SceneManagerSystem::AddScene(Scene* scene)
	{
		m_Scenes[scene->Name()] = scene;
	}

	//removes a scene form the scenes pool
	void SceneManagerSystem::RemoveScene(Scene* scene)
	{
		//find the scene, if its there, remove it
		auto iter = m_Scenes.find(scene->Name());
		if (iter != m_Scenes.end())
		{
            SafeDelete(m_Scenes.at(scene->Name()));
			m_Scenes.erase(iter);
		}
	}

	//does nothing
	std::vector<SystemCallback*> SceneManagerSystem::GetCallbacks()
	{
		return {};
	}

	//notify all the observers
	void SceneManagerSystem::NotifyObservers()
	{
		//if there is an active scene notify
		if (!m_ActiveScenes.empty())
		{
			for (int i = 0; i < m_Observers.Size(); i++)
			{
				m_Observers[i]->NotifyActiveScene(m_ActiveScenes.top());
			}
		}
	}
}