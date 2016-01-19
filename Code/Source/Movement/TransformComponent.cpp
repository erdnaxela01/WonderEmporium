#include "TransformComponent.h"

namespace WE
{

    TransformComponent::TransformComponent() :m_Scale(vec3f(1.0f, 1.0f, 1.0f)), m_Rotation(vec3f(0.0f, 0.0f, 0.0f))
	{
		
	}


	void TransformComponent::SetPosition(vec3f pos)
	{
		m_Position = pos;
	}
	vec3f TransformComponent::GetPosition()
	{
		return m_Position;
	}
    void TransformComponent::SetRotation(vec3f rotation)
	{
		m_Rotation = rotation;
	}
    vec3f TransformComponent::GetRotation()
	{
		return m_Rotation;
	}
	void TransformComponent::SetScale(vec3f scale)
	{
		m_Scale = scale;
	}
	vec3f TransformComponent::GetScale()
	{
		return m_Scale;
	}

	mat4f TransformComponent::GetTransform()
	{
		//create a matrix and get the transform
		mat4f trans;
        mat4f::Transform(vec3f(-m_Position.x, m_Position.y, m_Position.z) * Config::s_PPM, m_Rotation.x, m_Rotation.y, m_Rotation.z, vec3f(m_Scale.x, m_Scale.y, m_Scale.z), &trans);
		return trans;
	}
	mat4f TransformComponent::GetInverse()
	{
		//create a matrix and get the inverse
		mat4f trans;
        mat4f::Inverse(vec3f(-m_Position.x, m_Position.y, m_Position.z) * Config::s_PPM, m_Rotation.x, m_Rotation.y, m_Rotation.z, vec3f(m_Scale.x, m_Scale.y, m_Scale.z), &trans);
		return trans;
	}
}