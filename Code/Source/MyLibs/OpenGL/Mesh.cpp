#include "Mesh.h"
#include "ShaderProgram.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\GLExtensions.h"

Mesh::AttributeData::AttributeData(const char* tname, unsigned short tcount,
	unsigned short tstride, unsigned short toffset, bool tnormalized, GLenum attribType) :name(tname), 
    count(tcount), stride(tstride), offset(toffset), normalized(tnormalized), type(attribType)
	
{

}

Mesh::Mesh() :m_Count(0), m_DrawMode(0), m_DrawType(0), m_Size(0), m_VBO(0)
{
}



void Mesh::Create(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>& attributes, GLenum drawMode, GLenum drawType)
{
	m_DrawMode = drawMode;
    m_Count = verticeCount;
	std::swap(m_Attributes, std::forward<std::vector<AttributeData>&>(attributes));

	//generate the buffer
	GenerateVertexBuffer(data, size, drawType);

    m_DrawType = drawType;
    m_Size = size;

}

void Mesh::Create(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>&& attributes, GLenum drawMode, GLenum drawType)
{
	m_DrawMode = drawMode;
    m_Count = verticeCount;
	std::swap(m_Attributes, std::forward<std::vector<AttributeData>&&>(attributes));
	//generate the buffer
	GenerateVertexBuffer(data, size, drawType);
	
    m_DrawType = drawType;
    m_Size = size;
}

Mesh::Mesh(Mesh&& m)
{
	m_VBO = m.m_VBO;
	m.m_VBO = 0;
    m_DrawMode = m.m_DrawMode;
    m_Count = m.m_Count;
    m_DrawType = m.m_DrawType;
    m_Size = m.m_Size;
    m_Attributes = std::move(m.m_Attributes);
    
}

Mesh& Mesh::operator==(Mesh&& m)
{
	m_VBO = m.m_VBO;
	m.m_VBO = 0;
	return *this;
}

Mesh::~Mesh()
{
	//delete the buffer
	if (m_VBO != 0)
	{
		glDeleteBuffers(1, &m_VBO);
	}
}


void Mesh::DrawMesh(ShaderProgram* program)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	std::vector<int> loc;
	//roll through and set all attributes
	for (unsigned int i = 0; i < m_Attributes.size(); i++)
	{
		loc.emplace_back();
		loc[i] = program->SetAttribute(m_Attributes[i]);
	}
	//Draw the buffer
	glDrawArrays(m_DrawMode, 0, m_Count);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (unsigned int i = 0; i < loc.size(); i++)
	{
		if (loc[i] != -1)
		{
			glDisableVertexAttribArray(loc[i]);
		}
	}
}

void Mesh::GenerateVertexBuffer(void* vertices, unsigned int size, GLenum drawType)
{
	//generate the buffer
	glGenBuffers(1, &m_VBO);
	//bind the buffer to set it as active
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	if (size > 0)
	{
		//set the data for the array buffer
		glBufferData(GL_ARRAY_BUFFER, size, vertices, drawType);
	}

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//change the data inside the vbo
void Mesh::ChangeData(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>& attributes, GLenum drawMode)
{
    assert(m_DrawType == GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_DrawMode = drawMode;
    m_Count = verticeCount;
    std::swap(m_Attributes, std::forward<std::vector<AttributeData>&&>(attributes));
    
    //if the size is larger change the data size
    if (size > m_Size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        m_Size = size;
    }
    else
    {
        //change the data
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//change the data within the vbo
void Mesh::ChangeData(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>&& attributes, GLenum drawMode)
{
    assert(m_DrawType == GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_DrawMode = drawMode;
    m_Count = verticeCount;
    std::swap(m_Attributes, std::forward<std::vector<AttributeData>&&>(attributes));

    //if the size is larger change the data size
    if (size > m_Size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        m_Size = size;
    }
    else
    {
        //change the data
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}