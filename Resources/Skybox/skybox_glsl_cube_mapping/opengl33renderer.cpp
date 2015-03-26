#include "opengl33renderer.h"

// ----------------------------------------------------------------------------------------------------------------------------

COpenGL33Renderer::COpenGL33Renderer()
{
	Camera = NULL;
}

COpenGL33Renderer::~COpenGL33Renderer()
{
}

void COpenGL33Renderer::MoveCamera(const vec3 &Movement)
{
	if(Camera != NULL)
	{
		Camera->Move(Movement);
	}
}

bool COpenGL33Renderer::OnCameraKeys(SHORT Keys, float FrameTime, vec3 &Movement)
{
	if(Camera != NULL)
	{
		return Camera->OnKeys(Keys, FrameTime, Movement);
	}

	return false;
}

void COpenGL33Renderer::OnKeyDown(UINT Key)
{
}

void COpenGL33Renderer::OnLButtonDown(int X, int Y)
{
	LastX = X;
	LastY = Y;
}

void COpenGL33Renderer::OnMouseMove(int X, int Y, bool LButtonDown, bool RButtonDown)
{
	if(RButtonDown)
	{
		if(Camera != NULL)
		{
			Camera->OnMouseMove(LastX - X, LastY - Y);
		}
	}

	LastX = X;
	LastY = Y;
}

void COpenGL33Renderer::OnMouseWheel(short zDelta)
{
	if(Camera != NULL)
	{
		Camera->OnMouseWheel(zDelta);
	}
}

void COpenGL33Renderer::OnRButtonDown(int X, int Y)
{
	LastX = X;
	LastY = Y;
}
