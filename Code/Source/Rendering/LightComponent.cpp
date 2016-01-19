#include "LightComponent.h"

namespace WE
{
    LightComponent::LightComponent(const char* vert, const char* frag):
        m_Program((std::string(Config::ASSET_PATH) + "/Shaders/" + vert).c_str(), (std::string(Config::ASSET_PATH) + "/Shaders/" +frag).c_str())
    {
    }

    //enable the light
    void LightComponent::Enable()
    {
        m_Enabled = true;
    }
    //disable the light
    void LightComponent::Disable()
    {
        m_Enabled = false;
    }

   
}