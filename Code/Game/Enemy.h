#ifndef __ENEMY_H
#define __ENEMY_H

#include "../Source/Core/Entity.h"
#include "../Source/Movement/RigidBodyComponent.h"
#include "../Source/Rendering/ModelComponent.h"
#include "../Source/Rendering/Node.h"

#include "EnemyLogic.h"
#include "EnemyCollisionHandler.h"
#include "Player.h"

#include <string>

namespace Game
{
    class EnemyPool;

    //this is the enemy class, it will be in the tunnel and the player must avoid them
    class Enemy
    {
    public:
        Enemy(std::string path, vec3f size,vec3f modelSize, vec3f tunnelSize, unsigned int count, unsigned int current, Player* player, EnemyPool* enemies, CameraLogic* camera);
        virtual ~Enemy();

        WE::Entity* GetEntity();

        //set the position of the enemy
        void InitialisePosition(vec3f tunnelSize, vec3f enemySize, unsigned int count, unsigned int current);
    private:
        static const double TWEEN_TIME;

        //components
        WE::Entity m_Enemy;
        WE::RigidBodyComponent m_Body;
        WE::ModelComponent m_Model;
        WE::Node* m_Node;

        EnemyLogic m_Logic;
        EnemyCollisionHandler m_Handler;

    };

}

#endif //__ENEMY_H