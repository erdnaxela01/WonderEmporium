#ifndef __PLAYER_INPUT_HANDLER_H
#define __PLAYER_INPUT_HANDLER_H

#include "../Source/Input/InputHandler.h"
#include "../Source/Movement/RigidBodyComponent.h"
#include "PlayerLogic.h"

namespace Game
{
    //handles the input sent to the player, it will move the player
    class PlayerInputHandler: public WE::InputHandler
    {
    public:

		PlayerInputHandler(PlayerLogic* logic);

        virtual ~PlayerInputHandler();

        //handle the input sent to the player
        void HandleInput(WE::Input&& t);
    private:
        using Callback = void(PlayerInputHandler::*)(bool);

        static const std::string INPUT_PATH;

        std::map<std::string, Callback> m_InputCallbacks;
		
		PlayerLogic* m_Logic;

        //set up the input
        void SetUpInput();
        
        //handles to input commands
        void Front(bool state);
        void Back(bool state);
		void RotateLeft(bool state);
		void RotateRight(bool state);
    };
}

#endif  __PLAYER_INPUT_HANDLER_H