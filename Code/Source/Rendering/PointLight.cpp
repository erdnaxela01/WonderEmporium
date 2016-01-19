#include "PointLight.h"


namespace WE
{
	const std::string PointLight::SHADERS[2] = { "PointLight.LVert", "PointLight.LFrag" };

	//set the transform matrix
	PointLight::PointLight(Entity* entity) :LightComponent(SHADERS[0].c_str(), SHADERS[1].c_str())
	{
		assert(entity->HasType<TransformComponent>());

		//set the transform component
		m_MyTransform = entity->GetComponent<TransformComponent>();
	}

	//set the radius of the light
	void PointLight::SetRadius(float radius)
	{
		m_Radius = radius * Config::s_PPM;
	}

	//return the radius of the light
	float PointLight::GetRadius()
	{
		return m_Radius;
	}

	//render the light
	void PointLight::Render(DeferedRenderer* renderer)
	{
		m_Program.UseProgram();

		//set both light uniforms
		int loc = glGetUniformLocation(m_Program.GetProgram(), "u_Position");
		vec3f pos = m_MyTransform->GetPosition() * Config::s_PPM;
		glUniform3f(loc, -pos.x, pos.y, pos.z);

		loc = glGetUniformLocation(m_Program.GetProgram(), "u_Radius");
		glUniform1f(loc, m_Radius * Config::s_PPM);

		//render the light
		renderer->RenderLight(&m_Program);
	}
}