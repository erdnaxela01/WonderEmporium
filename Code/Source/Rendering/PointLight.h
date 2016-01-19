#ifndef __POINT_LIGHT_H
#define __POINT_LIGHT_H

#include "LightComponent.h"

namespace WE
{
    //this will render a point light
    //it will use the point light shader
	class PointLight : public LightComponent
	{
	public:
		//set the transform matrix
		PointLight(Entity* entity);

		//set the radius of the light
		void SetRadius(float radius);

		//return the radius of the light
		float GetRadius();

		//render the light
		void Render(DeferedRenderer* renderer) override;

	private:
		float m_Radius;
		TransformComponent* m_MyTransform;

		static const std::string SHADERS[2];

	};
}

#endif //__POINT_LIGHT_H