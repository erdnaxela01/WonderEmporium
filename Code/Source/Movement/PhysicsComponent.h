#ifndef __PHYSICS_COMPONENT_H
#define __PHYSICS_COMPONENT_H

#include "TransformComponent.h"
#include "Core\Core.h"

namespace WE
{
    //this call will handle collision objects that arent rigid bodies
    //They are part of the bullet physics world
	class PhysicsComponent : public TransformComponent
	{
	public:
		PhysicsComponent(btCollisionObject* obj);

		PhysicsComponent(PhysicsComponent&) = delete;
		PhysicsComponent(PhysicsComponent&&) = delete;
		PhysicsComponent& operator=(PhysicsComponent&) = delete;
		PhysicsComponent& operator=(PhysicsComponent&&) = delete;

		virtual ~PhysicsComponent();

		//returns the body associated to the physics component
		btCollisionObject* GetBody();

		//set the position of the transform component
		void SetPosition(vec3f pos) override;
		//get the position of the component
		vec3f GetPosition() override;
		//set the rotation of the component
		void SetRotation(vec3f rotation);
		//get the rotation of the component
		vec3f GetRotation();

		//get the transform matrix
		mat4f GetTransform();
		//get the inverse transform matrix
		mat4f GetInverse();

		//add the body to the world
        virtual void AddToWorld(btDynamicsWorld* world);

		//remove the body from the world
		virtual void RemoveFromWorld(btDynamicsWorld* world);
	private:
		btCollisionObject* m_Object;
	};
}

#endif //__PHYSICS_COMPONENT_H