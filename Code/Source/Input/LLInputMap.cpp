#include "LLInputMap.h"

namespace WE
{
    //load the map from a file
    void LLInputMap::LoadMap(const char* path)
    {
        //open the file
        std::ifstream file(path);
        //the line to get
        std::string line;
        //loop through all the lines
        while (std::getline(file, line))
        {
            //if there is a mapping here
            if (line[0] = 'm')
            {
                int code;
                std::string name;
                //get the code
                sscanf_s(line.c_str(), "m %X", &code);
                //get the name
                name = line.substr(line.find(":") + 1, line.length()).c_str();

                //add to the map
                m_Map[code] = name.c_str();
            }
        }
        file.close();
    }
    //convert the key code to a string
    std::string LLInputMap::Convert(unsigned int keyCode)
    {
        auto iter = m_Map.find(keyCode);

        //if it is found return it, if not return nothing
        if (iter != m_Map.end())
        {
            return iter->second;
        }
        return "";
    }
}