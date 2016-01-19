#include "PlayerInputHandler.h"

using namespace WE;

namespace Game
{
	const std::string PlayerInputHandler::INPUT_PATH = Config::ASSET_PATH + std::string("/Bin/") + "PlayerMap.txt";

	PlayerInputHandler::PlayerInputHandler(PlayerLogic* logic) :
        InputHandler(INPUT_PATH.c_str()),
		m_Logic(logic)
    {
		assert(logic != nullptr);
		SetUpInput();
    }

    PlayerInputHandler::~PlayerInputHandler()
    {
    }

    //handle the input sent to the player
    void PlayerInputHandler::HandleInput(WE::Input&& t)
    {
        //check what state the keys were in
		bool state;
        if (*t.data.Get<std::string>() == "KeyDown")
        {
			state = true;
        }
		else if (*t.data.Get<std::string>() == "KeyUp")
		{
			state = false;
		}

		if (m_InputCallbacks.find(t.name) != m_InputCallbacks.end())
		{
			(this->*m_InputCallbacks[t.name])(state);
		}
        
    }


    //set up the input
    void PlayerInputHandler::SetUpInput()
    {
		m_InputCallbacks["FRONT"] = &PlayerInputHandler::Front;
		m_InputCallbacks["BACK"] = &PlayerInputHandler::Back;
		m_InputCallbacks["LEFT"] = &PlayerInputHandler::RotateLeft;
		m_InputCallbacks["RIGHT"] = &PlayerInputHandler::RotateRight;
    }

    //handles to input commands
	void PlayerInputHandler::Front(bool state)
    {
		m_Logic->SetState(PlayerLogic::ForwardState, state);
		
    }
	void PlayerInputHandler::Back(bool state)
    {
		
		m_Logic->SetState(PlayerLogic::BackState, state);
		
    }
	void PlayerInputHandler::RotateLeft(bool state)
    {
		m_Logic->SetState(PlayerLogic::LeftState, state);
    }
	void PlayerInputHandler::RotateRight(bool state)
    {
		m_Logic->SetState(PlayerLogic::RightState, state);
    }
}