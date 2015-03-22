#include "opengl33renderer.h"

// ----------------------------------------------------------------------------------------------------------------------------

class COpenGL33View
{
private:
	char *Title;
	int Width, Height, Samples;
	HWND hWnd;
	HGLRC hGLRC;

private:
	COpenGL33Renderer *OpenGL33Renderer;

public:
	COpenGL33View(COpenGL33Renderer *OpenGL33Renderer);
	~COpenGL33View();

	bool Init(HINSTANCE hInstance, char *Title, int Width, int Height, int Samples);
	void Show(bool Maximized = false);
	void MessageLoop();
	void Destroy();
	
	void OnKeyDown(UINT Key);
	void OnLButtonDown(int X, int Y);
	void OnMouseMove(int X, int Y);
	void OnMouseWheel(short zDelta);
	void OnPaint();
	void OnRButtonDown(int X, int Y);
	void OnSize(int Width, int Height);
};
