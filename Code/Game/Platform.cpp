#include "Platform.h"
#include "Game.h"

using namespace WE;

namespace Game
{
	const Platform::PlatformValues Platform::PLATFORM_VALUES = { vec2f(0.6f, 0.6f), 0.001f};
	static const unsigned int BLOCK_COUNT = 8;


	Platform::Platform() :m_Platform("Platform"),
		m_Model(""),
		m_Position()
	{
		m_Platform.AddComponent(&m_Model);
		m_Platform.AddComponent(&m_Position);
		m_Parent = New ParentNode(&m_Platform);
		m_Platform.AddComponent(m_Parent);
	}

	Platform::~Platform()
	{
		SafeDelete(m_Parent);

		for (uint32 i = 0; i < m_Pieces.size(); i++)
		{
			SafeDelete(m_Pieces[i]);
		}


        for (uint32 i = 0; i < MaxEvents; i++)
        {
            SafeDelete(m_Events[i]);
        }
	}

    void Platform::CreatePlatform(vec3f size, CameraLogic* logic, PlayerLogic* playerLogic)
	{
		//Set the top of the platform
		m_Pieces.reserve(BLOCK_COUNT);

		//left piece
		m_Pieces.emplace_back();
		m_Pieces.back() = New PlatformPiece(vec3f(size.x*0.5f * (1.0f - PLATFORM_VALUES.holePercentage.x)*0.5f,
			size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f, size.z* 0.5f));
		m_Parent->AddChild(m_Pieces.back()->GetEntity());

		PlatformPiece* piece = m_Pieces.back();
		float val = size.x*0.5f;
		val -= (size.x *0.5f* (1.0f - PLATFORM_VALUES.holePercentage.x))*0.5f;
        piece->GetBody()->SetPosition(vec3f(-val, -size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f, 0.0f) / Config::s_PPM);

		//right piece
		m_Pieces.emplace_back();
		m_Pieces.back() = New PlatformPiece(vec3f(size.x *0.5f* (1.0f - PLATFORM_VALUES.holePercentage.x)*0.5f,
            size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f, size.z * 0.5f));
		m_Parent->AddChild(m_Pieces.back()->GetEntity());

		piece = m_Pieces.back();
        piece->GetBody()->SetPosition(vec3f(val, -size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f, 0.0f) / Config::s_PPM);

		//top piece
		m_Pieces.emplace_back();
		m_Pieces.back() = New PlatformPiece(vec3f(size.x  * 0.5f* PLATFORM_VALUES.holePercentage.x,
            size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f,
			size.z *0.5f * (1.0f - PLATFORM_VALUES.holePercentage.y)*0.5f));

		piece = m_Pieces.back();
		val = size.z *0.5f;
		val -= size.z *0.5f* (1.0f - PLATFORM_VALUES.holePercentage.y)*0.5f;
        piece->GetBody()->SetPosition(vec3f(0.0f, -size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f, val) / Config::s_PPM);

		//bottom piece
		m_Pieces.emplace_back();
		m_Pieces.back() = New PlatformPiece(vec3f(size.x * 0.5f* PLATFORM_VALUES.holePercentage.x,
            size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f,
			size.z *0.5f * (1.0f - PLATFORM_VALUES.holePercentage.y)*0.5f));

		piece = m_Pieces.back();
        piece->GetBody()->SetPosition(vec3f(0.0f, -size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage * 0.5f, -val) / Config::s_PPM);

        //Left tunnel piece
        m_Pieces.emplace_back();
        m_Pieces.back() = New PlatformPiece(vec3f(size.x*0.5f * (1.0f - PLATFORM_VALUES.holePercentage.x)*0.5f,
            size.y * 0.5f * (1.0 - PLATFORM_VALUES.platformWidthToHeigthPercentage),
            size.z * 0.5f* PLATFORM_VALUES.holePercentage.x));

        float xVal = size.x * 0.5f * PLATFORM_VALUES.holePercentage.x;
        xVal += size.x*0.5f * (1.0f - PLATFORM_VALUES.holePercentage.x)*0.5f;

        float yVal = size.y * 0.5f * (1.0 - PLATFORM_VALUES.platformWidthToHeigthPercentage);
        yVal += size.y * PLATFORM_VALUES.platformWidthToHeigthPercentage;


        piece = m_Pieces.back();
        piece->GetBody()->SetPosition(vec3f(xVal, -yVal, 0.0f) / Config::s_PPM);


        //right tunnel piece
        m_Pieces.emplace_back();
        m_Pieces.back() = New PlatformPiece(vec3f(size.x*0.5f * (1.0f - PLATFORM_VALUES.holePercentage.x)*0.5f,
            size.y * 0.5f * (1.0 - PLATFORM_VALUES.platformWidthToHeigthPercentage),
            size.z * 0.5f* PLATFORM_VALUES.holePercentage.x));




        piece = m_Pieces.back();
        piece->GetBody()->SetPosition(vec3f(-xVal, -yVal, 0.0f) / Config::s_PPM);

        //Top tunnel piece
        m_Pieces.emplace_back();
        m_Pieces.back() = New PlatformPiece(vec3f(size.x*0.5f * (PLATFORM_VALUES.holePercentage.x),
            size.y * 0.5f * (1.0 - PLATFORM_VALUES.platformWidthToHeigthPercentage),
            size.z * 0.5f* (1.0 - PLATFORM_VALUES.holePercentage.x) * 0.5f));

        float zVal = size.z * 0.5f * PLATFORM_VALUES.holePercentage.y;
        zVal+= size.z*0.5f * (1.0f - PLATFORM_VALUES.holePercentage.y)*0.5f;


        piece = m_Pieces.back();
        piece->GetBody()->SetPosition(vec3f(0.0, -yVal, zVal) / Config::s_PPM);

        //back tunnel piece
        m_Pieces.emplace_back();
        m_Pieces.back() = New PlatformPiece(vec3f(size.x*0.5f * (PLATFORM_VALUES.holePercentage.x),
            size.y * 0.5f * (1.0 - PLATFORM_VALUES.platformWidthToHeigthPercentage),
            size.z * 0.5f* (1.0 - PLATFORM_VALUES.holePercentage.x) * 0.5f));


        piece = m_Pieces.back();
        piece->GetBody()->SetPosition(vec3f(0.0, -yVal, -zVal) / Config::s_PPM);

		//add all the nodes
		for (uint32 i = 0; i < m_Pieces.size(); i++)
		{
			m_Parent->AddChild(m_Pieces[i]->GetEntity());
		}


        //set up the camera transition event boxes
        m_Events[Events::CameraShiftEvent] = New EventBox(vec3f(size.x * PLATFORM_VALUES.holePercentage.x, 1000.0f, size.z * PLATFORM_VALUES.holePercentage.y), logic, playerLogic);

        m_Events[Events::WinEvent] = New EventBox(vec3f(size.x * PLATFORM_VALUES.holePercentage.x, 1000.0f, size.z * PLATFORM_VALUES.holePercentage.y), logic, playerLogic);
        m_Events[Events::WinEvent]->GetEntity()->GetComponent<TransformComponent>()->SetPosition(vec3f(0.0f,  -size.y -500.0f, 0.0f) / Config::s_PPM);
        m_Events[Events::WinEvent]->GetEntity()->GetComponent<EventCollisionHandler>()->SetCameraState(CameraLogic::OverTheShoulderState);

        m_Parent->AddChild(m_Events[Events::CameraShiftEvent]->GetEntity());
        m_Parent->AddChild(m_Events[Events::WinEvent]->GetEntity());

        //Find using a parent node
        //For high level development
        WE::Entity* entity;
        if (m_Parent->Find("Event Box0", entity))
        {
            entity->GetComponent<TransformComponent>()->SetPosition(vec3f(0.0f, 500.0f, 0.0f) / Config::s_PPM);
            entity->GetComponent<EventCollisionHandler>()->SetCameraState(CameraLogic::TransitionState);
        }

        m_TunnelSize = size;
        m_TunnelSize.x = size.x * PLATFORM_VALUES.holePercentage.x;
        m_TunnelSize.z = size.z * PLATFORM_VALUES.holePercentage.y;
        m_TunnelSize.y = size.y;

        //create the beams
        m_Beams.Create(m_TunnelSize, 3);

	}



	void Platform::AddToScene(GameScene* game)
	{
		game->GetSceneGraph()->AddChild(&m_Platform);
		game->Add(&m_Platform);

		for (uint32 i = 0; i < m_Pieces.size(); i++)
		{
			game->AddEntity(m_Pieces[i]->GetEntity());
		}


        for (uint32 i = 0; i < MaxEvents; i++)
        {
            game->AddEntity(m_Events[i]->GetEntity());
        }

        m_Beams.AddToGame(game);
	}

    WE::Entity* Platform::GetEntity()
    {
        return &m_Platform;
    }
	WE::ParentNode* Platform::GetNode()
	{
		return m_Parent;
	}

    vec3f Platform::TunnelDimensions()
    {
        return m_TunnelSize;
    }

    

    
}