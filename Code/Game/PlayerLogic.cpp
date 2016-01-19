#include "PlayerLogic.h"

namespace Game
{

	const float PlayerLogic::PLAYER_LINEAR_VELOCITY = 4.0;
	const float PlayerLogic::PLAYER_ANGULAR_VELOCITY = 3.3;
    const vec3f PlayerLogic::DEFAULT_POSITION = vec3f(vec3f(0.0f, 0.2f, -3.5f));

	PlayerLogic::PlayerLogic(WE::RigidBodyComponent* body) :m_Body(body),
        m_Controls(OverTheShoulder)
    {
		assert(body != nullptr);
    }

    PlayerLogic::~PlayerLogic()
    {
    }

	//turn on the state of the player
	void PlayerLogic::SetState(LogicState state, bool flag)
	{
		m_States[state] = flag;
	}

    void PlayerLogic::SetControls(ControlType control)
    {
        m_Controls = control;
    }

    void PlayerLogic::ResetPosition()
    {
        m_Body->SetPosition(DEFAULT_POSITION);
        m_Body->GetRigidBody().setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
    }

    //set the total time and get the delta time
    void PlayerLogic::SetTotalTime(double time)
    {
        m_TotalTime = time;
    }
    void PlayerLogic::SetTime(double time)
    {
        m_DeltaTime = time;
    }
    double PlayerLogic::GetTime()
    {
        return m_DeltaTime;
    }

    double PlayerLogic::GetTotalTime()
    {
        return m_TotalTime;
    }

    //update the player logic
    void PlayerLogic::Update(double delta)
    {

        m_DeltaTime += delta;
        if (m_DeltaTime > m_TotalTime)
        {
            m_DeltaTime = 0.0f;
        }

		m_Body->GetBody()->activate();

        //probably the worst control setup ever X)
        if (m_Controls == OverTheShoulder)
        {
	        //check the states of movement
	        if (m_States[ForwardState])
	        {
		        vec3f rotation = m_Body->GetRotation();
				m_Body->GetRigidBody().setLinearVelocity(btVector3(cos(rotation.z + 3.14f / 2.0f) * PLAYER_LINEAR_VELOCITY, m_Body->GetRigidBody().getLinearVelocity().getY(), sin(rotation.z + 3.14f / 2.0f) * PLAYER_LINEAR_VELOCITY));
	        }
	        else if (m_States[BackState])
	        {
		        vec3f rotation = m_Body->GetRotation();
		        m_Body->GetRigidBody().setLinearVelocity(btVector3(cos(rotation.z + 3.14f / 2.0f) * -PLAYER_LINEAR_VELOCITY, m_Body->GetRigidBody().getLinearVelocity().getY(), sin(rotation.z + 3.14f / 2.0f) * -PLAYER_LINEAR_VELOCITY));
	        }
	        else
	        {
		        m_Body->GetRigidBody().setLinearVelocity(btVector3(0.0f, m_Body->GetRigidBody().getLinearVelocity().getY(), 0.0f));
	        }

            //check the states of rotation
            if (m_States[RightState])
            {
                m_Body->GetRigidBody().setAngularVelocity(btVector3(0.0f, PLAYER_ANGULAR_VELOCITY, 0.0f));
            }
            else if (m_States[LeftState])
            {
                m_Body->GetRigidBody().setAngularVelocity(btVector3(0.0f, -PLAYER_ANGULAR_VELOCITY, 0.0f));
            }
            else
            {
                m_Body->GetRigidBody().setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
            }
        }
        else if (m_Controls == TopDown)
        {
            //check the states of movement
            if (m_States[ForwardState])
            {
               
                m_Body->GetRigidBody().setLinearVelocity(btVector3(m_Body->GetRigidBody().getLinearVelocity().getX(), m_Body->GetRigidBody().getLinearVelocity().getY(), PLAYER_LINEAR_VELOCITY));
            }
            else if (m_States[BackState])
            {
               
                m_Body->GetRigidBody().setLinearVelocity(btVector3(m_Body->GetRigidBody().getLinearVelocity().getX(), m_Body->GetRigidBody().getLinearVelocity().getY(), -PLAYER_LINEAR_VELOCITY));
            }
            else
            {
                m_Body->GetRigidBody().setLinearVelocity(btVector3(m_Body->GetRigidBody().getLinearVelocity().getX(), m_Body->GetRigidBody().getLinearVelocity().getY(), 0.0f));
            }

            //check the states of rotation
            if (m_States[RightState])
            {
                m_Body->GetRigidBody().setLinearVelocity(btVector3(PLAYER_LINEAR_VELOCITY, m_Body->GetRigidBody().getLinearVelocity().getY(), m_Body->GetRigidBody().getLinearVelocity().getZ()));
            }
            else if (m_States[LeftState])
            {
                m_Body->GetRigidBody().setLinearVelocity(btVector3(-PLAYER_LINEAR_VELOCITY, m_Body->GetRigidBody().getLinearVelocity().getY(), m_Body->GetRigidBody().getLinearVelocity().getZ()));
            }
            else
            {
                m_Body->GetRigidBody().setLinearVelocity(btVector3(0.0f, m_Body->GetRigidBody().getLinearVelocity().getY(), m_Body->GetRigidBody().getLinearVelocity().getZ()));
            }
        }
		
    }
}