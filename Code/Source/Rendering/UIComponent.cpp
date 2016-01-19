#include "UIComponent.h"

namespace WE
{
    UIComponent::UIComponent(const char* vert, const char* frag):
        m_Program((std::string(Config::ASSET_PATH) + "/Shaders/" + vert).c_str(), (std::string(Config::ASSET_PATH) + "/Shaders/" + frag).c_str())
    {

    }

    UIComponent::~UIComponent()
    {

    }

    //set the normalized screen position of the ui object
    void UIComponent::SetScreenPosition(vec2f position)
    {
        m_ScreenPosition = position;
    }

    //get the normalized screen position of the object
    vec2f UIComponent::GetScreenPosition()
    {
        return m_ScreenPosition;
    }

    //render the ui ob=ject
    void UIComponent::Render(UniformBuffer* buffer)
    {
        //set the uniform
        m_Program.UseProgram();
        float arr[2];
        arr[0] = m_ScreenPosition.x;
        arr[1] = m_ScreenPosition.y;
        //set the uniform and register the shader
        buffer->SetUniform("u_ScreenPosition", arr, 2, sizeof(float));
        buffer->RegisterShader(m_Program.GetProgram());
        buffer->SetValues();

    }
}