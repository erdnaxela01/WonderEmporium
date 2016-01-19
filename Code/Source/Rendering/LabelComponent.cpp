#include "LabelComponent.h"

namespace WE
{
	LabelComponent::LabelComponent(vec2f dimensions, vec2i num, std::string format, std::string path) :
        m_Font(dimensions.x, dimensions.y,num.x, num.y, format, (std::string(Config::ASSET_PATH) + "/Fonts/" + path).c_str())
    {

    }

    LabelComponent::~LabelComponent()
    {

    }

    //return the font
    Font& LabelComponent::GetText()
    {
        return m_Font;
    }

    //render the font
    void LabelComponent::Render(UniformBuffer* buffer)
    {
        //render the font
        UIComponent::Render(buffer);
        m_Font.Render(&m_Program);
    }
}