#include "shaderprogram.h"

// ----------------------------------------------------------------------------------------------------------------------------

#define CAMERA_KEY_W 0x0001
#define CAMERA_KEY_S 0x0002
#define CAMERA_KEY_A 0x0004
#define CAMERA_KEY_D 0x0008
#define CAMERA_KEY_R 0x0010
#define CAMERA_KEY_F 0x0020
#define CAMERA_KEY_Q 0x0040
#define CAMERA_KEY_E 0x0080
#define CAMERA_KEY_C 0x0100
#define CAMERA_KEY_SPACE 0x0200
#define CAMERA_KEY_SHIFT 0x0400
#define CAMERA_KEY_CONTROL 0x0800

// ----------------------------------------------------------------------------------------------------------------------------

class CCamera
{
protected:
	float Speed, Sensitivity;

protected:
	mat4x4 *ViewMatrix, *ViewMatrixInverse;

public:
	vec3 X, Y, Z, Position;

public:
	CCamera();
	~CCamera();

	virtual void Look(const vec3 &Position, const vec3 &Reference);
	virtual void Move(const vec3 &Movement);
	virtual bool OnKeys(SHORT Keys, float FrameTime, vec3 &Movement) = 0;
	virtual void OnMouseMove(int dx, int dy) = 0;
	virtual void OnMouseWheel(short zDelta);
	virtual void SetViewMatrixPointer(float *ViewMatrix, float *ViewMatrixInverse = NULL);

protected:
	virtual void CalculateViewMatrix();
};

// ----------------------------------------------------------------------------------------------------------------------------

class CUniverseCamera : public CCamera
{
public:
	CUniverseCamera();
	~CUniverseCamera();

	bool OnKeys(SHORT Keys, float FrameTime, vec3 &Movement);
	void OnMouseMove(int dx, int dy);
};

// ----------------------------------------------------------------------------------------------------------------------------

class CFlyingCamera : public CCamera
{
public:
	CFlyingCamera();
	~CFlyingCamera();

	bool OnKeys(SHORT Keys, float FrameTime, vec3 &Movement);
	void OnMouseMove(int dx, int dy);
};

// ----------------------------------------------------------------------------------------------------------------------------

class CFirstPersonCamera : public CCamera
{
public:
	CFirstPersonCamera();
	~CFirstPersonCamera();

	bool OnKeys(SHORT Keys, float FrameTime, vec3 &Movement);
	void OnMouseMove(int dx, int dy);
};

// ----------------------------------------------------------------------------------------------------------------------------

class CThirdPersonCamera : public CCamera
{
public:
	vec3 Reference;

public:
	CThirdPersonCamera();
	~CThirdPersonCamera();

	void Look(const vec3 &Position, const vec3 &Reference);
	void Move(const vec3 &Movement);
	bool OnKeys(SHORT Keys, float FrameTime, vec3 &Movement);
	void OnMouseMove(int dx, int dy);
	void OnMouseWheel(short zDelta);
};
