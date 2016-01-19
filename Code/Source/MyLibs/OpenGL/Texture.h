#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\GLExtensions.h"
#include "ShaderProgram.h"
#include "TexturePool.h"

//this class holds a texture and gives it some useful tools
//its pretty versatile giving you options on how you want to initiate your texture
class Texture
{
public:
    //creates the texture
    Texture(const char* path, GLenum textureUnit = GL_TEXTURE0, GLenum sWrap = GL_CLAMP, GLenum tWrap = GL_CLAMP);
    //destroys the texture
    virtual ~Texture();

    //set the texture unit to bind the texture to
    void SetUnit(unsigned int unit);

    //return the texture
    unsigned int GetTexture();

    //set the uniform for the texture
    void SetUniform(ShaderProgram* program, const char* name, unsigned int unit = 0);

    //bind the texture to the unit and set the uniform
    void UseTexture(ShaderProgram* program, const char* uniformName, unsigned int unit = 0);

	//get the width of the texture
	unsigned int GetWidth();

	//get the height of the texture
	unsigned int GetHeight();
private:
	unsigned int m_Width;
	unsigned int m_Height;
    unsigned int m_Texture;

    static TexturePool s_TexturePool;
};

#endif //__TEXTURE_H