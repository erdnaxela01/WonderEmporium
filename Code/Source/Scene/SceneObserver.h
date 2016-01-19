#ifndef __SCENE_OBSERVER_H
#define __SCENE_OBSERVER_H

#include "Scene.h"
namespace WE
{
	//This class will get called whenever a new scene is at the top of the stack
	class SceneObserver
	{
	public:
		//create the observer holder
		template<typename type>
		SceneObserver(type* t);

		//delete the holder
		virtual ~SceneObserver();

		//cant copy
		SceneObserver(const SceneObserver& system) = delete;
		SceneObserver& operator=(const SceneObserver& system) = delete;
		SceneObserver(const SceneObserver&& system) = delete;
		SceneObserver& operator=(SceneObserver&& system) = delete;

		//notify of a new active scene
		void NotifyActiveScene(Scene* scene);

		//get the address of the held pointer
		void* GetAddress();
	private:
		struct PlaceHolder
		{
			//call the held type
			virtual void NotifyActiveScene(Scene* scene) = 0;

			virtual void* GetAddress() = 0;
		};


		template<typename type>
		struct Holder :public PlaceHolder
		{
			//call the function
			void NotifyActiveScene(Scene* scene) override;

			void* GetAddress() override;

			type* m_Inner;
		};

		PlaceHolder* m_Holder;

	};

	template<typename type>
	SceneObserver::SceneObserver(type* t)
	{
		//create the holder and store it
		Holder<type>* hold = New Holder<type>;
		hold->m_Inner = t;

		m_Holder = hold;
	}

	template<typename type>
	void SceneObserver::Holder<type>::NotifyActiveScene(Scene* scene)
	{
		//notify
		m_Inner->NotifyActiveScene(scene);
	}

	template<typename type>
	void* SceneObserver::Holder<type>::GetAddress()
	{
		//notify
		return m_Inner;
	}
}

#endif //__SCENE_OBSERVER_H