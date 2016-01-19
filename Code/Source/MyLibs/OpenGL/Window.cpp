#include "Window.h"
#include "GL\GLExtensions.h"
#include <iostream>

static ResizeFunction s_Resize = DefaultResize;
static EventFunction s_Event = DefaultEventHandling;
static Window* s_Window = nullptr;

LRESULT CALLBACK ProcessEvents(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        if (s_Window != nullptr)
        {
            //clear the active flag
            s_Window->ClearFlag(Active);
            return 0;
        }
        break;
    case WM_SIZE:
        //get the size of the window
        RECT rect;
        GetWindowRect(hWnd, &rect);
		(*s_Resize)(LOWORD(lParam), HIWORD(lParam));
        //set the dimensions of the window
        if (s_Window != nullptr)
        {
            s_Window->m_Width = LOWORD(lParam);
            s_Window->m_Height = HIWORD(lParam);
        }
        return 0;
        
		
    }
    return (*s_Event)(hWnd, uMsg, wParam, lParam);
}

Window::Window() :m_Flags(0), m_HInstance(0), m_HWnd(0),
m_HDeviceContext(0),
m_HRenderingContext(0),
m_Width(-1.0f),
m_Height(-1.0f)
{

}
Window::~Window()
{
    //kill the window
    KillWindow();
}
bool Window::InitWindow(char* title, int width, int height, bool fullscreenflag, int colorbits, int zbits, int stencilbits)
{
    m_Width = static_cast<float>(width);
    m_Height = static_cast<float>(height);

	GLuint pixelFormat;

	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;

	RECT windowRect;
	windowRect.left = (long)0;
    windowRect.right = (long)width;
    windowRect.top = (long)0;
    windowRect.bottom = (long)height;

	m_Flags = m_Flags | (FullScreen * fullscreenflag);

	m_HInstance = GetModuleHandle(0); //grab and instance for out window

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //redraw when move, own the dc
	wc.lpfnWndProc = (WNDPROC)ProcessEvents; // set up the callback for the window

	wc.cbClsExtra = 0; //no extra data
	wc.cbWndExtra = 0; //no extra data
	wc.hInstance = m_HInstance; //set the instance

	wc.hIcon = LoadIcon(0, IDI_WINLOGO); //load the default icon
	wc.hCursor = LoadCursor(0, IDC_ARROW); //set up the arrow

	wc.hbrBackground = 0; //no back for opengl
	wc.lpszMenuName = 0; // NO MENU!
	
	wc.lpszClassName = "OpenGl";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "Failed to register the window class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if ((m_Flags & FullScreen) == FullScreen)
	{
		DEVMODE dmScreenSettings; //device mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); //CLEAR DAT MEMORY x)
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // size of structure
		dmScreenSettings.dmPelsWidth = width; //selected screen width
		dmScreenSettings.dmPelsHeight = height; //screen height
		dmScreenSettings.dmBitsPerPel = colorbits; //selected bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(0, "The Requested fullscreen mode is not supported by\nyour video card. Use Windowed mode instead?", "", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				m_Flags = m_Flags ^ FullScreen;
			}
			else
			{
				MessageBox(0, "Program will now close", "ERROR", MB_OK | MB_ICONSTOP);
				return false;
			}
		}
	}

	if ((m_Flags & FullScreen) == FullScreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(false);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle); // adjust window to requested size

	if (!(m_HWnd = CreateWindowEx(dwExStyle,
		"OpenGl",
		title,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
		0, 0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		0,
		0,
		m_HInstance,
		0)))
	{
		KillWindow();
		MessageBox(0, "Window creation failed", "ERROR", MB_OK || MB_ICONEXCLAMATION);
		return false;
	}

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // Size Of This Pixel Format Descriptor
		1,                              // Version Number
		PFD_DRAW_TO_WINDOW |            // Format Must Support Window
		PFD_SUPPORT_OPENGL |          // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,             // Must Support Double Buffering
		PFD_TYPE_RGBA,                  // Request An RGBA Format
		colorbits,                      // Select Our Color Depth
		0, 0, 0, 0, 0, 0,               // Color Bits Ignored
		0,                              // No Alpha Buffer
		0,                              // Shift Bit Ignored
		0,                              // No Accumulation Buffer
		0, 0, 0, 0,                     // Accumulation Bits Ignored
		zbits,                          // Bits for Z-Buffer (Depth Buffer)
		stencilbits,                    // Stencil bits
		0,                              // No Auxiliary Buffer
		PFD_MAIN_PLANE,                 // Main Drawing Layer
		0,                              // Reserved
		0, 0, 0                         // Layer Masks Ignored
	};



	if (!(m_HDeviceContext = GetDC(m_HWnd)))
	{
		KillWindow();
		MessageBox(0, "Can't find a suitable pixel format", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!(pixelFormat = ChoosePixelFormat(m_HDeviceContext, &pfd))) // Did Windows Find A Matching Pixel Format?
	{
		KillWindow();
		MessageBox(0, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	if (!SetPixelFormat(m_HDeviceContext, pixelFormat, &pfd)) // Are We Able To Set The Pixel Format?
	{
		KillWindow();
		MessageBox(0, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	if (!(m_HRenderingContext = wglCreateContext(m_HDeviceContext))) // Are We Able To Get A Rendering Context?
	{
		KillWindow();
		MessageBox(0, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	if (!wglMakeCurrent(m_HDeviceContext, m_HRenderingContext)) // Try To Activate The Rendering Context
	{
		KillWindow();
		MessageBox(0, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	ShowWindow(m_HWnd, SW_SHOW);
	SetForegroundWindow(m_HWnd);
	SetFocus(m_HWnd);


	m_Flags = m_Flags | Active;

	//initialize the extensions
	OpenGL_InitExtensions();
	//ennable alpha blending
	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;

	
}
void Window::KillWindow()
{
	if ((m_Flags & FullScreen) == FullScreen)
	{
		ChangeDisplaySettings(0, 0);
		ShowCursor(true);
	}

	if (m_HRenderingContext)
	{
		if (!wglMakeCurrent(0, 0))
		{
			MessageBox(0, "Release Of Device Context And Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_HRenderingContext))
		{
			MessageBox(0, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

	}
    m_HRenderingContext = 0;

	if (m_HDeviceContext && !ReleaseDC(m_HWnd, m_HDeviceContext))
	{
		MessageBox(0, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
    m_HDeviceContext = 0;

	if (m_HWnd && !DestroyWindow(m_HWnd))
	{
		MessageBox(0, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
    m_HWnd = 0;

	if (!UnregisterClass("OpenGL", m_HInstance))
	{
		MessageBox(0, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
    m_HInstance = 0;
}

bool Window::IsFullscreen()
{
	return (m_Flags & FullScreen) == FullScreen;
}
bool Window::IsActive()
{
	return (m_Flags & Active) == Active;
}

void Window::SetFlags(Flags flags)
{
	m_Flags = m_Flags | flags;
}
void Window::ClearFlags()
{
	m_Flags = 0;
}

bool Window::CheckFlags(Flags flags)
{
	return (m_Flags & flags) == flags;
}


void Window::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
void Window::Display()
{
	SwapBuffers(m_HDeviceContext);
	CheckForGLErrors();
}

void Window::Run()
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		//if the message is to quit set done to true
		if (msg.message == WM_QUIT)
		{
			//makes sure the flag gets set to false
			m_Flags = m_Flags | Active;
			m_Flags = m_Flags ^ Active;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
}

//clear a flag
void Window::ClearFlag(Flags flag)
{
    //flip the flag to true
    m_Flags = m_Flags | flag;
    //invert it
    m_Flags = m_Flags ^ flag;
}

void DefaultResize(unsigned int w, unsigned int h)
{
    glViewport(0, 0, w, h);
}


void SetResizeCallback(ResizeFunction function)
{
    s_Resize = function;
}

void SetEventCallback(EventFunction function)
{
    s_Event = function;
}

LRESULT DefaultEventHandling(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void SetWindow(Window* window)
{
    s_Window = window;
}

