#ifndef __PLATFORM_PIECE_H
#define __PLATFORM_PIECE_H

#include "../Source/Core/Entity.h"
#include "../Source/Rendering/Node.h"
#include "../Source/Rendering/ModelComponent.h"
#include "../Source/Collision/CollisionHandler.h"
#include "../Source/Movement/RigidBodyComponent.h"

#include "CollisionTag.h"

namespace Game
{
    //this is a platform piece, it is where the player stands, it makes the walls and all of the platform
	class PlatformPiece
	{
	public:
		PlatformPiece(vec3f size);

		virtual ~PlatformPiece();

		PlatformPiece(PlatformPiece&) = delete;

		WE::Entity* GetEntity();
		WE::RigidBodyComponent* GetBody();
	private:
        struct PlatformCollider : public WE::CollisionHandler
        {
            void HandleCollision(WE::Entity*, WE::Entity*) {};
        };

		//components
		WE::Entity m_Entity;
		WE::Node* m_Node;
		WE::ModelComponent m_Model;
		WE::RigidBodyComponent m_Body;

        PlatformCollider m_Collider;
		CollisionTag m_Tag;
	};
}


#endif //__PLATFORM_PIECE_H