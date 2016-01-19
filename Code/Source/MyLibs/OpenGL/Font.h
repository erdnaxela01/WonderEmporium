#ifndef __FONT_H
#define __FONT_H

#include "MyLibs\OpenGL\Texture.h"
#include "MyLibs\OpenGL\Mesh.h"
#include <map>
#include <string>

//this class will load a font and display it
//this only takes completely even fonts in a file
class Font
{
public:
    //set up the values of the font
    Font(float width, float height, unsigned int numWidth, unsigned int numHeight, std::string format, const char* path);

    virtual ~Font();

    //render the font
    void Render(ShaderProgram* program);

    //set the text
    void SetText(std::string text);

    //return the text
    std::string GetText();
private:
    struct VertexData
    {
        float x;
        float y;
        float u;
        float v;
    };

    struct vec2
    {
        float x;
        float y;
    };

    std::map<char, vec2> m_UVData;
    std::string m_Text;
    Texture m_Texture;
    Mesh m_Mesh;
    vec2 m_Stride;
    vec2 m_Size;

};



#endif //__FONT_H