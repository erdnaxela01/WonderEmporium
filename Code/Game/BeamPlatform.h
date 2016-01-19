#ifndef __BEAM_PLATFORM_H
#define __BEAM_PLATFORM_H

#include "../Source/Rendering/ParticleEmitter.h"
#include "../Source/Core/Entity.h"
#include "../Source/Movement/TransformComponent.h"
#include "../Source/Rendering/Node.h"
#include "../Source/Rendering/ModelComponent.h"
#include "../Source/Rendering/ParentNode.h"

namespace Game
{
    class GameScene;

    //this beam platform will handle all the particle beams at the bottom of the pit
    //it will generate them when the function create it called
    class BeamPlatform
    {
    public:
        BeamPlatform();

        virtual ~BeamPlatform();

        //return the entity
        WE::Entity* GetEntity();

        //adds all the objects to the game
        void AddToGame(GameScene* game);


        void Create(vec3f size, float count);
    private:
        static const float BEAM_LINKS;
        static const float BEAM_FREQUENCY;
        static const unsigned int BEAM_COUNT;

        //this struct holds the data for a single beam
        struct SingleBeam
        {
            SingleBeam();
            virtual ~SingleBeam();

            WE::Entity beamEntity;
            WE::ParticleEmitter emitter;
            WE::TransformComponent transform;
            WE::Node* node;

        };

        WE::Entity m_BeamPlatform;
        WE::TransformComponent m_Transform;
        WE::ModelComponent m_Model;
        WE::ParentNode* m_Parent;
        std::vector<SingleBeam*> m_Beams;
    };
}


#endif //__BEAM_PLATFORM_H