#ifndef __LIGHT_LOGGER_H
#define __LIGHT_LOGGER_H

#include <string>


/*
This logger will do just what you ask it, Log things, it's light due to it's simplicity,
a heavier but more complex logger might be added overtime
*/
struct LightLogger
{
	//this will log a message
	static void Log(std::string c);
};


#endif //__LIGHT_LOGGER_H