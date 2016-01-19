#ifndef __PLAYER_H
#define __PLAYER_H

#include "../Source/Core/Entity.h"
#include "../Source/Movement/RigidBodyComponent.h"
#include "../Source/Rendering/ModelComponent.h"
#include "../Source/Rendering/Node.h"

#include "CollisionTag.h"
#include "PlayerInputHandler.h"
#include "PlayerLogic.h"
#include "PlayerCollisionHandler.h"
#include "PlayerModel.h"
#include "../Source/Rendering/PointLight.h"
#include "../Source/Rendering/LabelComponent.h"

namespace Game
{
    //this is the character controlled by the player
    //he has a vertex and fragment shader effect
    class Player
    {
    public:
        struct Score
        {
            unsigned int score;
            WE::LabelComponent* m_Label;
            //adds a value to the score
            void AddScore(unsigned int score);
        };


		static const vec3f SIZE;


        Player(WE::LabelComponent* label);

        virtual ~Player();

        WE::Entity* GetEntity();

        //reset the position of the enemy
        void ResetPosition();
    private:
        //constant values
        static const char* MODEL_PATH;

        WE::Entity m_Entity;
        WE::RigidBodyComponent m_PhysicsBody;
        WE::Node* m_SceneNode;
		WE::PointLight* m_Light;
        
        CollisionTag m_Tag;
		PlayerLogic m_Logic;
		PlayerInputHandler m_Handler;
        PlayerCollisionHandler m_Collision;
        PlayerModel m_Model;
        Score m_Score;

    };
}


#endif //__PLAYER_H