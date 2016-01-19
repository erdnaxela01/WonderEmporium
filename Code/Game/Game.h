#ifndef __GAME_H
#define __GAME_H

#include "../Source/Scene/Scene.h"
#include "../Source/Movement/RigidBodyComponent.h"
#include "../Source/Rendering/ModelComponent.h"
#include "../Source/Rendering/RenderSystem.h"
#include "../Source/Rendering/ParentNode.h"

#include "../Source/Rendering/DirectionalLight.h"
#include "../Source/Rendering/PointLight.h"
#include "../Source/Rendering/LabelComponent.h"
#include "../Source/Rendering/ParticleEmitter.h"
#include "../Source/Rendering/DirectionalLight.h"

#include "Player.h"
#include "Platform.h"
#include "Camera.h"
#include "EnemyPool.h"

namespace Game
{
    //this is the core scene of the game, it initializes everything in the game
	class GameScene : public WE::Scene
	{
	public:
		GameScene();

		virtual ~GameScene();

		void LoadContent();

        void Add(WE::Entity* entity);

		WE::SceneGraphComponent* GetSceneGraph();
	private:
        Player m_Player;
		Platform m_Platform;
        Camera m_Camera;
        EnemyPool m_Enemies;

		WE::Entity m_Graph;
		WE::Entity m_DirectionalLight;
        WE::Entity m_LabelEntity;

		WE::SceneGraphComponent m_SceneGraph;
		WE::DirectionalLight m_Light;

        WE::LabelComponent m_Label;
	};
}


#endif //__GAME_H