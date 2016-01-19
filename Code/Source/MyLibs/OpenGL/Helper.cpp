#include "Helper.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\GLExtensions.h"

#include "lodepng\lodepng.h"

std::string LoadFile(const char* path)
{
	std::fstream file(path);

	if (!file.is_open())
	{
		printf("%s", "Could not load file");
		return "";
	}
	

	std::stringstream ss;
	std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(ss));


	return ss.str();
}

void CheckForGLErrors()
{
#ifdef MY_DEBUG
	GLenum error;
	const char* text = nullptr;
    
    
	//loop through all the errors if there is any
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		//get the text, output it and crash
		switch (error) {
			case GL_INVALID_OPERATION:      
				text = "INVALID_OPERATION\n";      
				break;
			case GL_INVALID_ENUM:          
				text = "INVALID_ENUM\n";      
				break;
			case GL_INVALID_VALUE:     
				text = "INVALID_VALUE\n";  
				break;
			case GL_OUT_OF_MEMORY:  
				text = "OUT_OF_MEMORY\n";  
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: 
				text = "INVALID_FRAMEBUFFER_OPERATION\n"; 
				break;
			default:
				text = "OpenGL error\n";
				break;
		}
		//Log the info
		//TODO: remove
		std::cout << text << std::endl;
		OutputDebugString(text);
		assert(false);

	}
#endif
}

void LoadPng(const char* path, unsigned int* width, unsigned int* height, unsigned char** png)
{
	*png = nullptr;
	//load the png
	lodepng_decode32_file(png, width, height, path);

	//flip it around its x axis
	if (*png != nullptr)
	{
		Flip32BitImageVertically(*png, *width, *height);
	}
}

void Flip32BitImageVertically(unsigned char* png, unsigned int width, unsigned int height)
{
	//allocate a line to hold the png line
	unsigned int* temp = New unsigned int[sizeof(unsigned int) * width];

	//cast the buffer to an int cast so that its rgba
	unsigned int* buffer = reinterpret_cast<unsigned int*>(png);

	//get the size of each line
	unsigned int size = width * sizeof(unsigned int);

	for (unsigned int i = 0; i < height / 2; i++)
	{
		//get the top line
		int offsetY = width * i;
		//get the bottom line
		int bottom = (height - 1 - i) * width;
		
		//copy the top line into the temp holder
		memcpy(temp, &buffer[offsetY], size);

		//copy the bottom line into the top line
		memcpy(&buffer[offsetY], &buffer[bottom], size);

		//copy the top line stored in temp into the bottom line
		memcpy(&buffer[bottom], temp, size);

		//we just swapped both lines
		
	}


	SafeDeleteArray(temp);
}

unsigned int MakeTexture(const char* path, unsigned int* width, unsigned int* height, GLenum textureUnit, GLenum sWrap, GLenum tWrap)
{
	unsigned int textureObject = 0;
	//generate the texture object
	glGenTextures(1, &textureObject);
	//set the texture to the texture unit
	glActiveTexture(textureUnit);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, textureObject);

	unsigned char* png;

	unsigned int twidth;
	unsigned int theight;

	//load the png data
	LoadPng(path, &twidth, &theight, &png);
	//set the 2d image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, png);

	//set the texture wrapping when the 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
	//set the minification and magnification filter to nearest
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//reset the texture to 0
	glBindTexture(GL_TEXTURE_2D, 0);
	*width = twidth;
	*height = theight;
	return textureObject;
}

//get the texture unit number for the unit texture
unsigned int GetNumber(GLenum unit)
{
	switch (unit)
	{
	case GL_TEXTURE0:
		return 0;
	case GL_TEXTURE1:
		return 1;
	case GL_TEXTURE2:
		return 2;
	case GL_TEXTURE3:
		return 3;
	}
	return 0;
}