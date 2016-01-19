#include "TexturePool.h"
#include <algorithm>
#include "Helper.h"


TexturePool::~TexturePool()
{
	//delete all the remaining textures
	for (auto i : m_Textures)
	{
		glDeleteTextures(1, &i.second.first.index);
	}
}

//
TextureData TexturePool::Create(const char* path, GLenum textureUnit, GLenum sWrap, GLenum tWrap)
{
    //find if the path exists
    auto iter = m_Textures.find(path);
    //if it doesnt
    if (iter == m_Textures.end())
    {
        //create a new texture
        TextureData data;
        data.index = MakeTexture(path, &data.width, &data.height, textureUnit, sWrap, tWrap);

        //add it to the map and return it
        m_Textures[path] = std::make_pair(data, 1);
        return data;
    }
    else
    {
        //increment the reference count and return  it
        ++iter->second.second;
        return iter->second.first;
    }
    
}
//destroy a texture
void TexturePool::Destroy(unsigned int index)
{
	if (m_Textures.empty()) return;
    auto iter = std::find_if(m_Textures.begin(), m_Textures.end(), [&](const std::pair<const std::string, 
        std::pair<TextureData, unsigned int>>& v)->bool{ return v.second.first.index == index; });
    if (iter != m_Textures.end())
    {
        --iter->second.second;
        if (iter->second.second <= 0)
        {
            glDeleteTextures(1, &iter->second.first.index);
            m_Textures.erase(iter);
        }
    }
}