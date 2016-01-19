#ifndef __ENEMY_POOL_H
#define __ENEMY_POOL_H

#include "Enemy.h"
#include <array>

namespace Game
{
	class GameScene;

	static const unsigned int ENEMY_POOL_NUM_MODELS = 3;

    //this class holds all of the enemies and sets them all up at the very start of the game
	class EnemyPool
	{
	public:
		EnemyPool();
		virtual ~EnemyPool();

		//add them to the scene
		void Add(GameScene* game);

        void Create(unsigned int size, vec3f tunnel, Player* player, EnemyPool* enemies, CameraLogic* camera);

        void ResetPositions();
	private:
		static const std::array<const char*, ENEMY_POOL_NUM_MODELS> MODEL_PATHS;
		static const std::array<vec3f, ENEMY_POOL_NUM_MODELS>  ENEMY_SIZE;
        static const std::array<vec3f, ENEMY_POOL_NUM_MODELS>  ENEMY_MODEL_SIZE;


        unsigned int m_EnemyCount;
        vec3f m_TunnelSize;
		std::vector<Enemy*> m_Enemies;
	};
}


#endif //__ENEMY_POOL_H