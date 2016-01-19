#ifndef __PARTICLE_RENDERER_H
#define __PARTICLE_RENDERER_H

#include <utility>
#include <vector>

#include "ShaderProgram.h"

struct VertexData
{
	float* initialPoints;
	unsigned int numOfFloats;
	unsigned int vertexCount;
	GLenum drawType;
};

struct ParticleAttributeData
{
	ParticleAttributeData(const char* tname, unsigned short tcount, unsigned short tstride, unsigned short toffset = 0, bool tnormalized = false, GLenum atribType = GL_FLOAT);
	ParticleAttributeData() {};
	unsigned short stride;
	unsigned short offset;
	unsigned short count;
	bool normalized;
	const char* name;
	GLenum type;
};

//this class will render all the particles you pass to it
//you can set the active size and attributes and give it an evaluation function for every draw to determine the particles
template<typename Functor, typename VertexFormat>
class ParticleRenderer
{
public:

	ParticleRenderer(VertexData data, ParticleAttributeData instanceAttrib, std::vector<ParticleAttributeData> attributes, Functor* functor, unsigned int maximum = 1000, unsigned short attributesPerVertex = 1);

	virtual ~ParticleRenderer();

	//adds a particle to the count
	void AddParticle(VertexFormat vert);

	//removes the back particle
	void RemoveParticle();

	//this will return the max attributes
	std::pair<VertexFormat*, unsigned int> GetAttributes();

	//this will set all the attributes of a specific size
	void SetAttributes(VertexFormat*, unsigned int size);

	//returns how many are active
	unsigned int GetActiveSize();

	//sets how many are active
	void SetActiveSize(unsigned int size);

	//set the working function
	void SetFunctor(Functor* functor);

	//get the working function
	Functor* GetFunctor();

	//render using this program
	void Render(ShaderProgram* program);
private:
	VertexFormat* m_AttributeData;
	Functor* m_Functor;
	unsigned int m_VertexVBO;
	unsigned int m_AttributeDataVBO;
	unsigned int m_Count;
	unsigned int m_VertexCount;
	unsigned int m_MaxSize;
	unsigned short m_AttributesPerVert;
	std::vector<ParticleAttributeData> m_Attributes;
	ParticleAttributeData m_VertexAttrib;
	GLenum m_DrawType;
};


template<typename Functor, typename VertexFormat>
ParticleRenderer<Functor, VertexFormat>::ParticleRenderer(VertexData data, ParticleAttributeData instanceAttrib, std::vector<ParticleAttributeData> attributes, Functor* functor, unsigned int maximum, unsigned short attributesPerVertex):
m_AttributeDataVBO(0), m_VertexVBO(0), m_AttributesPerVert(0), m_Functor(nullptr), m_VertexCount(0)
{
	//set up the initial data
	glGenBuffers(1, &m_VertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	assert(data.numOfFloats != 0 && data.vertexCount != 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) *data.numOfFloats* data.vertexCount, data.initialPoints, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//create the buffer
	glGenBuffers(1, &m_AttributeDataVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_AttributeDataVBO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//set up the members
	m_Functor = functor;
	m_AttributesPerVert = attributesPerVertex;

	m_MaxSize = maximum;

	m_AttributeData = New VertexFormat[m_MaxSize];

	m_Attributes = std::move(attributes);
	m_VertexAttrib = instanceAttrib;
	m_VertexCount = data.vertexCount;

	m_DrawType = data.drawType;


}

template<typename Functor, typename VertexFormat>
ParticleRenderer<Functor, VertexFormat>::~ParticleRenderer()
{
	glDeleteBuffers(1, &m_VertexVBO);
	glDeleteBuffers(1, &m_AttributeDataVBO);
	//delete the attribute data
	SafeDeleteArray(m_AttributeData);
}

//adds a particle to the count

template<typename Functor, typename VertexFormat>
void ParticleRenderer<Functor, VertexFormat>::AddParticle(VertexFormat vert)
{
	if (m_Count == m_MaxSize)
	{
		return;
	}
	//add a new vertex
	m_AttributeData[m_Count] = vert;
	m_Count++;
	glBindBuffer(GL_ARRAY_BUFFER, m_AttributeDataVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_Count, m_AttributeData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//removes the back particle
template<typename Functor, typename VertexFormat>
void ParticleRenderer<Functor, VertexFormat>::RemoveParticle()
{
	m_Count--;
	glBindBuffer(GL_ARRAY_BUFFER, m_AttributeDataVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexFormat) * m_Count, m_AttributeData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//this will return the max attributes
template<typename Functor, typename VertexFormat>
std::pair<VertexFormat*, unsigned int> ParticleRenderer<Functor, VertexFormat>::GetAttributes()
{
	return std::make_pair(m_AttributeData, m_MaxSize);
}

//this will set all the attributes of a specific size
template<typename Functor, typename VertexFormat>
void ParticleRenderer<Functor, VertexFormat>::SetAttributes(VertexFormat* data, unsigned int size)
{
	if (m_MaxSize < size)
	{
		size = m_MaxSize;
	}

	m_Count = size;
	//loop through and copy the data
	for (unsigned int i = 0; i < size; i++)
	{
		m_AttributeData[i] = data[i];
	}
	if (m_Count > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_AttributeDataVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_Count, m_AttributeData, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

//returns how many are active
template<typename Functor, typename VertexFormat>
unsigned int ParticleRenderer<Functor, VertexFormat>::GetActiveSize()
{
	return m_Count;
}

//sets how many are active
template<typename Functor, typename VertexFormat>
void ParticleRenderer<Functor, VertexFormat>::SetActiveSize(unsigned int size)
{
	
	m_Count = m_MaxSize >= size? size:m_MaxSize;
}

//set the working function
template<typename Functor, typename VertexFormat>
void ParticleRenderer<Functor, VertexFormat>::SetFunctor(Functor* functor)
{
	m_Functor = functor;
}

//get the working function
template<typename Functor, typename VertexFormat>
Functor* ParticleRenderer<Functor, VertexFormat>::GetFunctor()
{
	return m_Functor;
}

template<typename Functor, typename VertexFormat>
void ParticleRenderer<Functor, VertexFormat>::Render(ShaderProgram* program)
{
	//evaluate the current conditions
	m_Functor->Evaluate(this);

	if (m_Count <= 0)
	{
		return;
	}

	//bind the instance vbo and set its attribute
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	int vertloc = glGetAttribLocation(program->GetProgram(), m_VertexAttrib.name);
	if (vertloc != -1)
	{
		glVertexAttribPointer(vertloc, m_VertexAttrib.count, m_VertexAttrib.type, m_VertexAttrib.normalized, 
			m_VertexAttrib.stride, (void*)m_VertexAttrib.offset);
		glEnableVertexAttribArray(vertloc);
	}
	//setup all the attribute data
	glBindBuffer(GL_ARRAY_BUFFER, m_AttributeDataVBO);
	//make sure to reserve so we dont have to resize
	std::vector<int> locations;
	locations.reserve(m_Attributes.size());

	//loop through all the attributes
	for (int i = 0; i < m_Attributes.size(); i++)
	{
		locations.emplace_back();
		//get the location and set the attributes
		locations[i] = glGetAttribLocation(program->GetProgram(), m_Attributes[i].name);
		if (locations[i] != -1)
		{
			glVertexAttribPointer(locations[i], m_Attributes[i].count, m_Attributes[i].type, m_Attributes[i].normalized, m_Attributes[i].stride, (void*)m_Attributes[i].offset);
			glEnableVertexAttribArray(locations[i]);
			glVertexAttribDivisor(locations[i], m_AttributesPerVert);
		}
	}

	//draw the instanced particles
	glDrawArraysInstanced(m_DrawType, 0, m_VertexCount, m_Count);

	//reset the divisors to 0
	for (unsigned int i = 0; i < locations.size(); i++)
	{
		if (locations[i] != -1)
		{
			glVertexAttribDivisor(locations[i], 0);
		}
	}

}


#endif //__PARTICLE_RENDERER_H