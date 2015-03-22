#include "camera.h"

// ----------------------------------------------------------------------------------------------------------------------------

CCamera::CCamera()
{
	Speed = 2.5f;
	Sensitivity = 0.25f;

	ViewMatrix = NULL;
	ViewMatrixInverse = NULL;

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 0.0f);
}

CCamera::~CCamera()
{
}

void CCamera::Look(const vec3 &Position, const vec3 &Reference)
{
	this->Position = Position;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}

void CCamera::Move(const vec3 &Movement)
{
	Position += Movement;

	CalculateViewMatrix();
}

void CCamera::OnMouseWheel(short zDelta)
{
}

void CCamera::SetViewMatrixPointer(float *ViewMatrix, float *ViewMatrixInverse)
{
	this->ViewMatrix = (mat4x4*)ViewMatrix;
	this->ViewMatrixInverse = (mat4x4*)ViewMatrixInverse;

	CalculateViewMatrix();
}

void CCamera::CalculateViewMatrix()
{
	if(ViewMatrix != NULL)
	{
		*ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);

		if(ViewMatrixInverse != NULL)
		{
			*ViewMatrixInverse = inverse(*ViewMatrix);
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------

CUniverseCamera::CUniverseCamera()
{
}

CUniverseCamera::~CUniverseCamera()
{
}

bool CUniverseCamera::OnKeys(SHORT Keys, float FrameTime, vec3 &Movement)
{
	float Speed = this->Speed;

	if(Keys & CAMERA_KEY_SHIFT) Speed *= 2.0f;
	if(Keys & CAMERA_KEY_CONTROL) Speed *= 0.5f;

	float Distance = Speed * FrameTime;

	vec3 Up = Y;
	vec3 Right = X;
	vec3 Forward = -Z;

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	if(Keys & CAMERA_KEY_W) Movement += Forward;
	if(Keys & CAMERA_KEY_S) Movement -= Forward;
	if(Keys & CAMERA_KEY_A) Movement -= Right;
	if(Keys & CAMERA_KEY_D) Movement += Right;
	if(Keys & CAMERA_KEY_R) Movement += Up;
	if(Keys & CAMERA_KEY_F) Movement -= Up;
	
	float AngleSpeed = 45.0f * FrameTime;

	if(Keys & CAMERA_KEY_Q)
	{
		X = rotate(X, AngleSpeed, Z);
		Y = rotate(Y, AngleSpeed, Z);
	}

	AngleSpeed = -AngleSpeed;

	if(Keys & CAMERA_KEY_E)
	{
		X = rotate(X, AngleSpeed, Z);
		Y = rotate(Y, AngleSpeed, Z);
	}

	return Keys & 0xFF ? true : false;
}

void CUniverseCamera::OnMouseMove(int dx, int dy)
{
	if(dx != 0)
	{
		float DeltaX = (float)dx * Sensitivity;

		X = rotate(X, DeltaX, Y);
		Z = rotate(Z, DeltaX, Y);
	}

	if(dy != 0)
	{
		float DeltaY = (float)dy * Sensitivity;

		Y = rotate(Y, DeltaY, X);
		Z = rotate(Z, DeltaY, X);

	}

	CalculateViewMatrix();
}

// ----------------------------------------------------------------------------------------------------------------------------

CFlyingCamera::CFlyingCamera()
{
}

CFlyingCamera::~CFlyingCamera()
{
}

bool CFlyingCamera::OnKeys(SHORT Keys, float FrameTime, vec3 &Movement)
{
	float Speed = this->Speed;

	if(Keys & CAMERA_KEY_SHIFT) Speed *= 2.0f;
	if(Keys & CAMERA_KEY_CONTROL) Speed *= 0.5f;

	float Distance = Speed * FrameTime;

	vec3 Up = Y;
	vec3 Right = X;
	vec3 Forward = -Z;

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	if(Keys & CAMERA_KEY_W) Movement += Forward;
	if(Keys & CAMERA_KEY_S) Movement -= Forward;
	if(Keys & CAMERA_KEY_A) Movement -= Right;
	if(Keys & CAMERA_KEY_D) Movement += Right;
	if(Keys & CAMERA_KEY_R) Movement += Up;
	if(Keys & CAMERA_KEY_F) Movement -= Up;

	return Keys & 0x3F ? true : false;
}

void CFlyingCamera::OnMouseMove(int dx, int dy)
{
	if(dx != 0)
	{
		float DeltaX = (float)dx * Sensitivity;

		X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
	}

	if(dy != 0)
	{
		float DeltaY = (float)dy * Sensitivity;

		Y = rotate(Y, DeltaY, X);
		Z = rotate(Z, DeltaY, X);

		if(Y.y < 0.0f)
		{
			Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
			Y = cross(Z, X);
		}
	}

	CalculateViewMatrix();
}

// ----------------------------------------------------------------------------------------------------------------------------

CFirstPersonCamera::CFirstPersonCamera()
{
}

CFirstPersonCamera::~CFirstPersonCamera()
{
}

bool CFirstPersonCamera::OnKeys(SHORT Keys, float FrameTime, vec3 &Movement)
{
	float Speed = this->Speed;

	if(Keys & CAMERA_KEY_SHIFT) Speed *= 2.0f;
	if(Keys & CAMERA_KEY_CONTROL) Speed *= 0.5f;

	float Distance = Speed * FrameTime;

	vec3 Up = vec3(0.0f, 1.0f, 0.0f);
	vec3 Right = X;
	vec3 Forward = cross(Up, Right);

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	if(Keys & CAMERA_KEY_W) Movement += Forward;
	if(Keys & CAMERA_KEY_S) Movement -= Forward;
	if(Keys & CAMERA_KEY_A) Movement -= Right;
	if(Keys & CAMERA_KEY_D) Movement += Right;
	if(Keys & CAMERA_KEY_R) Movement += Up;
	if(Keys & CAMERA_KEY_F) Movement -= Up;

	return Keys & 0x3F ? true : false;
}

void CFirstPersonCamera::OnMouseMove(int dx, int dy)
{
	if(dx != 0)
	{
		float DeltaX = (float)dx * Sensitivity;

		X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
	}

	if(dy != 0)
	{
		float DeltaY = (float)dy * Sensitivity;

		Y = rotate(Y, DeltaY, X);
		Z = rotate(Z, DeltaY, X);

		if(Y.y < 0.0f)
		{
			Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
			Y = cross(Z, X);
		}
	}

	CalculateViewMatrix();
}

// ----------------------------------------------------------------------------------------------------------------------------

CThirdPersonCamera::CThirdPersonCamera()
{
	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

CThirdPersonCamera::~CThirdPersonCamera()
{
}

void CThirdPersonCamera::Look(const vec3 &Position, const vec3 &Reference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}

void CThirdPersonCamera::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

bool CThirdPersonCamera::OnKeys(SHORT Keys, float FrameTime, vec3 &Movement)
{
	float Speed = this->Speed;

	if(Keys & CAMERA_KEY_SHIFT) Speed *= 2.0f;
	if(Keys & CAMERA_KEY_CONTROL) Speed *= 0.5f;

	float Distance = Speed * FrameTime;

	vec3 Up = vec3(0.0f, 1.0f, 0.0f);
	vec3 Right = X;
	vec3 Forward = cross(Up, Right);

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	if(Keys & CAMERA_KEY_W) Movement += Forward;
	if(Keys & CAMERA_KEY_S) Movement -= Forward;
	if(Keys & CAMERA_KEY_A) Movement -= Right;
	if(Keys & CAMERA_KEY_D) Movement += Right;
	if(Keys & CAMERA_KEY_R) Movement += Up;
	if(Keys & CAMERA_KEY_F) Movement -= Up;

	return Keys & 0x3F ? true : false;
}

void CThirdPersonCamera::OnMouseMove(int dx, int dy)
{
	Position -= Reference;

	if(dx != 0)
	{
		float DeltaX = (float)dx * Sensitivity;

		X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
	}

	if(dy != 0)
	{
		float DeltaY = (float)dy * Sensitivity;

		Y = rotate(Y, DeltaY, X);
		Z = rotate(Z, DeltaY, X);

		if(Y.y < 0.0f)
		{
			Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
			Y = cross(Z, X);
		}
	}

	Position = Reference + Z * length(Position);

	CalculateViewMatrix();
}

void CThirdPersonCamera::OnMouseWheel(short zDelta)
{
	Position -= Reference;

	if(zDelta < 0 && length(Position) < 500.0f)
	{
		Position += Position * 0.1f;
	}

	if(zDelta > 0 && length(Position) > 0.05f)
	{
		Position -= Position * 0.1f;
	}

	Position += Reference;

	CalculateViewMatrix();
}
