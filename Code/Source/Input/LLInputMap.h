#ifndef __LL_INPUT_MAP_H
#define __LL_INPUT_MAP_H

#include <fstream>
#include <map>

/*
File Format:

m code:string


*/

namespace WE
{
    //this will convert hardware input to engine input
    class LLInputMap
    {
    public:
        //load the map from a file
        void LoadMap(const char* path);
        //convert the key code to a string
        std::string Convert(unsigned int keyCode);
    private:
        std::map<int, std::string> m_Map;
    };
}

#endif //__LL_INPUT_MAP_H