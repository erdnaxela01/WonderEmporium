#include "HLInputMap.h"
#include <fstream>

namespace WE
{
    //load the map from a file
    void HLInputMap::LoadMap(const char* path)
    {
        //open the file
        std::ifstream file(path);

        //the line to get
        std::string line;
        //loop through all the lines
        while (std::getline(file, line))
        {
            //if there is a mapping here
            if (line[0] == 'm')
            {
                std::string code;
                std::string name;
                
                //get the position 
                unsigned int pos = line.find(":");
                //get the name can code
                code = line.substr(2, pos - 2).c_str();
                name = line.substr(pos + 1, line.length()).c_str();

                //add to the map
                m_Map[code] = name.c_str();
            }
        }
        file.close();
    }
    //convert the key code to a string
    std::string HLInputMap::Convert(const char* code)
    {
        auto iter = m_Map.find(code);

        //if it is found return it, if not return nothing
        if (iter != m_Map.end())
        {
            return iter->second;
        }
        return "";
    }
}