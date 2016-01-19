#include "CameraComponent.h"
#include "RenderState.h"

namespace WE
{
    const float CameraComponent::CAMERA_COMPONENT_DEFAULT_FOV = 3.14f / 2.0f;
    const vec2f CameraComponent::CAMERA_COMPONENT_DEFAULT_DEPTH = vec2f(1.0f, 100000.0f);

    CameraComponent::CameraComponent() : m_FOV(CAMERA_COMPONENT_DEFAULT_FOV),
        m_Depth(CAMERA_COMPONENT_DEFAULT_DEPTH)
	{
		m_WorldSize = Config::WINDOW_SIZE;
		m_ScreenSize = vec2f(1.0f, 1.0f);
        m_RealScreenSize = Config::WINDOW_SIZE;
	}


	void CameraComponent::SetScreenPosition(vec2f pos)
	{
		m_ScreenPositon = pos;
	}
	vec2f CameraComponent::GetScreenPosition()
	{
		return m_ScreenPositon;
	}
	void CameraComponent::SetScreenSize(vec2f size)
	{
		m_ScreenSize = size;
	}
	vec2f CameraComponent::GetScreenSize()
	{
		return m_ScreenSize;
	}
	void CameraComponent::SetWorldSize(vec2f size)
	{
		m_WorldSize = size;
	}
	vec2f CameraComponent::GetWorldSize()
	{
		return m_WorldSize;
	}

    //set the depth of the camera
    void CameraComponent::SetDepth(vec2f depth)
    {
        m_Depth = depth;
    }
    //get the depth of the camera
    vec2f CameraComponent::GetDepth()
    {
        return m_Depth; 
    }

    //set the field of vision
    //takes an angle in radians
    void CameraComponent::SetFieldOfVision(float f)
    {
        m_FOV = f;
    }
    //return the field of vision
    float CameraComponent::GetFieldOfVision()
    {
        return m_FOV;
    }

	void CameraComponent::View(RenderState* program)
	{
		//set the viewport
        glViewport(static_cast<int>(m_ScreenPositon.x* m_RealScreenSize.x), static_cast<int>(m_ScreenPositon.y* m_RealScreenSize.y), static_cast<int>(m_ScreenSize.x* m_RealScreenSize.x), static_cast<int>(m_ScreenSize.y* m_RealScreenSize.y));

        float aspect = (m_WorldSize.x) / (m_WorldSize.y);
        mat4f::Frustum(aspect, m_Depth.x, m_Depth.y, m_FOV, &program->stack->Top(), true);

	}

    //set the screen size in pixels
    void CameraComponent::SetRealScreenSize(vec2f size)
    {
        m_RealScreenSize = size;
    }
    //return the size of the camera in pixels
    vec2f CameraComponent::GetRealScreenSize()
    {
        return m_RealScreenSize;
    }
}