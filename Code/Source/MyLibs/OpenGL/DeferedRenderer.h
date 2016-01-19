#ifndef __DEFERED_RENDERER_H
#define __DEFERED_RENDERER_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\GLExtensions.h"
#include "GL\glext.h"
#include "ShaderProgram.h"
#include "UniformBuffer.h"

#define TEXTURE_COUNT 3


//this guy will use a defered rendering scheme to render objects
//this means that values are stored in a texture and reread by following stages in the rendering
class DeferedRenderer
{
public:
	//set up the frame buffers
	DeferedRenderer(unsigned int width, unsigned int height, const char* shaderPath);

	virtual ~DeferedRenderer();

	//draw the geometry
	void GeometryPass();

	//draw the lights
	void LightingPass();

	//render a light
	void RenderLight(ShaderProgram* program);

	//finalize the drawing
	void FinalPass();

    void ResizeTextures(unsigned int width, unsigned int height);
private:
	static const char* UNIFORM_TEXTURE_NAME;


	unsigned int m_FrameBuffer;
	unsigned int m_LightFrameBuffer;
	unsigned int m_RenderTextures[TEXTURE_COUNT];
	unsigned int m_DepthTexture;
	unsigned int m_LightTexture;

	unsigned int m_Width;
	unsigned int m_Height;

	unsigned int m_FinalVBO;

	ShaderProgram* m_Program;

   // UniformBuffer* m_Buffer;

};

#endif //__DEFERED_RENERER_H