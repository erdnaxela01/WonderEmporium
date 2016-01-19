#ifndef __CAMERA_LOGIC_H
#define __CAMERA_LOGIC_H

#include "../Source/Logic/LogicComponent.h"
#include "../Source/Movement/TransformComponent.h"
#include "../Source/Core/Entity.h"

namespace Game
{
    //this component is used by the camera in order to follow the player
    // this will change state if the function set state is called
    class CameraLogic : public WE::LogicComponent
    {
    public:
        enum CameraLogicState
        {
            OverTheShoulderState = 0,
            TopDownState,
            TransitionState,
            MaxLogicStates
        };

        CameraLogic(WE::TransformComponent* camera, WE::TransformComponent* player);
        virtual ~CameraLogic();

        //update the camera's logic
        void Update(double delta) override;

        //set the state of the camera
        void SetState(CameraLogicState state);

        CameraLogicState GetState();
    private: 
        using State = void(CameraLogic::*)(double);
        static const CameraLogicState DEFAULT_STATE;
        static const float DISTANCE_FROM_PLAYER;
        static const float HEIGHT_FROM_PLAYER;
        static const float LOOK_AHEAD_DISTANCE;
        static const float FALLING_LOOK_DISTANCE;
        static const float CAMERA_TRACK_VELOCITY;
        static const float CAMERA_TRACK_THRESHOLD;
        static const float CAMERA_MAX_DISTANCE;


        //Logic functions
        void SetUpLogicFunctions();
        void OverTheShoulder(double delta);
        void TransitionToTopDown(double delta);
        void TopDown(double delta);

        //all the states the camera can be in
        State m_States[MaxLogicStates];
        CameraLogicState m_CurrentState;

        WE::TransformComponent* m_MyTransform;
        WE::TransformComponent* m_PlayerTransform;

    };
}


#endif //__CAMERA_LOGIC_H