#ifndef __PLATFORM_H
#define __PLATFORM_H

#include "PlatformPiece.h"
#include "EventBox.h"
#include "Player.h"
#include "BeamPlatform.h"
#include "../Source/Core/Entity.h"
#include "../Source/Rendering/ModelComponent.h"
#include "../Source/Rendering/ParentNode.h"
#include "../Source/Movement/TransformComponent.h"

namespace Game
{
	class GameScene;

    //this class holds all the platform pieces in order to create the whole platform
    //it initializes the platforms positions
	class Platform
	{
	public:
        enum Events
        {
            CameraShiftEvent,
            WinEvent,
            MaxEvents,
        };

		Platform();

        //create the platform and events
        void CreatePlatform(vec3f size, CameraLogic* logic, PlayerLogic* playerLogic);

		virtual ~Platform();

		WE::ParentNode* GetNode();

		void AddToScene(GameScene* game);

        //get the dimensions of the tunnel
        vec3f TunnelDimensions();

        WE::Entity* GetEntity();

	private:

		struct PlatformValues
		{
			vec2f holePercentage;
			float platformWidthToHeigthPercentage;
		};

		static const PlatformValues PLATFORM_VALUES;

		std::vector<PlatformPiece*> m_Pieces;

		//components
		WE::Entity m_Platform;
		WE::ParentNode* m_Parent;
		WE::ModelComponent m_Model;
		WE::TransformComponent m_Position;

        EventBox* m_Events[MaxEvents];
        BeamPlatform m_Beams;

        vec3f m_TunnelSize;
        

	};
}

#endif //__PLATFORM_H