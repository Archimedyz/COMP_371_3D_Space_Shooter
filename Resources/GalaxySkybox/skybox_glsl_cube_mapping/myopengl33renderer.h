#include "opengl33view.h"

// ----------------------------------------------------------------------------------------------------------------------------

class CMyOpenGL33Renderer : public COpenGL33Renderer
{
private:
	mat4x4 ViewProjectionMatrix;
	CTexture Textures[4];
	CShaderProgram SkyBox, Lighting;
	GLuint VBO[2], VAO[2];

private:
	bool Pause;
	int VerticesCount[3];

public:
	CMyOpenGL33Renderer();
	~CMyOpenGL33Renderer();

	bool Init();
	void Resize(int Width, int Height);
	void Render();
	bool Animate(float FrameTime);
	void Destroy();

	void OnKeyDown(UINT Key);
};

// ----------------------------------------------------------------------------------------------------------------------------

extern vec3 SkyBoxVertices[36];
extern vec2 GrassTexCoords[6];
extern vec3 GrassVertices[6];
extern vec2 CubeTexCoords[6];
extern vec3 CubeNormals[6];
extern vec3 CubeVertices[36];

// ----------------------------------------------------------------------------------------------------------------------------

int GenerateTorus(CBuffer &Buffer, float Radius, float TubeRadius, int SubDivAround, int SubDivTube, const mat4x4 &ModelMatrix);
