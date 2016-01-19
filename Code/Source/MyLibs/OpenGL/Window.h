#ifndef __WINDOW_H
#define __WINDOW_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

enum Flags
{
	None		= 0x00, //00000000
	FullScreen	= 0x01, //00000001
	Active		= 0x02  //00000010
	//0x04
	//0x08
	//0x11
	//0x22

};


using ResizeFunction = void(*)(unsigned int, unsigned int);
using EventFunction = LRESULT(*)(HWND, UINT, WPARAM, LPARAM);

//this class handles the windows api in order to create a window and handle events
//it will init the window and keep a few useful variables
class Window
{
public:
    friend LRESULT CALLBACK ProcessEvents(HWND, UINT, WPARAM, LPARAM);

    //initializes all variables
    Window();

	//destroys all the stuff
	virtual ~Window();

	//creates the opengl window
	bool InitWindow(char* title,int width, int height, bool fullscreenflag = false, int colorbits = 32, int zbits = 31, int stencilbits = 1);

	//check if the window is fullscreen
	bool IsFullscreen();

	//check if the screen is active
	bool IsActive();

	//set flags onto the window
	void SetFlags(Flags flags);

	//clear all flags to 0
	void ClearFlags();

	//check if there is a flag
	bool CheckFlags(Flags flags);

	//clear the window
	void Clear(float red = 0.0f, float green = 0.0f, float blue = 0.75f, float alpha = 1.0f);

	//display the window
	void Display();

	//Call this every loop
	void Run();

    //clear a flag
    void ClearFlag(Flags flag);

private:

    //destroy all the opengl stuff
    void KillWindow();

	BYTE m_Flags;

	HINSTANCE m_HInstance;
	HWND m_HWnd;
	HDC m_HDeviceContext;
	HGLRC m_HRenderingContext;

	float m_Width;
	float m_Height;


};

void DefaultResize(unsigned int, unsigned int);
LRESULT DefaultEventHandling(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void SetResizeCallback(ResizeFunction function);
void SetEventCallback(EventFunction function);
void SetWindow(Window* window);

#endif