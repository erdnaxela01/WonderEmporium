#include "Texture.h"
#include "Helper.h"


TexturePool Texture::s_TexturePool = TexturePool();

Texture::Texture(const char* path, GLenum textureUnit, GLenum sWrap, GLenum tWrap) :m_Texture(0), m_Height(0), m_Width(0)
{
    //create the texture
    TextureData data;
    data = s_TexturePool.Create(path, textureUnit, sWrap, tWrap);


    m_Texture = data.index;
    m_Height = data.height;
    m_Width = data.width;

}
Texture::~Texture()
{
    //delete the texture
    s_TexturePool.Destroy(m_Texture);
}

void Texture::SetUnit(unsigned int unit)
{
    //bind the texture to the unit and set it as active
    glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

unsigned int Texture::GetTexture()
{
    return m_Texture;
}

void Texture::SetUniform(ShaderProgram* program, const char* name, unsigned int unit)
{
    //set the uniform to the shader
    program->SetTexture(name, unit);
}

void Texture::UseTexture(ShaderProgram* program, const char* uniformName, unsigned int unit)
{
    //set the unit then set the uniform
    SetUnit(unit);
    SetUniform(program, uniformName, unit);
}

//get the width of the texture
unsigned int Texture::GetWidth()
{
	return m_Width;
}

//get the height of the texture
unsigned int Texture::GetHeight()
{
	return m_Height;
}