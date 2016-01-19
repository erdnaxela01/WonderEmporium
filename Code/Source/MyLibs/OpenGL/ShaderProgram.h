#ifndef __SHADER_PROGRAM_H
#define __SHADER_PROGRAM_H

#include <Windows.h>
#include <gl\GL.h>
#include"Mesh.h"
#include "ShaderPool.h"

//this is where the shader program lives
//it gives you a few useful functions to use this shader
class ShaderProgram
{
public:
	ShaderProgram(const char* vertShader, const char* fragShader);

	virtual ~ShaderProgram();

	//return the program
	unsigned int GetProgram();

	//sets the program as the active program
	void UseProgram();

	//set an attribute
	int SetAttribute(const Mesh::AttributeData& data);

	//set the active texture for the shader
	void SetTexture(const char* name, unsigned int textureUnit);
private:
	friend class ShaderPool;

	unsigned int m_Program;

	static ShaderPool s_ShaderPool;


};


#endif