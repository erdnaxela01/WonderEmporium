#include "Camera.h"

namespace Game
{
    Camera::Camera(WE::TransformComponent* playerComponent) :m_Camera("Camera"),
        m_Logic(&m_CameraTransform, playerComponent)
    {
        m_Camera.AddComponent(&m_CameraComponent);
        m_Camera.AddComponent(&m_CameraTransform);
        m_Camera.AddComponent(&m_Logic);
        assert(playerComponent != nullptr);
    }
    Camera::~Camera()
    {

    }

    WE::Entity* Camera::GetEntity()
    {
        return &m_Camera;
    }
}