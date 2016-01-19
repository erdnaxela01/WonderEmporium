#ifndef __HL_INPUT_MAP_H
#define __HL_INPUT_MAP_H

#include <map>


/*
Layout style
m string:string
*/
namespace WE
{
    //this class will convert engine inputs to input handler inputs
    class HLInputMap
    {
    public:
        //load the map from a file
        void LoadMap(const char* path);
        //convert the key code to a string
        std::string Convert(const char* name);
    private:
        std::map<std::string, std::string> m_Map;
    };
    
}

#endif //__HL_INPUT_MAP_H