#ifndef __UNIFORM_BUFFER_H
#define __UNIFORM_BUFFER_H

#include <map>
#include <vector>

//this class is a uniform buffer object
//it holds all uniform values in one place and all a shader needs to do to access them
//is to register itself as a shader that wants them
class UniformBuffer
{
public:
	using Data = std::vector < std::pair<const char*, unsigned int> > ;

	//create the buffer object
	//and get the index
	UniformBuffer(unsigned int size, Data uniforms, const char* name);

	virtual ~UniformBuffer();

	//non copyable
	UniformBuffer(UniformBuffer&) = delete;
	UniformBuffer(UniformBuffer&&) = delete;
	UniformBuffer& operator=(UniformBuffer&) = delete;
	UniformBuffer& operator=(UniformBuffer&&) = delete;

	//set the values in the buffer
	void SetValues();

	//set the data at the specific uniform name location
	//make sure to only give the right size or else youll override
	//another uniforms data
	void SetUniform(const char* name, void* data, unsigned int size, unsigned int stride);

	//register a shader
	void RegisterShader(unsigned int program);
private:

	unsigned int m_Buffer;
	unsigned int m_Count;
	unsigned int m_Size;

	void* m_Data;

	std::map<const char*, unsigned int> m_Uniforms;
	static unsigned int s_Index;

	const std::string m_Name;

};


#endif //__UNIFORM_BUFFER_H