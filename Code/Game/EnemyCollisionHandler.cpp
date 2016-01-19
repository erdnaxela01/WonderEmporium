#include "EnemyCollisionHandler.h"
#include  "EnemyPool.h"

namespace Game
{
    EnemyCollisionHandler::EnemyCollisionHandler(Player* player, EnemyPool* enemies, CameraLogic* camera) :
        m_Player(player), m_Enemies(enemies), m_Camera(camera)
    {

    }

    EnemyCollisionHandler::~EnemyCollisionHandler()
    {

    }

    //handle the collision of the player and the entity
    void EnemyCollisionHandler::HandleCollision(WE::Entity* you, WE::Entity* other)
    {
        if (other->HasType<CollisionTag>() && *other->GetComponent<CollisionTag>() == CollisionTag::PlayerTag)
        {
            m_Player->ResetPosition();
            m_Enemies->ResetPositions();
            m_Camera->SetState(CameraLogic::OverTheShoulderState);
            m_Player->GetEntity()->GetComponent<PlayerLogic>()->SetControls(PlayerLogic::OverTheShoulder);
        }
    }
}