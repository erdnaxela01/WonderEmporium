#ifndef __LABEL_COMPONENT_H
#define __LABEL_COMPONENT_H

#include "MyLibs\OpenGL\Font.h"
#include "UIComponent.h"

namespace WE
{
    //this will handle fonts and draw them onto the screen as if they were UI elements
    class LabelComponent : public UIComponent
    {
    public:
        static const std::string SHADERS[2];

        LabelComponent(vec2f dimension, vec2i num, std::string format, std::string path);

        virtual ~LabelComponent();

        //return the font
        Font& GetText();

        //render the font
        void Render(UniformBuffer* buffer) override;
    private:
        Font m_Font;
    };
}


#endif //__LABEL_COMPONENT_H