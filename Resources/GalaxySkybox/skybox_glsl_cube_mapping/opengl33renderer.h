#include "camera.h"

// ----------------------------------------------------------------------------------------------------------------------------

class COpenGL33Renderer
{
protected:
	int LastX, LastY;

protected:
	int Width, Height;

protected:
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix, ModelViewProjectionMatrix;

protected:
	CCamera *Camera;

public:
	CString Text;

public:
	COpenGL33Renderer();
	~COpenGL33Renderer();

	virtual bool Init() = 0;
	virtual void Resize(int Width, int Height) = 0;
	virtual void Render() = 0;
	virtual bool Animate(float FrameTime) = 0;
	virtual void Destroy() = 0;

	virtual void MoveCamera(const vec3 &Movement);

	virtual bool OnCameraKeys(SHORT Keys, float FrameTime, vec3 &Movement);
	virtual void OnKeyDown(UINT Key);
	virtual void OnLButtonDown(int X, int Y);
	virtual void OnMouseMove(int X, int Y, bool LButtonDown, bool RButtonDown);
	virtual void OnMouseWheel(short zDelta);
	virtual void OnRButtonDown(int X, int Y);
};
