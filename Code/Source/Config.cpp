#include "Config.h"
#include <fstream>
#include <sstream>

namespace WE
{
	const char* Config::ASSET_PATH = "Assets";
    const char* Config::CONFIG_PATH = "Assets/Bin/Config.txt";
	const vec2f Config::WINDOW_SIZE = vec2f(0.0f, 0.0f);
    const std::string Config::WINDOW_NAME = "";
    const char* Config::WINDOW_SHADERS[2] = { "Default.vert", "Default.frag" };
    const char* Config::INPUT_SYSTEM_LL_PATH = "Assets/Bin/LowLevelMap.txt";
    unsigned int Config::s_PhysicsFPS = 60;
    unsigned int Config::s_PPM = 100;
    unsigned int Config::s_LogicFPS = 60;

    void Config::LoadConfig()
    {
        std::ifstream file(CONFIG_PATH);

        std::string line;
        while (std::getline(file, line))
        {
            if (line.find("WINDOW_SIZE") != line.npos)
            {
                //cast away the constness and load the values
                vec2f* v = const_cast<vec2f*>(&WINDOW_SIZE);
                sscanf_s(line.c_str(), "WINDOW_SIZE %f/%f", &(v->x), &(v->y));
            }
            else if (line.find("WINDOW_NAME") != line.npos)
            {
                std::string* s = const_cast<std::string*>(&WINDOW_NAME);
                //load the string
                *s = line.substr(std::string("WINDOW_NAME ").length(), line.length());
            }
			else if (line.find("PHYSICS_FPS") != line.npos)
            {
                std::stringstream stream;
                stream.str(line);
                std::string lines;
                stream >> lines;
                stream >> s_PhysicsFPS;
			}
            else if (line.find("LOGIC_FPS") != line.npos)
            {
                std::stringstream stream;
                stream.str(line);
                std::string lines;
                stream >> lines;
                stream >> s_LogicFPS;
            }
            else if (line.find("PHYSICS_PPM") != line.npos)
            {
                std::stringstream stream;
                stream.str(line);
                std::string lines;
                stream >> lines;
                stream >> s_PPM;
            }
        }

    }
}