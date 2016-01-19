#ifndef __DIRECTIONAL_LIGHT_H
#define __DIRECTIONAL_LIGHT_H

#include "LightComponent.h"

namespace WE
{
    //directional lights will light things as if they were from an infinite distance,
    //you can set the unit vector to use this light
    class DirectionalLight : public LightComponent
    {
    public:
        //create the light
        DirectionalLight();

        void SetDirection(vec3f direction);

        vec3f GetDirection();

        void Render(DeferedRenderer* renderer) override;

    private:
        static const std::string SHADERS[];

        vec3f m_Direction;
    };
}

#endif //__DIRECTIONAL_LIGHT_H