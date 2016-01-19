#include "Font.h"


//set up the values of the font
Font::Font(float width, float height, unsigned int numWidth, unsigned int numHeight, std::string format, const char* name) :m_Texture(name)
{

    m_Mesh.Create(nullptr, 0, 0, {}, GL_TRIANGLES, GL_DYNAMIC_DRAW);

    //get the number of letters for the width
    //unsigned int widthCount = floor(m_Texture.GetWidth() / width);
    //get the stride data
    float wStride = 1.0/ numWidth;

    //set up the height of the font
    //unsigned int heightCount = floor(m_Texture.GetHeight() / height);
    float hStride = 1.0 / numHeight;

    //set up all the uv points
    for (int i = 0; i < format.size(); i++)
    {
        float level = floor(i / numWidth);
        m_UVData[format[i]] = { ( wStride * (float)(i % numWidth)),  1.0f-(hStride * (level + 1.0f)) };
    }

    //setup the stride and size
    m_Stride.x = wStride;
    m_Stride.y = hStride;
    m_Size.x = width;
    m_Size.y = height;

}

Font::~Font()
{

}

//render the font
void Font::Render(ShaderProgram* program)
{
    //set the texture and draw the mesh
    m_Texture.UseTexture(program, "u_Texture");
    if (m_Text.size() != 0)
    {
        m_Mesh.DrawMesh(program);
    }
}

//set the text
void Font::SetText(std::string text)
{
    m_Text = text;
    std::vector<VertexData> m_Vertices;

    m_Vertices.emplace_back();
    m_Vertices.emplace_back();
    m_Vertices.emplace_back();
    m_Vertices.emplace_back();

    //set up the first line of vertices
    m_Vertices[0].x = 0.0f;
    m_Vertices[0].y = 0.0f;

    m_Vertices[1].x = 0.0f;
    m_Vertices[1].y = m_Size.y;

    m_Vertices[0].u = m_UVData.at(text[0]).x;
    m_Vertices[0].v = m_UVData.at(text[0]).y;

    m_Vertices[1].u = m_UVData.at(text[0]).x;
    m_Vertices[1].v = m_UVData.at(text[0]).y + m_Stride.y;

    m_Vertices[2].x = m_Size.x * 1;
    m_Vertices[2].y = 0.0f;

    m_Vertices[2].u = m_UVData.at(text[0]).x + m_Stride.x;
    m_Vertices[2].v = m_UVData.at(text[0]).y;

    m_Vertices[3].x = m_Size.x * 1;
    m_Vertices[3].y = m_Size.y;

    m_Vertices[3].u = m_UVData.at(text[0]).x + m_Stride.x;
    m_Vertices[3].v = m_UVData.at(text[0]).y + m_Stride.y;

    //set up all the letters
    for (int i = 1; i < text.size(); i++)
    {
        m_Vertices.emplace_back();
        m_Vertices.emplace_back();

        m_Vertices[i * 4].x = m_Size.x * i;
        m_Vertices[i * 4 ].y = 0.0f;

        m_Vertices[i * 4].u = m_UVData.at(text[i]).x;
        m_Vertices[i * 4 ].v = m_UVData.at(text[i]).y;

        m_Vertices[i * 4 + 1].x = m_Size.x * i;
        m_Vertices[i * 4 + 1].y = m_Size.y;

        m_Vertices[i * 4 + 1].u = m_UVData.at(text[i]).x;
        m_Vertices[i * 4 + 1].v = m_UVData.at(text[i]).y + m_Stride.y;


        m_Vertices.emplace_back();
        m_Vertices.emplace_back();

        m_Vertices[i * 4 + 2].x = m_Size.x * (i + 1);
        m_Vertices[i * 4 + 2].y = 0.0f;

        m_Vertices[i * 4 + 2].u = m_UVData.at(text[i]).x + m_Stride.x;
        m_Vertices[i * 4 + 2].v = m_UVData.at(text[i]).y;

        m_Vertices[i * 4 + 3].x = m_Size.x * (i + 1);
        m_Vertices[i * 4 + 3].y = m_Size.y;

        m_Vertices[i * 4 + 3].u = m_UVData.at(text[i]).x + m_Stride.x;
        m_Vertices[i * 4 + 3].v = m_UVData.at(text[i]).y + m_Stride.y;
            
    }
	m_Mesh.ChangeData(m_Vertices.data(), m_Vertices.size() * sizeof(Font::VertexData), m_Vertices.size(),
    {
        Mesh::AttributeData("i_Position", 2, sizeof(Font::VertexData)),
		Mesh::AttributeData("i_TexCoord", 2, sizeof(Font::VertexData), sizeof(float) * 2)
    }, GL_TRIANGLE_STRIP);

}

//return the text
std::string Font::GetText()
{
    return m_Text;
}
