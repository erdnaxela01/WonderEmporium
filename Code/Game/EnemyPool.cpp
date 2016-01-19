#include "EnemyPool.h"
#include "Game.h"

using namespace WE;

namespace Game
{
    const std::array<const char*, ENEMY_POOL_NUM_MODELS> EnemyPool::MODEL_PATHS = { "BattleDroid.obj", "gazelle.obj", "sphere.obj" };
    const std::array<vec3f, ENEMY_POOL_NUM_MODELS> EnemyPool::ENEMY_SIZE = { vec3f(2.0, 2.0, 2.0), vec3f(0.6f, 0.6f, 0.6f) * 2.0f, vec3f(0.5f, 0.5f, 0.5f) };
    const std::array<vec3f, ENEMY_POOL_NUM_MODELS> EnemyPool::ENEMY_MODEL_SIZE = { vec3f(2.0, 2.0, 2.0), vec3f(0.6f, 0.6f, 0.6f) * Config::s_PPM, vec3f(0.5f, 0.5f, 0.5f) * Config::s_PPM };

	EnemyPool::EnemyPool()
	{
	}
	EnemyPool::~EnemyPool()
	{
		for (uint32 i = 0; i < m_Enemies.size(); i++)
		{
			SafeDelete(m_Enemies[i]);
		}
	}

	//add them to the scene
	void EnemyPool::Add(GameScene* game)
	{
		//add all the enemies to the scene
		for (uint32 i = 0; i < m_Enemies.size(); i++)
		{
			game->Add(m_Enemies[i]->GetEntity());
		}
	}

    void EnemyPool::Create(unsigned int size, vec3f tunnel, Player* player, EnemyPool* enemies, CameraLogic* camera)
	{
		m_Enemies.reserve(size);

		//create all the enemies
		for (uint32 i = 0; i < size; i++)
		{
			uint32 index = rand() % ENEMY_POOL_NUM_MODELS;
			m_Enemies.push_back(New Enemy(MODEL_PATHS[index], ENEMY_SIZE[index],ENEMY_MODEL_SIZE[index], tunnel, size, i, player, enemies, camera));
		}
        m_EnemyCount = size;
        m_TunnelSize = tunnel;
	}

    void EnemyPool::ResetPositions()
    {
        //resets the position of the enemies
        for (uint32 i = 0; i < m_Enemies.size(); i++)
        {
            m_Enemies[i]->InitialisePosition(m_TunnelSize, vec3f(0.0f, 0.0f, 0.0f), m_EnemyCount, i);
        }
    }
}