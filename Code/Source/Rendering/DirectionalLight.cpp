#include "DirectionalLight.h"

namespace WE
{
    const std::string DirectionalLight::SHADERS[] = { "DirectionalLight.LVert", "DirectionalLight.LFrag" };
    //create the light
    DirectionalLight::DirectionalLight() :LightComponent(SHADERS[0].c_str(), SHADERS[1].c_str())
    {

    }

    void DirectionalLight::SetDirection(vec3f direction)
    {
        m_Direction = direction;
    }

    vec3f DirectionalLight::GetDirection()
    {
        return m_Direction;
    }

    void DirectionalLight::Render(DeferedRenderer* renderer)
    {
        //set the uniform then render the light
        m_Program.UseProgram();
        int loc = glGetUniformLocation(m_Program.GetProgram(), "u_Direction");
        glUniform3f(loc, -m_Direction.x, m_Direction.y, m_Direction.z);
        
        renderer->RenderLight(&m_Program);

    }
}
