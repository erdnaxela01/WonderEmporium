#ifndef __INPUT_HANDLER_H
#define __INPUT_HANDLER_H

#include "HLInputMap.h"
#include "Input.h"

namespace WE
{
    //this will handle input sent from the input system
    //classes must implement the handle input function
    class InputHandler
    {
    public:
        virtual ~InputHandler() {};

        //load the input file
        InputHandler(const char*);

        //handle the input
        virtual void HandleInput(Input&& t) = 0;

        //receive the input
        void ReceiveInput(Input&& t);
    private:
        HLInputMap m_Map;
    };
}

#endif //__INPUT_HANDLER_H