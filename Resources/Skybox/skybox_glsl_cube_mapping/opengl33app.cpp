#include "myopengl33renderer.h"

// ----------------------------------------------------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{
	CMyOpenGL33Renderer *MyOpenGL33Renderer = new CMyOpenGL33Renderer();
	COpenGL33View *OpenGL33View = new COpenGL33View(MyOpenGL33Renderer);

	char *AppName = "Skybox, GLSL cube mapping";

	if(OpenGL33View->Init(hInstance, AppName, 800, 600, 4))
	{
		OpenGL33View->Show();
		OpenGL33View->MessageLoop();
	}
	else
	{
		MessageBox(NULL, ErrorLog, AppName, MB_OK | MB_ICONERROR);
	}

	OpenGL33View->Destroy();

	delete OpenGL33View;
	delete MyOpenGL33Renderer;

	return 0;
}
