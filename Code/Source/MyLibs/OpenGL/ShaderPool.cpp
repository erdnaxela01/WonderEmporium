#include "ShaderPool.h"
#include <algorithm>
#include <iostream>

ShaderPool::~ShaderPool()
{
	//go around and delete the fragment shaders
	for (auto i : m_Fragments)
	{
		glDeleteShader(i.second);
	}
	//go around and delete the vertex shaders
	for (auto i : m_Vertex)
	{
		glDeleteShader(i.second);
	}
}

//create a shader
unsigned int ShaderPool::Create(const char* vert, const char* frag)
{
	if (m_Programs.find(std::make_pair(vert, frag)) == m_Programs.end())
	{
		//create both shaders
		unsigned int vertex = CreateVertexShader(vert);
		unsigned int fragment = CreateFragmentShader(frag);

		//create the program
		unsigned int program = glCreateProgram();

		//attach our shaders to the program
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		//link the program
		Link(program);

		//add it to the programs list
		m_Programs[std::make_pair(vert, frag)] = std::make_pair(program, 1);
		return m_Programs[std::make_pair(vert, frag)].first;
	}
	else
	{
		//add one to the use count
		++m_Programs[std::make_pair(vert, frag)].second;
		//return the program
		return m_Programs[std::make_pair(vert, frag)].first;
	}

}

//destroy the shader
void ShaderPool::Destroy(unsigned int shaderProgram)
{
	auto iter = std::find_if(m_Programs.begin(), m_Programs.end(), [&](const std::pair<std::pair<std::string, std::string>,
		std::pair<unsigned int, unsigned int >> &v)->bool{ return v.second.first == shaderProgram; });
	if (iter != m_Programs.end())
	{
		--iter->second.second;
		if (iter->second.second <= 0)
		{
			glDeleteTextures(1, &iter->second.first);
			m_Programs.erase(iter);
		}
	}
}


//create the vert and frag
unsigned int ShaderPool::CreateVertexShader(const char* vertShader)
{
	//if there isnt a shader with this name compile one and add it to the map
	if (m_Vertex.find(vertShader) == m_Vertex.end())
	{
		//compile the shader
		unsigned int index = CompileShader(GL_VERTEX_SHADER, vertShader);
		m_Vertex[vertShader] = index;
		return index;
	}
	else
	{
		return m_Vertex.at(vertShader);
	}
}
unsigned int ShaderPool::CreateFragmentShader(const char* fragShader)
{
	//if there isnt a shader with this name compile one and add it to the map
	if (m_Fragments.find(fragShader) == m_Fragments.end())
	{
		//compile the shader
		unsigned int index = CompileShader(GL_FRAGMENT_SHADER, fragShader);
		m_Fragments[fragShader] = index;
		return index;
	}
	else
	{
		return m_Fragments.at(fragShader);
	}
}

unsigned int ShaderPool::CompileShader(GLenum type, const char* path)
{
	//create the shader
	unsigned int handle = glCreateShader(type);

	//get the source file of the shader
	std::string s = LoadFile(path);
	const char* source[] = { s.c_str() };

	//set the source file of the shader to the shader
	glShaderSource(handle, 1, source, 0);

	//compile the shader
	glCompileShader(handle);

	int compiled = 0;

	//check if it compiled
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

	//if it didnt compile
	if (compiled == 0)
	{
		//get the lenght of the info log
		int infolen = 0;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infolen);
		infolen += 1;

		//set a new buffer
		char* info = New char[infolen + 1];
		//get the log
		glGetShaderInfoLog(handle, infolen + 1, 0, info);

		//output the string
		OutputDebugString(info);
		SafeDeleteArray(info);

		//delete the shader
		glDeleteShader(handle);

		//this didnt work
		assert(false);



		//return 0;
		return 0;
	}

	return handle;
}

//provides the opporunity to bind attributes and vertices to specific indeces
//links the shaders to the program
void ShaderPool::Link(unsigned int program)
{
	glLinkProgram(program);
	int linked = 0;
	//check if it linked
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	//if it didnt link
	if (linked == 0)
	{
		//get the lenght of the info log
		int infolen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infolen);
		infolen += 1;

		//set a new buffer
		char* info = New char[infolen];
		//get the log
		glGetProgramInfoLog(program, infolen, 0, info);

		//output the string
		OutputDebugString(info);
		SafeDeleteArray(info);

		//delete the program
		glDeleteProgram(program);

		//this didnt work
		assert(false);




	}
}