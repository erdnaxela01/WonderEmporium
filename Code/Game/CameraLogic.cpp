#include "CameraLogic.h"

namespace Game
{
    const CameraLogic::CameraLogicState  CameraLogic::DEFAULT_STATE = CameraLogic::OverTheShoulderState;
    const float CameraLogic::DISTANCE_FROM_PLAYER = 1.0f;
    const float CameraLogic::HEIGHT_FROM_PLAYER = 0.5f;
    const float CameraLogic::LOOK_AHEAD_DISTANCE = 0.0f;
    const float CameraLogic::FALLING_LOOK_DISTANCE = 6.0f;
    const float CameraLogic::CAMERA_TRACK_VELOCITY = 5.0f;
    const float CameraLogic::CAMERA_TRACK_THRESHOLD = 0.1f;
    const float CameraLogic::CAMERA_MAX_DISTANCE = 1.0f;


    CameraLogic::CameraLogic(WE::TransformComponent* camera, WE::TransformComponent* player) :
        m_MyTransform(camera), 
        m_PlayerTransform(player),
        m_CurrentState(DEFAULT_STATE)
    {
        assert(camera != nullptr && player != nullptr);
        SetUpLogicFunctions();
    }
    CameraLogic::~CameraLogic()
    {

    }

    //update the camera's logic
    void CameraLogic::Update(double delta)
    {
        //update the logic
        (this->*m_States[m_CurrentState])(delta);
    }

    //set the state of the camera
    void CameraLogic::SetState(CameraLogicState state)
    {
        if (m_CurrentState != state)
        {
            LightLogger::Log("Changing state to state " + std::to_string(state) + "\n");
            m_CurrentState = state;
            m_MyTransform->SetRotation(vec3f(0.0f, 0.0f, 0.0f));
        }
    }

    //Logic functions
    void CameraLogic::SetUpLogicFunctions()
    {
        m_States[OverTheShoulderState] = &CameraLogic::OverTheShoulder;
        m_States[TransitionState] = &CameraLogic::TransitionToTopDown;
        m_States[TopDownState] = &CameraLogic::TopDown;
    }
    void CameraLogic::OverTheShoulder(double delta)
    {
        vec3f playerPos = m_PlayerTransform->GetPosition();
        float playerTheta = m_PlayerTransform->GetRotation().z;

        //get the placement of the camera
        float cameraTheta = playerTheta + PI;
        
        vec3f pos;
        pos.x = sin(-cameraTheta) * DISTANCE_FROM_PLAYER + playerPos.x;
        pos.z = cos(-cameraTheta) * DISTANCE_FROM_PLAYER + playerPos.z;
        pos.y = playerPos.y + HEIGHT_FROM_PLAYER;

        m_MyTransform->SetPosition(pos);

        //get the rotation of the camera
        vec3f rotation;

        //pitch and yaw, ignore roll
        rotation.y = playerTheta;
        


        m_MyTransform->SetRotation(rotation);

        
    }
    void CameraLogic::TransitionToTopDown(double delta)
    {
        m_CurrentState = TopDownState;
    }
    void CameraLogic::TopDown(double delta)
    {
        vec3f rotation;
        rotation.y = 0.0f;
        rotation.z = 0.0f;
        rotation.x = 3.14f / 2.0f;
        m_MyTransform->SetRotation(rotation);

        vec3f playerPos = m_PlayerTransform->GetPosition();
        vec3f cameraPos = m_MyTransform->GetPosition();

        vec2f player2 = vec2f(playerPos.x, playerPos.z);
        vec2f camera2 = vec2f(cameraPos.x, cameraPos.z);
        float distance = camera2.Distance(player2);
        if (distance> CAMERA_TRACK_THRESHOLD)
        {
            vec2f deltaVec = vec2f(playerPos.x - cameraPos.x, playerPos.z - cameraPos.z);
            float angle = atan2f(deltaVec.y, deltaVec.x);
            

            cameraPos.x += cos(angle) * CAMERA_TRACK_VELOCITY * delta *(distance / CAMERA_MAX_DISTANCE);
            cameraPos.z += sin(angle) * CAMERA_TRACK_VELOCITY * delta* (distance / CAMERA_MAX_DISTANCE);
        }

        //cameraPos = playerPos;
        cameraPos.y = playerPos.y + FALLING_LOOK_DISTANCE;

        

        m_MyTransform->SetPosition(cameraPos);
    }

    CameraLogic::CameraLogicState CameraLogic::GetState()
    {
        return m_CurrentState;
    }
}