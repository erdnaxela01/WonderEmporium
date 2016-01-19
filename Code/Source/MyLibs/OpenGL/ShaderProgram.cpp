#include "ShaderProgram.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\GLExtensions.h"
#include "Helper.h"
#include <cassert>

ShaderPool ShaderProgram::s_ShaderPool = ShaderPool();

ShaderProgram::ShaderProgram(const char* vertShader, const char* fragShader) :m_Program(0)
{
	m_Program = s_ShaderPool.Create(vertShader, fragShader);

}


ShaderProgram::~ShaderProgram()
{
	s_ShaderPool.Destroy(m_Program);
}


//return the program
unsigned int ShaderProgram::GetProgram()
{
	return m_Program;
}

//sets the program as the active program
void ShaderProgram::UseProgram()
{
	glUseProgram(m_Program);
}




int ShaderProgram::SetAttribute(const Mesh::AttributeData& data)
{
	//get the location of the attribute
	int loc = glGetAttribLocation(m_Program, data.name);
	if (loc != -1)
	{
		//set the attributes for the vbo
		glVertexAttribPointer(loc, data.count, data.type, data.normalized, data.stride, reinterpret_cast<void*>(data.offset));
		glEnableVertexAttribArray(loc);
	}

    //glDisableVertexAttribArray(loc);
	return loc;
}

//set a texture to the specified texture unit
void ShaderProgram::SetTexture(const char* name, unsigned int textureUnit)
{
	//set the sampler location
	unsigned int loc = glGetUniformLocation(m_Program, name);
	if (loc != -1)
	{
		glUniform1i(loc, textureUnit);
	}
	
}