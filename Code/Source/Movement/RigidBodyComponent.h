#ifndef __RIGID_BODY_COMPONENT_H
#define __RIGID_BODY_COMPONENT_H

#include "PhysicsComponent.h"

namespace WE
{
    //this is a rigid body, this means that the object collides against things and reacts to weak forces like gravity
    class RigidBodyComponent : public PhysicsComponent
    {
    public:
        RigidBodyComponent(float mass, btMotionState* motion, btCollisionShape* collision, vec3f inertia = vec3f(0.0f, 0.0f, 0.0f));

        virtual ~RigidBodyComponent();
		
		//get the body
        btRigidBody& GetRigidBody();

        void AddToWorld(btDynamicsWorld* world) override;

		//remove the body from the world
		void RemoveFromWorld(btDynamicsWorld* world) override;
    private:
        btMotionState* m_Motion;
        btCollisionShape* m_Shape;
    };
}

#endif //__RIGID_BODY_COMPONENT