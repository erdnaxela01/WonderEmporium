#include "ModelComponent.h"
#include "MyLibs\OpenGL\ModelParser.h"


namespace WE
{
	ModelComponent::ModelComponent(const char* model, vec3f dimensions, std::vector<const char*> name) :
		m_Program((std::string(Config::ASSET_PATH) + "/Shaders/" + name[0]).c_str(), (std::string(Config::ASSET_PATH) + "/Shaders/" + name[1]).c_str())
	{
		//get the model data
		if (model != "")
		{
			Parser::Parse(Paths((std::string(Config::ASSET_PATH) + "/Images/").c_str(),
				(std::string(Config::ASSET_PATH) + "/Meshes/").c_str(), model),
				Attributes("i_VertexPos", "i_Normal", "i_TexCoord"), &m_Model, dimensions.x, dimensions.y, dimensions.z);
		}
	}


	ModelComponent::~ModelComponent()
	{
	}

	void ModelComponent::Render(RenderState* state)
	{
		//set the render state
		SetState(state);
		state->buffer->RegisterShader(m_Program.GetProgram());
		state->buffer->SetValues();
		//use the texture
		m_Model.Render(&m_Program, MaterialData("u_AmbientUpper", "u_AmbientLower", "u_Diffuse", "u_Specular", "u_Illumination", "u_Texture"));
	}

	void ModelComponent::SetState(RenderState* state)
	{
		//set the matrix
        m_Program.UseProgram();

		state->buffer->SetUniform("u_MMatrix", state->stack->Top().GetArray(), 16, sizeof(float));

        state->buffer->SetUniform("u_NormalMatrix", state->normalStack->Top().Transpose().GetArray(), 16, sizeof(float));
	}

	ShaderProgram* ModelComponent::GetProgram()
	{
		return &m_Program;
	}
}