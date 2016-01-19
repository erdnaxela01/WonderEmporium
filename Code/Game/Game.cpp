#include "Game.h"
#include <ctime>
#include <random>

using namespace WE;

namespace Game
{
    GameScene::GameScene() :
		Scene("Game"),
		m_Graph("Scene"),
		m_Camera(m_Player.GetEntity()->GetComponent<TransformComponent>()),
		m_DirectionalLight("Directional Light"),
        m_Label(vec2f(20.0f, 20.0f), vec2i(9, 6), "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890,.:-<>!", "Font.png"),
        m_LabelEntity("Label"),
        m_Player(&m_Label)
	{

	}

	GameScene::~GameScene()
	{
		
		
			
		
	}

	void GameScene::LoadContent()
	{
		//seed the random number generator
		srand(time(0));

        //setup our entities
		m_Graph.AddComponent(&m_SceneGraph);

		m_SceneGraph.AddCamera(m_Camera.GetEntity());
        m_Platform.CreatePlatform(vec3f(1000.0f, 200000.0f, 1000.0f), m_Camera.GetEntity()->GetComponent<CameraLogic>(), m_Player.GetEntity()->GetComponent < PlayerLogic>());
		m_Enemies.Create(10, m_Platform.TunnelDimensions(), &m_Player, &m_Enemies, m_Camera.GetEntity()->GetComponent<CameraLogic>());


		m_DirectionalLight.AddComponent(&m_Light);
		m_Light.SetDirection(vec3f(1.0f, 0.0f, 0.0f));

        m_LabelEntity.AddComponent(&m_Label);
        m_Label.GetText().SetText("SCORE 0");
        m_Label.SetScreenPosition(vec2f(0.02f, 0.95f));

        //add the entities so the systems will know which entities to add to their records as the scenes change
		Add(&m_Graph);
		Add(&m_DirectionalLight);

        //added first due to the transparancy
        m_Platform.AddToScene(this);

        //add the player
        Add(m_Player.GetEntity());
        Add(&m_LabelEntity);

        //TODO: to avoid stuterring move this to a new final update iteration
        Add(m_Camera.GetEntity());

        //find the player using the scene graph and reset his position
        WE::Entity* entity;
        if (m_SceneGraph.Find("Player", entity))
        {
            entity->GetComponent<PlayerLogic>()->ResetPosition();
        }


		m_Enemies.Add(this);
	}

    void GameScene::Add(Entity* entity)

    {
        //add the node if it has one
        if (entity->HasType<Node>())
        {
            m_SceneGraph.AddChild(entity->GetComponent<Node>());
        }

        //add it to the pool
        AddEntity(entity);
    }

	WE::SceneGraphComponent* GameScene::GetSceneGraph()
	{
		return &m_SceneGraph;
	}
}