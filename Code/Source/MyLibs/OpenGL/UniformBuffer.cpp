#include "UniformBuffer.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\GLExtensions.h"
#include "GL\glext.h"

unsigned int UniformBuffer::s_Index = 0;

UniformBuffer::UniformBuffer(unsigned int size, Data uniforms, const char* name) : m_Size(size), m_Name(name), m_Buffer(0), m_Count(0),
m_Data(nullptr)
{
	m_Data = New char[size];
	m_Count = s_Index;
	++s_Index;
	//generate the uniform buffer
	glGenBuffers(1, &m_Buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer);
	glBufferData(GL_UNIFORM_BUFFER, size, m_Data, GL_DYNAMIC_DRAW);

	glBindBufferBase(GL_UNIFORM_BUFFER, m_Count, m_Buffer);

	m_Uniforms[uniforms[0].first] = 0;
	for (unsigned int i = 1; i < uniforms.size(); i++)
	{
		m_Uniforms[uniforms[i].first] = uniforms[i - 1].second + m_Uniforms[uniforms[i-1].first];
	}

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_Buffer);
	SafeDeleteArray(m_Data);
}

//set the values in the buffer
void UniformBuffer::SetValues()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, m_Size, m_Data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::SetUniform(const char* name, void* data, unsigned int size, unsigned int stride)
{
	for (int i = 0; i < size; i++)
	{
        for (int j = 0; j < stride; j++)
        {
            ((char*)m_Data)[m_Uniforms[name] + i * stride + j] = ((char*)data)[i * stride + j];
        }
	}
}

void UniformBuffer::RegisterShader(unsigned int program)
{
	int loc = glGetUniformBlockIndex(program, m_Name.c_str());
	//register the shader
    if (loc != -1)
    {
        glUniformBlockBinding(program, loc, m_Count);
    }
}