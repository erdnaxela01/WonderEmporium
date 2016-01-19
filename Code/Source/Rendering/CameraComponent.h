#ifndef __CAMERA_COMPONENT_H
#define __CAMERA_COMPONENT_H

#include "MyLibs\OpenGL\ShaderProgram.h"
#include "Movement\TransformComponent.h"
#include "RenderState.h"

namespace WE
{
    //this will render a camera
    //it will have a frustum and will setup the matrices to get them to work
	class CameraComponent
	{
	public:
		CameraComponent();

		virtual ~CameraComponent() {};
		//set the screen position of the camera
		void SetScreenPosition(vec2f pos);
		//get the screen position of the camera
		vec2f GetScreenPosition();
		//set the screen size of the camera in a normalized 0 to 1 range
		void SetScreenSize(vec2f size);
		//get the screen size of the camera
		vec2f GetScreenSize();
		//set the size of the camera in the world
		void SetWorldSize(vec2f size);
		//get the size of the camera in the world
		vec2f GetWorldSize();

        //set the depth of the camera
        void SetDepth(vec2f depth);
        //get the depth of the camera
        vec2f GetDepth();

        //set the field of vision
        //takes an angle in radians
        void SetFieldOfVision(float);
        //return the field of vision
        float GetFieldOfVision();
        //set the screen size in pixels
        void SetRealScreenSize(vec2f);
        //return the size of the camera in pixels
        vec2f GetRealScreenSize();

		//view the camera
		void View(RenderState* program);

        static const float CAMERA_COMPONENT_DEFAULT_FOV;
        static const vec2f CAMERA_COMPONENT_DEFAULT_DEPTH;

	private:
		vec2f m_ScreenPositon;
		vec2f m_ScreenSize;
        vec2f m_RealScreenSize;
		vec2f m_WorldSize;
        vec2f m_Depth;
        float m_FOV;
	};
}

#endif //__CAMERA_COMPONENT_H