#ifndef __PLAYER_LOGIC_H
#define __PLAYER_LOGIC_H

#include "../Source/Logic/LogicComponent.h"
#include "../Source/Movement/RigidBodyComponent.h"

#include <bitset>

namespace Game
{
    //handles the logic of the player such as moving and updating the frag and vert effects
    class PlayerLogic : public WE::LogicComponent
    {
    public:
        enum ControlType
        {
            OverTheShoulder,
            TopDown
        };

		enum LogicState
		{
			ForwardState = 0,
			BackState,
			LeftState,
			RightState,
			MaxLogicStates
		};

        PlayerLogic(WE::RigidBodyComponent* body);

        virtual ~PlayerLogic();

        //update the player logic
        void Update(double delta) override;

		//turn on or off the state of the player
		void SetState(LogicState state, bool flag);

        //set the controls of the player
        void SetControls(ControlType control);

        //reset the position of the player
        void ResetPosition();

        //set the total time and get the delta time
        void SetTotalTime(double time);
        void SetTime(double time);
        double GetTime();
        double GetTotalTime();
    private:
		static const float PLAYER_LINEAR_VELOCITY;
		static const float PLAYER_ANGULAR_VELOCITY;
        static const vec3f DEFAULT_POSITION;

        double m_DeltaTime;
        double m_TotalTime;

		//all the flags
		std::bitset<MaxLogicStates> m_States;
		WE::RigidBodyComponent* m_Body;

        ControlType m_Controls;

    };
}

#endif //__PLAYER_LOGIC_H