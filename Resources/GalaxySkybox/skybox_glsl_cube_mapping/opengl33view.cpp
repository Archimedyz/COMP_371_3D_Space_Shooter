#include "opengl33view.h"

// ----------------------------------------------------------------------------------------------------------------------------

COpenGL33View *OpenGL33View = NULL;

// ----------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			if(OpenGL33View != NULL) OpenGL33View->OnKeyDown((UINT)wParam);
			break;

		case WM_LBUTTONDOWN:
			if(OpenGL33View != NULL) OpenGL33View->OnLButtonDown(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_MOUSEMOVE:
			if(OpenGL33View != NULL) OpenGL33View->OnMouseMove(LOWORD(lParam), HIWORD(lParam));
			break;

		case 0x020A: // WM_MOUSEWHEEL
			if(OpenGL33View != NULL) OpenGL33View->OnMouseWheel(HIWORD(wParam));
			break;

		case WM_PAINT:
			if(OpenGL33View != NULL) OpenGL33View->OnPaint();
			break;

		case WM_RBUTTONDOWN:
			if(OpenGL33View != NULL) OpenGL33View->OnRButtonDown(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_SIZE:
			if(OpenGL33View != NULL) OpenGL33View->OnSize(LOWORD(lParam), HIWORD(lParam));
			break;

		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}

// ----------------------------------------------------------------------------------------------------------------------------

CString ModuleDirectory, ErrorLog;

// ----------------------------------------------------------------------------------------------------------------------------

void GetModuleDirectory()
{
	char *moduledirectory = new char[256];
	GetModuleFileName(GetModuleHandle(NULL), moduledirectory, 256);
	*(strrchr(moduledirectory, '\\') + 1) = 0;
	ModuleDirectory = moduledirectory;
	delete [] moduledirectory;
}

// ----------------------------------------------------------------------------------------------------------------------------

COpenGL33View::COpenGL33View(COpenGL33Renderer *OpenGL33Renderer)
{
	OpenGL33View = this;
	this->OpenGL33Renderer = OpenGL33Renderer;
}

COpenGL33View::~COpenGL33View()
{
}

bool COpenGL33View::Init(HINSTANCE hInstance, char *Title, int Width, int Height, int Samples)
{
	this->Title = Title;
	this->Width = Width;
	this->Height = Height;

	WNDCLASSEX WndClassEx;

	memset(&WndClassEx, 0, sizeof(WNDCLASSEX));

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.lpszClassName = "OpenGL33TutorialsWin32Framework";

	if(RegisterClassEx(&WndClassEx) == 0)
	{
		ErrorLog.Set("RegisterClassEx failed!");
		return false;
	}

	DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, WndClassEx.lpszClassName, Title, Style, 0, 0, Width, Height, NULL, NULL, hInstance, NULL);

	if(hWnd == NULL)
	{
		ErrorLog.Set("CreateWindowEx failed!");
		return false;
	}

	HDC hDC = GetDC(hWnd);

	if(hDC == NULL)
	{
		ErrorLog.Set("GetDC failed!");
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;
 
	int PixelFormat = ChoosePixelFormat(hDC, &pfd);

	if(PixelFormat == 0)
	{
		ErrorLog.Set("ChoosePixelFormat failed!");
		return false;
	}

	static int MSAAPixelFormat = 0;

	if(SetPixelFormat(hDC, MSAAPixelFormat == 0 ? PixelFormat : MSAAPixelFormat, &pfd) == FALSE)
	{
		ErrorLog.Set("SetPixelFormat failed!");
		return false;
	}

	hGLRC = wglCreateContext(hDC);

	if(hGLRC == NULL)
	{
		ErrorLog.Set("wglCreateContext failed!");
		return false;
	}

	if(wglMakeCurrent(hDC, hGLRC) == FALSE)
	{
		ErrorLog.Set("wglMakeCurrent (1) failed!");
		return false;
	}

	if(glewInit() != GLEW_OK)
	{
		ErrorLog.Set("glewInit failed!");
		return false;
	}

	if(MSAAPixelFormat == 0 && Samples > 0)
	{
		if(WGLEW_ARB_pixel_format && GLEW_ARB_multisample)
		{
			while(Samples > 0)
			{
				UINT NumFormats = 0;

				int PFAttribs[] =
				{
					WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
					WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
					WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
					WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
					WGL_COLOR_BITS_ARB, 32,
					WGL_DEPTH_BITS_ARB, 24,
					WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
					WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
					WGL_SAMPLES_ARB, Samples,
					0
				};

				if(wglChoosePixelFormatARB(hDC, PFAttribs, NULL, 1, &MSAAPixelFormat, &NumFormats) == TRUE && NumFormats > 0) break;

				Samples--;
			}

			wglDeleteContext(hGLRC);
			DestroyWindow(hWnd);
			UnregisterClass(WndClassEx.lpszClassName, hInstance);

			return Init(hInstance, Title, Width, Height, Samples);
		}
		else
		{
			Samples = 0;
		}
	}

	this->Samples = Samples;

	if(WGLEW_ARB_create_context)
	{
		wglDeleteContext(hGLRC);

		int GL33RCAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0
		};

		hGLRC = wglCreateContextAttribsARB(hDC, 0, GL33RCAttribs);

		if(hGLRC == NULL)
		{
			ErrorLog.Set("wglCreateContextAttribsARB failed!");
			return false;
		}

		if(wglMakeCurrent(hDC, hGLRC) == FALSE)
		{
			ErrorLog.Set("wglMakeCurrent (2) failed!");
			return false;
		}
	}
	else
	{
		ErrorLog.Set("WGL_ARB_create_context not supported!");
		return false;
	}

	GetModuleDirectory();

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &gl_max_texture_size);

	if(GLEW_EXT_texture_filter_anisotropic)
	{
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &gl_max_texture_max_anisotropy_ext);
	}

	if(WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0);
	}

	if(OpenGL33Renderer != NULL)
	{
		return OpenGL33Renderer->Init();
	}

	return true;
}

void COpenGL33View::Show(bool Maximized)
{
	RECT dRect, wRect, cRect;

	GetWindowRect(GetDesktopWindow(), &dRect);
	GetWindowRect(hWnd, &wRect);
	GetClientRect(hWnd, &cRect);

	wRect.right += Width - cRect.right;
	wRect.bottom += Height - cRect.bottom;
	wRect.right -= wRect.left;
	wRect.bottom -= wRect.top;
	wRect.left = dRect.right / 2 - wRect.right / 2;
	wRect.top = dRect.bottom / 2 - wRect.bottom / 2;

	MoveWindow(hWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);

	ShowWindow(hWnd, Maximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
}

void COpenGL33View::MessageLoop()
{
	MSG Msg;

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void COpenGL33View::Destroy()
{
	if(OpenGL33Renderer != NULL && GLEW_VERSION_3_3)
	{
		OpenGL33Renderer->Destroy();
	}

	wglDeleteContext(hGLRC);
	DestroyWindow(hWnd);
}

void COpenGL33View::OnKeyDown(UINT Key)
{
	switch(Key)
	{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
	}

	if(OpenGL33Renderer != NULL)
	{
		OpenGL33Renderer->OnKeyDown(Key);
	}
}

void COpenGL33View::OnLButtonDown(int X, int Y)
{
	if(OpenGL33Renderer != NULL)
	{
		OpenGL33Renderer->OnLButtonDown(X, Y);
	}
}

void COpenGL33View::OnMouseMove(int X, int Y)
{
	if(OpenGL33Renderer != NULL)
	{
		OpenGL33Renderer->OnMouseMove(X, Y, GetKeyState(VK_LBUTTON) & 0x80 ? true : false, GetKeyState(VK_RBUTTON) & 0x80 ? true : false);
	}
}

void COpenGL33View::OnMouseWheel(short zDelta)
{
	if(OpenGL33Renderer != NULL)
	{
		OpenGL33Renderer->OnMouseWheel(zDelta);
	}
}

void COpenGL33View::OnPaint()
{
	static DWORD LastFrameTime = GetTickCount(), LastFPSTime = LastFrameTime, FPS = 0;

	PAINTSTRUCT ps;

	HDC hDC = BeginPaint(hWnd, &ps);

	DWORD Time = GetTickCount();

	float FrameTime = float(Time - LastFrameTime) * 0.001f;
	LastFrameTime = Time;

	if(Time - LastFPSTime > 1000)
	{
		CString Text = Title;

		if(OpenGL33Renderer != NULL)
		{
			if(OpenGL33Renderer->Text[0] != 0)
			{
				Text.Append(" - " + OpenGL33Renderer->Text);
			}
		}

		Text.Append(" - %dx%d", Width, Height);
		Text.Append(", ATF %dx", gl_max_texture_max_anisotropy_ext);
		Text.Append(", MSAA %dx", Samples);
		Text.Append(", FPS: %d", FPS);
		Text.Append(" - %s", glGetString(GL_RENDERER));

		SetWindowText(hWnd, Text);
	
		LastFPSTime = Time;
		FPS = 0;
	}
	else
	{
		FPS++;
	}

	if(OpenGL33Renderer != NULL)
	{
		bool Animated = OpenGL33Renderer->Animate(FrameTime);

		SHORT Keys = 0x0000;

		if(GetKeyState('W') & 0x80) Keys |= CAMERA_KEY_W;
		if(GetKeyState('S') & 0x80) Keys |= CAMERA_KEY_S;
		if(GetKeyState('A') & 0x80) Keys |= CAMERA_KEY_A;
		if(GetKeyState('D') & 0x80) Keys |= CAMERA_KEY_D;
		if(GetKeyState('R') & 0x80) Keys |= CAMERA_KEY_R;
		if(GetKeyState('F') & 0x80) Keys |= CAMERA_KEY_F;
		if(GetKeyState('Q') & 0x80) Keys |= CAMERA_KEY_Q;
		if(GetKeyState('E') & 0x80) Keys |= CAMERA_KEY_E;
		if(GetKeyState('C') & 0x80) Keys |= CAMERA_KEY_C;
		if(GetKeyState(VK_SPACE) & 0x80) Keys |= CAMERA_KEY_SPACE;
		if(GetKeyState(VK_SHIFT) & 0x80) Keys |= CAMERA_KEY_SHIFT;
		if(GetKeyState(VK_CONTROL) & 0x80) Keys |= CAMERA_KEY_CONTROL;

		vec3 Movement;

		if(OpenGL33Renderer->OnCameraKeys(Keys, FrameTime, Movement))
		{
			OpenGL33Renderer->MoveCamera(Movement);
		}

		OpenGL33Renderer->Render();
	}

	SwapBuffers(hDC);

	EndPaint(hWnd, &ps);

	InvalidateRect(hWnd, NULL, FALSE);
}

void COpenGL33View::OnRButtonDown(int X, int Y)
{
	if(OpenGL33Renderer != NULL)
	{
		OpenGL33Renderer->OnRButtonDown(X, Y);
	}
}

void COpenGL33View::OnSize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	if(OpenGL33Renderer != NULL)
	{
		OpenGL33Renderer->Resize(Width, Height);
	}
}
