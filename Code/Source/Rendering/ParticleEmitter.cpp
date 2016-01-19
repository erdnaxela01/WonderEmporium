#include "ParticleEmitter.h"
#include <random>
#include <time.h>

namespace WE
{
	const std::string ParticleEmitter::SHADERS[2] = { "Beam.GVert", "Beam.GFrag" };
	const double ParticleEmitter::INITIAL_FREQUENCY = 1.0;
	const unsigned int ParticleEmitter::RESIZE_ITERATIONS = 4;


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
		unsigned short stride;
		unsigned short offset;
		unsigned short count;
		bool normalized;
		const char* name;
		GLenum type;
	};

	ParticleEmitter::ParticleEmitter() :
		m_Shader((std::string(Config::ASSET_PATH) + "/Shaders/" + SHADERS[0]).c_str(), (std::string(Config::ASSET_PATH) + "/Shaders/" + SHADERS[1]).c_str()),
		m_Manager(this), m_ParticleRenderer(nullptr), m_Links(5), m_Beams(1), m_Width(1.0f)
	{
		float points[] = 
		{
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f
		};

		::VertexData data;
		data.drawType = GL_TRIANGLE_STRIP;
		data.initialPoints = points;
		data.numOfFloats = 3;
		data.vertexCount = 4;

		//setup the particle renderer
		m_ParticleRenderer = New ParticleRenderer < ParticleManager, VertexFormat>(data, ::ParticleAttributeData("i_Position", 3, sizeof(float) * 3),
		{ ::ParticleAttributeData("i_PointB", 3, sizeof(VertexFormat), sizeof(float) * 7),::ParticleAttributeData("i_PointA", 3, sizeof(VertexFormat), sizeof(float) * 4), ::ParticleAttributeData("i_Color", 4, sizeof(VertexFormat)) },
		&m_Manager, 1000, 1);

		m_Timer.SetInterval(INITIAL_FREQUENCY);

		srand(time(0));

		m_Color = vec4f(1.0f,1.0f, 1.0f, 1.0f);


	}

	ParticleEmitter::~ParticleEmitter()
	{
		SafeDelete(m_ParticleRenderer);
	}


	void ParticleEmitter::Render(RenderState* state)
	{
		glDisable(GL_DEPTH_TEST);
		
		SetState(state);

		int loc = glGetUniformLocation(m_Shader.GetProgram(), "u_Scale");
		glUniform1f(loc, m_Width);

		state->buffer->RegisterShader(m_Shader.GetProgram());
		state->buffer->SetValues();

		//use the texture
		m_ParticleRenderer->Render(&m_Shader);
		glEnable(GL_DEPTH_TEST);

	}

	//set the state of the render component
	void ParticleEmitter::SetState(RenderState* state)
	{
		//set the matrix
		m_Shader.UseProgram();

		state->buffer->SetUniform("u_MMatrix", state->stack->Top().GetArray(), 16, sizeof(float));
	}

	//sets the frequency of the emitter
	void ParticleEmitter::SetFrequency(double frequency)
	{
		m_Timer.SetInterval(frequency);
	}

	//returns the frequency of the emitter
	double ParticleEmitter::GetFrequency()
	{
		return m_Timer.GetInterval();
	}

	//sets the number of beams
	void ParticleEmitter::SetNumberOfBeams(unsigned char number)
	{
		m_Beams = number;
	}

	//set number of links
	void ParticleEmitter::SetLinksPerBeam(unsigned short number)
	{
		m_Links = number;
	}


	//set the parent for data
	ParticleEmitter::ParticleManager::ParticleManager(ParticleEmitter* emitter) :m_Parent(emitter)
	{

	}

	//evaluate what action to take for the particle emitter
	void ParticleEmitter::ParticleManager::Evaluate(ParticleRenderer<ParticleManager, VertexFormat>* renderer)
	{
		//TODO: change this to use the particle renderes particles instead of creating and copying
		if (!m_Parent->m_Timer.PassedInterval())
		{
			return;
		}
		std::vector<VertexFormat> accumulation;

		for (unsigned int j = 0; j < m_Parent->m_Beams; j++)
		{
			//reserve the needed points
			std::vector<VertexFormat> points;
			points.reserve(m_Parent->m_Links);

			//get points between -1 and 1 times the amplitude
			for (unsigned int i = 0; i < m_Parent->m_Links; i++)
			{
				points.emplace_back();
				
				float y = (((float)(rand() % 2000) / 1000.0f) - 1.0f) * m_Parent->m_Amplitude;
				points[i].positionA.y = y;
			}

			float lineLength = 1.0f / m_Parent->m_Links * m_Parent->m_Length;

			//set up the initial line lengths
			for (unsigned int i = 0; i < m_Parent->m_Links; i++)
			{
				points[i].positionA.x = lineLength;
			}

			//vary the line lengths
			for (unsigned int i = 0; i < RESIZE_ITERATIONS * m_Parent->m_Links; i++)
			{
				unsigned int index1 = (rand() % points.size());
				unsigned int index2 = (rand() % points.size());

				//get a number betweem 0 and 0.25
				float shrink = (float)(rand() % 100) / 1000.0f;

				//remove from one and add to the other
				points[index1].positionA.x -= points[index1].positionA.x*shrink;
				points[index2].positionA.x += points[index1].positionA.x*shrink;
				
			}

			points[0].positionA.x = 0.0f;
			points[0].positionA.y = 0.0f;
			//setup all the points between the two sentinal points
			for (unsigned int i = 1; i < points.size(); i++)
			{
				points[i].positionA.x += points[(i-1)].positionA.x;
				points[i].color = m_Parent->m_Color;
				points[i].positionB = points[i - 1].positionA;
			}
			points[0].color = m_Parent->m_Color;

			//set up the points
			points[points.size() - 1].positionA.x = 1.0f * m_Parent->m_Length;
			points[points.size() - 1].positionA.y = 0.0f;

			//add to the accumulation
			accumulation.insert(accumulation.end(), points.begin(), points.end());
		}

		//pass the attributes to the particle renderer
		renderer->SetAttributes(accumulation.data(), accumulation.size());


		
	}

	void ParticleEmitter::SetLength(float length)
	{
		m_Length = length * Config::s_PPM;
	}

	void ParticleEmitter::SetAmplitude(float amplitude)
	{
		m_Amplitude = amplitude * Config::s_PPM;
	}

	void ParticleEmitter::SetColor(vec4f color)
	{
		m_Color = color;
	}

	//set the width of the beams
	void ParticleEmitter::SetWidth(float width)
	{
		m_Width = width* Config::s_PPM;
	}
}