#include "SceneObserver.h"

namespace WE
{
	SceneObserver::~SceneObserver()
	{
		//delete the holder
		
        SafeDelete(m_Holder);
			
		
	}

	//notify of a new active scene
	void SceneObserver::NotifyActiveScene(Scene* scene)
	{
		//begin the notifying process
		m_Holder->NotifyActiveScene(scene);
	}

	void* SceneObserver::GetAddress()
	{
		return m_Holder->GetAddress();
	}
}