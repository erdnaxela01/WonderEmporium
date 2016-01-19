#ifndef __TRANSFORM_COMPONENT_H
#define __TRANSFORM_COMPONENT_H

namespace WE
{
	/*
	Careful with the transform component, if there is a physics component
	this wont update it
	//this class holds all the matrix values for the entity
	*/
	class TransformComponent
	{
	public:
		TransformComponent();

        virtual ~TransformComponent()  {};

		//set the position of the transform component
		virtual void SetPosition(vec3f pos);
		//get the position of the component
		virtual vec3f GetPosition();
		//set the rotation of the component
		virtual void SetRotation(vec3f rotation);
		//get the rotation of the component
		virtual vec3f GetRotation();
		//set the scale of the component
		void SetScale(vec3f scale);
		//get the scale of the component
		vec3f GetScale();

		//get the transform matrix
		virtual mat4f GetTransform();
		//get the inverse transform matrix
		virtual mat4f GetInverse();

	private:
		vec3f m_Position;
		vec3f m_Rotation;
		vec3f m_Scale;
	};
}

#endif //__TRANSFORM_COMPONENT_H