#include "DeferedRenderer.h"
#include <vector>

const char* DeferedRenderer::UNIFORM_TEXTURE_NAME = "u_Texture";



DeferedRenderer::DeferedRenderer(unsigned int width, unsigned int height, const char* shaderPath) :m_Width(width), m_Height(height), m_DepthTexture(0),
m_FinalVBO(0), m_FrameBuffer(0), m_LightFrameBuffer(0), m_LightTexture(0), m_RenderTextures()
{

	glGenBuffers(1, &m_FinalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_FinalVBO);

	//create the quad
	float quad[8] = 
	{
		-1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, quad, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//setup the geometry frame buffer
	{
		//create the frame buffer and bind it
		glGenFramebuffers(1, &m_FrameBuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FrameBuffer);
		//set the render and depth textures
		glGenTextures(TEXTURE_COUNT, m_RenderTextures);
		glGenTextures(1, &m_DepthTexture);

        glActiveTexture(GL_TEXTURE0);

		//setup all the textures
		for (int i = 0; i < TEXTURE_COUNT; i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_RenderTextures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_RenderTextures[i], 0);
		}

		//set up the depth texture
		glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);

		//set up the buffers
		GLenum buffers[TEXTURE_COUNT];
		for (int i = 0; i < TEXTURE_COUNT; i++)
		{
			buffers[i] = GL_COLOR_ATTACHMENT0 + i;
		}

		//draw the buffers
		glDrawBuffers(TEXTURE_COUNT, buffers);

		//error check the frame buffer
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", status);
			assert(false);
		}

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}


	{
		//generate the light frame buffer
		glGenFramebuffers(1, &m_LightFrameBuffer);

		//generate the light texture
		glGenTextures(1, &m_LightTexture);

		//bind the frame buffer as the active frame buffer
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_LightFrameBuffer);

		//create the texture
		glBindTexture(GL_TEXTURE_2D, m_LightTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_LightTexture, 0);

		//set the buffer
		GLenum buffer[1];
		buffer[0] = GL_COLOR_ATTACHMENT0;

		glDrawBuffers(1, buffer);

		//error check the frame buffer
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", status);
			assert(false);
		}

		//bind the oiriginal buffer
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	}
    

	//create the final shader
	m_Program = New ShaderProgram((std::string(shaderPath) + "FinalPass.FVert").c_str(), (std::string(shaderPath) + "FinalPass.FFrag").c_str());

}

void DeferedRenderer::ResizeTextures(unsigned int width, unsigned int height)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FrameBuffer);
	if (width == 0 && height == 0)
	{
		return;
	}
    //setup all the textures
    for (int i = 0; i < TEXTURE_COUNT; i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_RenderTextures[i]);
		
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_RenderTextures[i], 0);
    }

    //set up the depth texture
    glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);

    //set up the buffers
    GLenum buffers[TEXTURE_COUNT];
    for (int i = 0; i < TEXTURE_COUNT; i++)
    {
        buffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    //draw the buffers
    glDrawBuffers(TEXTURE_COUNT, buffers);

    //error check the frame buffer
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", status);
        assert(false);
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    //bind the frame buffer as the active frame buffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_LightFrameBuffer);

    //create the texture
    glBindTexture(GL_TEXTURE_2D, m_LightTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_LightTexture, 0);

    //set the buffer
    GLenum buffer[1];
    buffer[0] = GL_COLOR_ATTACHMENT0;

    glDrawBuffers(1, buffer);

    //error check the frame buffer
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", status);
        assert(false);
    }

    //bind the oiriginal buffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

DeferedRenderer::~DeferedRenderer()
{
	//delete all the textures and frame buffers
	glDeleteFramebuffers(1, &m_FrameBuffer);
	glDeleteFramebuffers(1, &m_LightFrameBuffer);
	glDeleteTextures(TEXTURE_COUNT, m_RenderTextures);
	glDeleteTextures(1, &m_DepthTexture);
	glDeleteTextures(1, &m_LightTexture);
    glDeleteBuffers(1, &m_FinalVBO);

    SafeDelete(m_Program);
}

//draw the geometry
void DeferedRenderer::GeometryPass()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FrameBuffer);

	//clear the color and depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	
	//glDisable(GL_MIPMAP);
	

}

//draw the lights
void DeferedRenderer::LightingPass()
{

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_LightFrameBuffer);
	//clear the color and depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);


	glDisable(GL_DEPTH_TEST);
	//make sure the pass adds to the lighting
	glEnable(GL_BLEND);
	//glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
	

}

void DeferedRenderer::RenderLight(ShaderProgram* program)
{

    program->UseProgram();
    glBindBuffer(GL_ARRAY_BUFFER, m_FinalVBO);

    std::string name = UNIFORM_TEXTURE_NAME;
    for (int i = 0; i < TEXTURE_COUNT; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_RenderTextures[i]);

        //set the uniform
        std::string names = (name + std::to_string(i)).c_str();
        int loc = glGetUniformLocation(program->GetProgram(), (name + std::to_string(i)).c_str());
        glUniform1i(loc, i);

    }
	

	//setup the attributes
	int loc = program->SetAttribute(Mesh::AttributeData("i_Position", 2, sizeof(float) * 2));


	//draw the quad

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (loc != -1)
	{
		glDisableVertexAttribArray(loc);
	}
}

//finalize the drawing
void DeferedRenderer::FinalPass()
{
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	//set the default shader
    m_Program->UseProgram();


	//will change to sky box code
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//

    //reset the blending function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //bind the quad
    glBindBuffer(GL_ARRAY_BUFFER, m_FinalVBO);

	//set the light accumulation texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_LightTexture);
	m_Program->SetTexture("u_LightTexture", 0);

	//set the diffuse texture
	glActiveTexture(GL_TEXTURE0 +1);
	glBindTexture(GL_TEXTURE_2D, m_RenderTextures[0]);
	m_Program->SetTexture("u_DiffuseTexture", 1);
	//setup the attributes
    int loc = m_Program->SetAttribute(Mesh::AttributeData("i_Position", 2, sizeof(float) * 2));

	//draw the quad
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	if (loc != -1)
	{
		glDisableVertexAttribArray(loc);
	}
}