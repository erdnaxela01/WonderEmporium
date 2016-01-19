#include "Enemy.h"
#include "EnemyPool.h"
#include <random>

using namespace WE;

namespace Game
{
    const double Enemy::TWEEN_TIME = 2.6f;

    Enemy::Enemy(std::string path, vec3f size,vec3f modelSize, vec3f tunnelSize, unsigned int count, unsigned int current, Player* player, EnemyPool* enemies, CameraLogic* camera) : m_Enemy("Enemy"),
        m_Model(path.c_str(),modelSize),
        m_Body(1, New btDefaultMotionState(), New btBoxShape(btVector3(size.x, size.y, size.z) / 2.0f)),
        m_Node(nullptr),
        m_Logic(&m_Body),
        m_Handler(player, enemies,camera)
        
    {
        m_Enemy.AddComponent(&m_Model);
        m_Enemy.AddComponent(&m_Body);

        m_Node = New Node(&m_Enemy);
        m_Enemy.AddComponent(m_Node);

        InitialisePosition(tunnelSize,size,count, current);
		m_Body.GetRigidBody().setLinearFactor(btVector3(1.0f, 0.0f, 1.0f));
		m_Body.GetRigidBody().setCollisionFlags(m_Body.GetRigidBody().getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

        m_Enemy.AddComponent(&m_Logic);
        m_Enemy.AddComponent(&m_Handler);
    }
    Enemy::~Enemy()
    {
        SafeDelete(m_Node);
    }

    WE::Entity* Enemy::GetEntity()
    {
        return &m_Enemy;
    }

	void Enemy::InitialisePosition(vec3f tunnelSize, vec3f enemySize, unsigned int count, unsigned int current)
    {
        //set the random position
        vec3f pos;
        pos.x = ((float)(rand() % 1000)) / 1000.0f;
		pos.x = ((tunnelSize.x - enemySize.x) / Config::s_PPM * pos.x) - ((tunnelSize.x - enemySize.x) / Config::s_PPM* 0.5f);

        pos.z = ((float)(rand() % 1000)) / 1000.0f;;
		pos.z = ((tunnelSize.z - enemySize.z) / Config::s_PPM* pos.z) - ((tunnelSize.z - enemySize.z) / Config::s_PPM* 0.5f);

        pos.y = ((float)(rand() % 1000)) / 1000.0f;
		pos.y = (tunnelSize.y / count)* pos.y;
		pos.y += (tunnelSize.y / count * current);
		pos.y /= Config::s_PPM;
        pos.y = -pos.y;

        vec3f end;
        end.x = ((float)(rand() % 1000)) / 1000.0f;
        end.x = ((tunnelSize.x - enemySize.x) / Config::s_PPM * end.x) - ((tunnelSize.x - enemySize.x) / Config::s_PPM* 0.5f);

        end.z = ((float)(rand() % 1000)) / 1000.0f;;
        end.z = ((tunnelSize.z - enemySize.z) / Config::s_PPM* end.z) - ((tunnelSize.z - enemySize.z) / Config::s_PPM* 0.5f);

        end.y = pos.y;

        m_Logic.SetStartAndEnd(pos, end);
        m_Logic.SetTime(TWEEN_TIME);
    }
}