#include "EventBox.h"

using namespace WE;

namespace Game
{
    static int s_Count = 0;
    EventBox::EventBox(vec3f size, CameraLogic* logic, PlayerLogic* playerLogic) :m_Event((std::string("Event Box") + std::to_string(s_Count)).c_str()),
        m_Handler(logic, playerLogic),
        m_Box(0, New btDefaultMotionState(), New btBoxShape(btVector3(size.x, size.y, size.z) * 0.5f / Config::s_PPM)),
        m_Model("")
    {
        s_Count++;

        m_Event.AddComponent(&m_Handler);
        m_Event.AddComponent(&m_Box);
        m_Event.AddComponent(&m_Model);

        m_Node = New WE::Node(&m_Event);
        m_Event.AddComponent(m_Node);
        m_Box.GetBody()->setCollisionFlags(m_Box.GetBody()->getCollisionFlags() |
           btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
    EventBox::~EventBox()
    {
        SafeDelete(m_Node);
    }

    WE::Entity* EventBox::GetEntity()
    {
        return &m_Event;
    }
}