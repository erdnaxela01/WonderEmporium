#include "PhysicsComponent.h"


namespace WE
{
	PhysicsComponent::PhysicsComponent(btCollisionObject* obj) : m_Object(obj)
	{
		assert(obj != nullptr);
	}

	PhysicsComponent::~PhysicsComponent()
	{
        SafeDelete(m_Object);
	}

	//returns the body associated to the physics component
	btCollisionObject* PhysicsComponent::GetBody()
	{
		return m_Object;
	}

	//set the position of the transform component
	void  PhysicsComponent::SetPosition(vec3f pos)
	{
		m_Object->getWorldTransform().getOrigin().setX(pos.x);
		m_Object->getWorldTransform().getOrigin().setY(pos.y);
		m_Object->getWorldTransform().getOrigin().setZ(pos.z);
	}
	//get the position of the component
	vec3f  PhysicsComponent::GetPosition()
	{
		vec3f pos;
        pos.x = m_Object->getWorldTransform().getOrigin().getX();
		pos.y = m_Object->getWorldTransform().getOrigin().getY();
		pos.z = m_Object->getWorldTransform().getOrigin().getZ();
		return pos;
	}
	//set the rotation of the component
	void  PhysicsComponent::SetRotation(vec3f rotation)
	{
		m_Object->getWorldTransform().getBasis().setEulerZYX(rotation.x, rotation.y, rotation.z);
	}
	//get the rotation of the component
	vec3f PhysicsComponent::GetRotation()
	{
		vec3f rot;
		m_Object->getWorldTransform().getBasis().getEulerZYX(rot.x, rot.y, rot.z, 1);
		return rot;
	}

	//get the transform matrix
	mat4f PhysicsComponent::GetTransform()
	{
		mat4f trans;
		vec3f rot = GetRotation();
		vec3f pos = GetPosition();
		pos.x *= -1;

        mat4f::Transform(pos * Config::s_PPM, rot.x, rot.y, rot.z, GetScale(), &trans);
		return trans;
	}
	//get the inverse transform matrix
	mat4f  PhysicsComponent::GetInverse()
	{
		mat4f trans;
		vec3f rot = GetRotation();
		vec3f pos = GetPosition();
		pos.x *= -1;

        mat4f::Inverse(pos * Config::s_PPM, rot.x, rot.y, rot.z, GetScale(), &trans);
		return trans;
	}

    void  PhysicsComponent::AddToWorld(btDynamicsWorld* world)
    {
        world->addCollisionObject(m_Object);
    }

	void PhysicsComponent::RemoveFromWorld(btDynamicsWorld* world)
	{
		world->removeCollisionObject(m_Object);
	}


}