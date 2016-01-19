#ifndef __ENEMY_COLLISION_HANDLER_H
#define __ENEMY_COLLISION_HANDLER_H

#include "../Source/Collision/CollisionHandler.h"
#include "Player.h"
#include "CameraLogic.h"

namespace Game
{
    class EnemyPool;

    //this is used by the enemy, it tells the enemy when he is collided against and handles the
    //logic associated with the collision
    class EnemyCollisionHandler : public WE::CollisionHandler
    {
    public:
        EnemyCollisionHandler(Player* player, EnemyPool* enemies,CameraLogic* camera);

        virtual ~EnemyCollisionHandler();

        //handle the collision of the player and the entity
        void HandleCollision(WE::Entity* you, WE::Entity* other) override;
    private:
        Player* m_Player;
        EnemyPool* m_Enemies;
        CameraLogic* m_Camera;
    };
}

#endif //__ENEMY_COLLISION_HANDLING