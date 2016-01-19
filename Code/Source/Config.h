#ifndef __CONFIG_H
#define __CONFIG_H

namespace WE
{
	struct Config
	{
		static const char* ASSET_PATH;
        static const char* CONFIG_PATH;
		static const vec2f WINDOW_SIZE;
        static const std::string WINDOW_NAME;
        static const char* WINDOW_SHADERS[2];
        static const char* INPUT_SYSTEM_LL_PATH;
		static unsigned int s_PhysicsFPS;
        static unsigned int s_LogicFPS;
        static unsigned int s_PPM;
        //loads all the default values from a config file
        static void LoadConfig();
	};
}

#endif //__CONFIG_H