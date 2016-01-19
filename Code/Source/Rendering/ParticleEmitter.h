#ifndef __PARTICLE_EMITTER_H
#define __PARTICLE_EMITTER_H

#include "RenderComponent.h"
#include "Time\Timer.h"
#include "MyLibs\OpenGL\ShaderProgram.h"
#include "MyLibs\OpenGL\ParticleRenderer.h"

namespace WE
{
    //this class will emit paticles into a lightning strike shape
	class ParticleEmitter : public RenderComponent
	{
	public:
		ParticleEmitter();

		virtual ~ParticleEmitter();

		
		void Render(RenderState* state);

		//set the state of the render component
		void SetState(RenderState* state);

		//sets the frequency of the emitter
		void SetFrequency(double frequency);

		//returns the frequency of the emitter
		double GetFrequency();

		//sets the number of beams
		void SetNumberOfBeams(unsigned char number);

		//set number of links
		void SetLinksPerBeam(unsigned short number);

		//set the length of the beam
		void SetLength(float length);

		//set the amplitude of the beam
		void SetAmplitude(float amplitude);

		//set the color of the beams
		void SetColor(vec4f color);

		//set the width of the beams
		void SetWidth(float width);
	private:
		static const std::string SHADERS[2];
		static const double INITIAL_FREQUENCY;
		static const unsigned int RESIZE_ITERATIONS;

		struct VertexFormat
		{
			vec4f color;
			vec3f positionA;
			vec3f positionB;
		};

		friend class ParticleManager;

		class ParticleManager
		{
		public:
			//set the parent for data
			ParticleManager(ParticleEmitter* emitter);

			//evaluate what action to take for the particle emitter
			void Evaluate(ParticleRenderer<ParticleManager, VertexFormat>* renderer);

		private:
			ParticleEmitter* m_Parent;
		};


		ParticleManager m_Manager;

		ShaderProgram m_Shader;

		ParticleRenderer<ParticleManager, VertexFormat>* m_ParticleRenderer;

		Timer m_Timer;

		vec4f m_Color;

		unsigned int m_Beams;
		unsigned int m_Links;
		float m_Length;
		float m_Amplitude;
		float m_Width;

	};
}

#endif //__PARTICLE_EMITTER_H