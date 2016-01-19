#include "PhysicsSystem.h"
#include "Scene\Scene.h"

namespace WE
{
	const unsigned int PhysicsSystem::PHYSICS_SYSTEM_MAX_SUBSTEP = 10;

	PhysicsSystem::PhysicsSystem()
	{
		m_Configuration = New btDefaultCollisionConfiguration();

		m_Dispatch = New btCollisionDispatcher(m_Configuration);

		m_Broadphase = New btDbvtBroadphase();

		m_Solver = New btSequentialImpulseConstraintSolver();

		//create the world
		m_World = New btDiscreteDynamicsWorld(m_Dispatch, m_Broadphase, m_Solver, m_Configuration);

        m_World->setGravity(btVector3(0.0f, -9.8f, 0.0f));
		//set the interval time
		m_Timer.SetInterval(1.0 / static_cast<double>(Config::s_PhysicsFPS));
	}

	PhysicsSystem::~PhysicsSystem()
	{
		SafeDelete(m_World);
        SafeDelete(m_Solver);
        SafeDelete(m_Broadphase);
        SafeDelete(m_Dispatch);
        SafeDelete(m_Configuration);
	}

	void PhysicsSystem::NotifyActiveScene(Scene* scene)
	{

		//remove all the components
		ArrayList<Entity*>* entities = scene->GetEntities();

		for (int i = m_Components.Size() - 1; i >= 0; i--)
		{
			m_Components.Back()->RemoveFromWorld(m_World);
			m_Components.PopBack();
		}
		for (uint32 i = 0; i < entities->Size(); i++)
		{
			Entity* entity = (*entities)[i];

			if (entity->HasType<PhysicsComponent>())
			{
				PhysicsComponent* p = entity->GetComponent<PhysicsComponent>();

                p->AddToWorld(m_World);
				m_Components.PushBack(p);
			}

		}

	}

	std::vector<SystemCallback*> PhysicsSystem::GetCallbacks()
	{
		return{ New SystemCallback(&PhysicsSystem::StepPhysics, this) };
	}

	void PhysicsSystem::StepPhysics()
	{
		//if the timer is passed an interva
		if (m_Timer.PassedInterval())
		{
			//simulate the world
			m_World->stepSimulation(m_Timer.GetInterval(), PHYSICS_SYSTEM_MAX_SUBSTEP);
		}
	}
}