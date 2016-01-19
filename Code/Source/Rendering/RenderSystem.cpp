#include "RenderSystem.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "Movement\TransformComponent.h"
#include "Core\Core.h"
#include <iostream>

namespace WE
{
	static ArrayList<CameraComponent*> s_ResizeCameras;
    static DeferedRenderer* s_Renderer;

	void Resize(unsigned int width, unsigned int height)
	{
		//loop through all the cameras and resize them
		for (unsigned int i = 0; i < s_ResizeCameras.Size(); i++)
		{
            s_ResizeCameras[i]->SetRealScreenSize(vec2f(static_cast<float>(width), static_cast<float>(height)));
		}
        s_Renderer->ResizeTextures(width, height);
       
	}

	const unsigned int RenderSystem::NUMBER_OF_MATRICES = 3;

	//create the system
    RenderSystem::RenderSystem(Core* core) :m_Core(core)
	{
		//initialize the window
		m_Window.InitWindow(const_cast<char*>(Config::WINDOW_NAME.c_str()), (int)Config::WINDOW_SIZE.x, (int)Config::WINDOW_SIZE.y);

		//set the current window to this window
		SetWindow(&m_Window);
		//set the resize callback
		SetResizeCallback(&Resize);


        m_Renderer = New DeferedRenderer(Config::WINDOW_SIZE.x, Config::WINDOW_SIZE.y, (std::string(Config::ASSET_PATH) + "/Shaders/").c_str());
        s_Renderer = m_Renderer;

		m_MatrixBuffer = New UniformBuffer(3 * sizeof(float) * 16, 
        { std::make_pair("u_MMatrix", sizeof(float) * 16), std::make_pair("u_VPMatrix", sizeof(float) * 16), std::make_pair("u_NormalMatrix", sizeof(float) * 16) },
		"Matrices");

	}
	//destroy the system
	RenderSystem::~RenderSystem()
	{
		
		SafeDelete(m_MatrixBuffer);
			

        
        SafeDelete(m_Renderer);
            
        
	}

	//notify the system of a new entity or a new component
	void RenderSystem::NotifyActiveScene(Scene* scene)
	{

		ArrayList<Entity*>* entities = scene->GetEntities();

		for (int i = m_Scenes.Size() - 1; i >= 0; i--)
		{
			m_Scenes.PopBack();
		}

		for (int i = s_ResizeCameras.Size() -1; i >= 0; i--)
		{
			s_ResizeCameras.PopBack();
		}

		for (uint32 i = 0; i < entities->Size(); i++)
		{
			Entity* entity = (*entities)[i];

				//if the entity has a transform and a render or camera add it
			if (entity->HasType<SceneGraphComponent>())
			{
				//get the name and set the scene
				SceneGraphComponent* scene = entity->GetComponent < SceneGraphComponent>();
				m_Scenes.PushBack(scene);
			}
			//if there is a camera
			if (entity->HasType<CameraComponent>())
			{
				//add the camera to the resize cams
				CameraComponent* cam = entity->GetComponent<CameraComponent>();
				s_ResizeCameras.PushBack(cam);
			}

		}
	}

	//get the systems callbacks
	std::vector<SystemCallback*> RenderSystem::GetCallbacks()
	{
		//return the render callback
		return { New SystemCallback(&RenderSystem::Render, this) };
	}

	void RenderSystem::Render()
	{

		//if the window isnt active
		if (!m_Window.IsActive())
		{
			m_Core->SetExit(true);
		}
		//clear the window
		m_Window.Clear();

		//run the window
		m_Window.Run();
		

		MatrixStackf stack;
        MatrixStackf normalStack;

        m_Renderer->GeometryPass();
		//loop through the scenes
		for (int i = 0; i < m_Scenes.Size(); i++)
        {
            stack.Clear();
            normalStack.Clear();
            m_Scenes[i]->Render(&RenderState(&stack, m_MatrixBuffer, &normalStack));
        }

		//display the window
		//m_Window.Display();
	}

    DeferedRenderer* RenderSystem::GetRenderer()
    {
        return m_Renderer;
    }

    Window* RenderSystem::GetWindow()
    {
        return &m_Window;
    }
}