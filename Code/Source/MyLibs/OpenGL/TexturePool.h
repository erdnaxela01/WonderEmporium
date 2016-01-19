#ifndef __TEXTURE_POOL_H
#define __TEXTURE_POOL_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\GLExtensions.h"
#include "GL\glext.h"


#include <string>
#include <map>

//this class will hold all textures and will delete all textures
struct TextureData
{
    unsigned int index;
    unsigned int height;
    unsigned int width;
};

class TexturePool
{
public:
    using TextureMap = std::map < const std::string, std::pair<TextureData, unsigned int> >;

    TexturePool() {};

	virtual ~TexturePool();

    //create a texture
    //will only return a created texture if the texture already exists
    TextureData Create(const char* path, GLenum textureUnit = GL_TEXTURE0, GLenum sWrap = GL_CLAMP, GLenum tWrap = GL_CLAMP);
    //destroy a texture
    void Destroy(unsigned int index);


private:
    TextureMap m_Textures;

};


#endif //__TEXTURE_POOL_H