#include "EventCollisionHandler.h"
#include "CollisionTag.h"
#include "Player.h"

namespace Game
{
    EventCollisionHandler::EventCollisionHandler(CameraLogic* logic, PlayerLogic* playerLogic) :m_Camera(logic), m_Player(playerLogic)
    {

    }

    void EventCollisionHandler::HandleCollision(WE::Entity* you, WE::Entity* other)
    {
        if (other->HasType<CollisionTag>() && *other->GetComponent<CollisionTag>() == PlayerTag)
        {
            if (m_CameraState!=CameraLogic::OverTheShoulderState && m_Camera->GetState() == CameraLogic::OverTheShoulderState)
            {
                m_Camera->SetState(m_CameraState);
                m_Player->SetControls(PlayerLogic::TopDown);
            }

			else if (m_CameraState == CameraLogic::OverTheShoulderState && m_Camera->GetState() == CameraLogic::TopDownState)
            {
                m_Camera->SetState(m_CameraState);
				m_Player->SetControls(PlayerLogic::OverTheShoulder);
                other->GetComponent<PlayerLogic>()->ResetPosition();
                other->GetComponent<Player::Score>()->AddScore(1);
            }
            
        }
    }

    void EventCollisionHandler::SetCameraState(CameraLogic::CameraLogicState state)
    {
        m_CameraState = state;
    }
}