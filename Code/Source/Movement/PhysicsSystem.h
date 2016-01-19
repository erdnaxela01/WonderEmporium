#ifndef __PHYSICS_SYSTEM_H
#define __PHYSICS_SYSTEM_H

#include "Core\Core.h"
#include "Time\Timer.h"
#include "PhysicsComponent.h"
#include "Scene\Scene.h"

namespace WE
{
    //this is the physics system
    //it will handle the physics world provided by bullet
    //all collisions and collision responses are handled by bullet
	class PhysicsSystem
	{
	public:
		PhysicsSystem();

		//non copyable
		PhysicsSystem(PhysicsSystem&) = delete;
		PhysicsSystem(PhysicsSystem&&) = delete;
		PhysicsSystem& operator=(PhysicsSystem&) = delete;
		PhysicsSystem& operator=(PhysicsSystem&&) = delete;


		virtual ~PhysicsSystem();

		//functions that need to be implemented
		void NotifyActiveScene(Scene* scene);

		std::vector<SystemCallback*> GetCallbacks();

		static const unsigned int PHYSICS_SYSTEM_MAX_SUBSTEP;

	private:
		//steps the physics
		void StepPhysics();

		Timer m_Timer;

		ArrayList<PhysicsComponent*> m_Components;
		btDefaultCollisionConfiguration* m_Configuration;
		btCollisionDispatcher* m_Dispatch;
		btBroadphaseInterface* m_Broadphase;
		btSequentialImpulseConstraintSolver* m_Solver;
		btDiscreteDynamicsWorld* m_World;
	};
}


#endif //__PHYSICS_SYSTEM_H