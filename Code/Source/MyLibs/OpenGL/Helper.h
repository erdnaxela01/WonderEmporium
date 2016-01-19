#ifndef __HELPER_H
#define __HELPER_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\GLExtensions.h"
#include <string>

//load a file
std::string LoadFile(const char* path);

//check for an opengl

void CheckForGLErrors();



//load a png from a path
void LoadPng(const char* path, unsigned int* width, unsigned int* height, unsigned char** png);

//flip the image vertically
void Flip32BitImageVertically(unsigned char* png, unsigned int width, unsigned int height);

//make a texture from a path
unsigned int MakeTexture(const char* path, unsigned int* width, unsigned int* height, GLenum textureUnit = GL_TEXTURE0, GLenum sWrap = GL_CLAMP, GLenum tWrap = GL_CLAMP);

//get the number for the texture unit
//does from one to 4, returns 0 if it isnt anything
unsigned int GetNumber(GLenum unit);

#endif