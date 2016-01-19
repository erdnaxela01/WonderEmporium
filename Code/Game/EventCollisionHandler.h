#ifndef __EVENT_COLLISION_HANDLER_H
#define __EVENT_COLLISION_HANDLER_H

#include "../Source/Collision/CollisionHandler.h"
#include "CameraLogic.h"
#include "PlayerLogic.h"

namespace Game
{
    //this will handle the collision against the event box
    //it will handle the logic for this
    class EventCollisionHandler: public WE::CollisionHandler
    {
    public:
        EventCollisionHandler(CameraLogic* logic, PlayerLogic* playerLogic);
        virtual ~EventCollisionHandler() {};

        //handle the collisions between objects
        void HandleCollision(WE::Entity* you, WE::Entity* other);

        //set the state that camera will change to
        void SetCameraState(CameraLogic::CameraLogicState state);

    private:
        CameraLogic::CameraLogicState m_CameraState;
        CameraLogic* m_Camera;
        PlayerLogic* m_Player;

    };
}


#endif //__EVENT_COLLISION_HANDLER_H