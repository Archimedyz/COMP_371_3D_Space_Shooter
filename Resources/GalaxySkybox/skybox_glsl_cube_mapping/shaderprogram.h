#include "texture.h"

// ----------------------------------------------------------------------------------------------------------------------------

class CShaderProgram
{
private:
	GLuint VertexShader, FragmentShader, Program;

public:
	GLuint *UniformLocations, *AttribLocations;

public:
	CShaderProgram();
	~CShaderProgram();

	operator GLuint ();

	bool Load(char *VertexShaderFileName, char *FragmentShaderFileName);
	void Destroy();

private:
	GLuint LoadShader(char *FileName, GLenum Type);
	void SetDefaults();
};
