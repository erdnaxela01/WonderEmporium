#ifndef __CAMERA_H
#define __CAMERA_H

#include "CameraLogic.h"
#include "../Source/Rendering/CameraComponent.h"

namespace Game
{
    //this camera class will follow the player based on its state
    class Camera
    {
    public:
        Camera(WE::TransformComponent* playerComponent);
        virtual ~Camera();

        WE::Entity* GetEntity();
    private:
        WE::Entity m_Camera;
        WE::CameraComponent m_CameraComponent;
        WE::TransformComponent m_CameraTransform;
        
        CameraLogic m_Logic;
    };
}


#endif //__CAMERA_H