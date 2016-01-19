#ifndef __CAMERA_COLLISION_HANDLER_H
#define __CAMERA_COLLISION_HANDLER_H

#include "../Source/Core/Entity.h"
#include "../Source/Movement/TransformComponent.h"
#include "../Source/Collision/CollisionHandler.h"
#include "CameraLogic.h"
#include "CollisionTag.h"
#include "Camera.h"

namespace Game
{
    //handles the collision of the player against other things, does nothing right now
    class PlayerCollisionHandler : public WE::CollisionHandler
    {
    public:
        PlayerCollisionHandler();
        virtual ~PlayerCollisionHandler();

        //handle the collisions between objects
        void HandleCollision(WE::Entity* you, WE::Entity* other);
    private:
        

    };
}

#endif //__CAMERA_COLLISION_HANDLER_H