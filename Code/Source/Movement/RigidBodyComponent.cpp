#include "RigidBodyComponent.h"

namespace WE
{

    RigidBodyComponent::RigidBodyComponent(float mass, btMotionState* motion, btCollisionShape* collision, vec3f inertia) :
        PhysicsComponent(New btRigidBody(mass, motion, collision, btVector3(inertia.x, inertia.y, inertia.z))), m_Motion(motion), m_Shape(collision)
    {
        assert(motion != nullptr);
        assert(collision != nullptr);
    }

    btRigidBody& RigidBodyComponent::GetRigidBody()
    {
        return *dynamic_cast<btRigidBody*>(GetBody());
    }

    RigidBodyComponent::~RigidBodyComponent()
    {
        SafeDelete(m_Shape);
        SafeDelete(m_Motion);
    }

    void RigidBodyComponent::AddToWorld(btDynamicsWorld* world)
    {
        world->addRigidBody(&GetRigidBody());
    }

	void RigidBodyComponent::RemoveFromWorld(btDynamicsWorld* world)
	{
		world->removeRigidBody(&GetRigidBody());
	}
}