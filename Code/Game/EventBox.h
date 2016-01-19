#ifndef __EVENT_BOX_H
#define __EVENT_BOX_H

#include "../Source/Core/Entity.h"
#include "../Source/Movement/RigidBodyComponent.h"
#include "../Source/Rendering/ModelComponent.h"
#include "../Source/Rendering/Node.h"
#include "EventCollisionHandler.h"

namespace Game
{
    //this is an event box, when the player collides with this an event happens
    //Like the camera changing position
    class EventBox
    {
    public:
        EventBox(vec3f size, CameraLogic* logic, PlayerLogic* playerLogic);
        virtual ~EventBox();

        WE::Entity* GetEntity();
    private:
        WE::Entity m_Event;
        WE::RigidBodyComponent m_Box;
        WE::ModelComponent m_Model;
        WE::Node* m_Node;

        EventCollisionHandler m_Handler;
    };
}

#endif //__EVENT_BOX_H