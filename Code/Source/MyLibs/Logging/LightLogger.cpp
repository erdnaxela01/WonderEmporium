/*
Purpose: this class will log messages for you

Author: Alexandre Sabourin
*/

#include "LightLogger.h"
#include <iostream>

void LightLogger::Log(std::string c)
{
	std::cerr << c;
}
