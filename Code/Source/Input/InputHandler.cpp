#include "InputHandler.h"

namespace WE
{
    //load the input file
    InputHandler::InputHandler(const char* path)
    {
		m_Map.LoadMap(path);
    }

    //receive the input
    void InputHandler::ReceiveInput(Input&& t)
    {
        //set the name
        t.name = (m_Map.Convert(t.name.c_str()));
        //call the derived method
        HandleInput(std::forward<Input&&>(t));
    }
}