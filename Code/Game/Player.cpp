#include "Player.h"

using namespace WE;

namespace Game
{
    const char* Player::MODEL_PATH = "capsule.obj";
    const vec3f Player::SIZE = vec3f(0.2f, 0.2f, 0.2f);

    void Player::Score::AddScore(unsigned int sco)
    {
        score += sco;
        m_Label->GetText().SetText("SCORE " + std::to_string(score));
    }

    Player::Player(WE::LabelComponent* label) :m_Entity("Player"),
        m_Tag(PlayerTag),
        m_Model(&m_Logic, MODEL_PATH, SIZE / 1.5f * (float)Config::s_PPM),
        m_PhysicsBody(1, New btDefaultMotionState(), New btBoxShape(btVector3(SIZE.x + 0.15, SIZE.y, SIZE.z) / 2.0f)),
        m_SceneNode(nullptr),
        m_Logic(&m_PhysicsBody),
        m_Handler(&m_Logic),
        m_Score({ 0 , label})
		
    {
        //adds a collision tag for the collision handlers
        m_Entity.AddComponent(&m_Tag);
        m_Entity.AddComponent(&m_Model);
        m_Entity.AddComponent(&m_PhysicsBody);
		m_Entity.AddComponent(&m_Logic);
		m_Entity.AddComponent(&m_Handler);
        m_Entity.AddComponent(&m_Collision);
        m_Entity.AddComponent(&m_Score);

        m_SceneNode = New Node(&m_Entity);
        m_Entity.AddComponent(m_SceneNode);

		m_Light = New PointLight(&m_Entity);
		m_Entity.AddComponent(m_Light);
		m_Light->SetRadius(1.0f);

		m_PhysicsBody.SetRotation(vec3f(0.0f, 0.0f, -3.14 / 2.0f));
        m_PhysicsBody.GetRigidBody().setFriction(0.0f);
    }

    Player::~Player()
    {
        SafeDelete(m_SceneNode);
		SafeDelete(m_Light);
    }


    WE::Entity* Player::GetEntity()
    {
        return &m_Entity;
    }

    void Player::ResetPosition()
    {
        m_Logic.ResetPosition();
    }
}