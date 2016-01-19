#include "BeamPlatform.h"
#include "Game.h"

using namespace WE;

namespace Game
{
    const float BeamPlatform::BEAM_LINKS = 10;
    const float BeamPlatform::BEAM_FREQUENCY = 1.0f / 10.0f;
    const unsigned int BeamPlatform::BEAM_COUNT = 3;

    BeamPlatform::BeamPlatform():
        m_Parent(nullptr),
        m_BeamPlatform("BeamPlatform"),
        m_Model(""),
        m_Transform()
    {
        //add all the components
        m_BeamPlatform.AddComponent(&m_Transform);
        m_BeamPlatform.AddComponent(&m_Model);
        
        m_Parent = New ParentNode(&m_BeamPlatform);
        m_BeamPlatform.AddComponent(m_Parent);


    }

    BeamPlatform::~BeamPlatform()
    {
        for (uint32 i = 0; i < m_Beams.size(); i++)
        {
            SafeDelete(m_Beams[i]);
        }
        SafeDelete(m_Parent);
    }

    //return the entity
    WE::Entity* BeamPlatform::GetEntity()
    {
        return &m_BeamPlatform;
    }

    void BeamPlatform::Create(vec3f size, float count)
    {
        m_Beams.reserve(count);

        //the width beams
        //set up all their parameters
        for (uint16 i = 0; i < count; i++)
        {
            m_Beams.emplace_back();
            m_Beams[i] = New SingleBeam();
            m_Beams[i]->emitter.SetAmplitude((size.x / Config::s_PPM / count) * 0.5);
            m_Beams[i]->emitter.SetColor(vec4f(1.0f, 1.0f, 0.0f, 1.0f));
            m_Beams[i]->emitter.SetFrequency(BEAM_FREQUENCY);
            m_Beams[i]->emitter.SetLength(size.z / Config::s_PPM);
            m_Beams[i]->emitter.SetWidth(2.0f);
            m_Beams[i]->emitter.SetLinksPerBeam(BEAM_LINKS);
            m_Beams[i]->emitter.SetNumberOfBeams(BEAM_COUNT);
            
            //setup their position
            float intervals = size.x / Config::s_PPM / count;
            vec3f pos;
            pos.x = (size.z / Config::s_PPM / 2.0);
            pos.y = -size.y / Config::s_PPM;
            pos.z = (intervals * i) - (size.x / Config::s_PPM/ 2.0);
            m_Beams[i]->transform.SetPosition(pos);
            m_Beams[i]->transform.SetRotation(vec3f(3.14f / 2.0f, 0.0f, 0.0));
            m_Parent->AddChild(&m_Beams[i]->beamEntity);
        }


    }

    //adds all the objects to the game
    void BeamPlatform::AddToGame(GameScene* game)
    {
        game->AddEntity(&m_BeamPlatform);
        for (uint32 i = 0; i < m_Beams.size(); i++)
        {
            game->AddEntity(&m_Beams[i]->beamEntity);
        }
        game->GetSceneGraph()->AddChild(m_Parent);
    }

    BeamPlatform::SingleBeam::SingleBeam() :
        beamEntity("Beam"),
        emitter(),
        node(nullptr),
        transform()
    {
        beamEntity.AddComponent(&emitter);
        beamEntity.AddComponent(&transform);
        node = New Node(&beamEntity);
        beamEntity.AddComponent(node);
    }
    BeamPlatform::SingleBeam::~SingleBeam()
    {
        SafeDelete(node);
    }
}