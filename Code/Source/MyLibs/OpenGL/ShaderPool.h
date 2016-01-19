#ifndef __SHADER_POOL_H
#define __SHADER_POOL_H

#include <map>
#include <string>

//this will hold shaders and their number of references
//if the shader is already created it will return that shader and increment the value
//it will destroy a shader if all references to it are destroyed
class ShaderPool
{
public:
	virtual ~ShaderPool();

	//create a shader
	unsigned int Create(const char* vert, const char* frag);

	//destroy the shader
	void Destroy(unsigned int shaderProgram);

private:
	//create the vert and frag
	unsigned int CreateVertexShader(const char* vertShader);
	unsigned int CreateFragmentShader(const char* fragShader);

	//this will compile shaders
	unsigned int CompileShader(GLenum type, const char* path);

	//provides the opporunity to bind attributes and vertices to specific indeces
	//links the shaders to the program
	void Link(unsigned int program);

	//cache the vert and frag
	std::map<std::string, unsigned int> m_Vertex;
	std::map<std::string, unsigned int> m_Fragments;
	//keep count for the programs
	std::map<std::pair<std::string, std::string>, std::pair<unsigned int, unsigned int>> m_Programs;
};

#endif //__SHADER_POOL_H