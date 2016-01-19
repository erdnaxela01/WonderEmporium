#ifndef __MODEL_COMPONENT_H
#define __MODEL_COMPONENT_H

#include "RenderComponent.h"

namespace WE
{
    //this class will hold a model and will get draw by the rendering system
    //if you pass nothing to the constructor it will be an emepty model
	class ModelComponent : public RenderComponent
	{
	public:
		ModelComponent(const char* model, vec3f dimensions = vec3f(1.0f, 1.0f, 1.0f),
			std::vector<const char*> shaderNames = { "GeometryDefault.GVert", "GeometryDefault.GFrag" });

		virtual ~ModelComponent();

		//render a sprite
		void Render(RenderState* state);

		//set the state of the render component
        virtual void SetState(RenderState* state);

		//return the program set with the render component
		ShaderProgram* GetProgram();
	private:
		Model m_Model;
		ShaderProgram m_Program;
	};
}


#endif //__MODEL_COMPONENT_H