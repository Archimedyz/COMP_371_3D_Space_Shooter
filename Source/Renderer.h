//--------------------------------------------------------------------------------------------------------------
// Contributors
// Assignment framework
// Awais Ali
//--------------------------------------------------------------------------------------------------------------



#pragma once

struct GLFWwindow;

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

#include <vector>
#include <GLM/glm.hpp>


enum ShaderType
{
	SHADER_PHONG,
	SHADER_BASIC,
	SHADER_SOLID_COLOR,
	NUM_SHADERS
};


class Renderer
{
public:
	static void Initialize();
	static void Shutdown();

	static void BeginFrame();
	static void EndFrame();

	static GLuint LoadShaders(std::string vertex_shader_path, std::string fragment_shader_path);
	static bool   LoadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals );

	static unsigned int GetShaderProgramID() { return sShaderProgramID[sCurrentShader]; }
	static unsigned int GetCurrentShader() { return sCurrentShader; }
	static void SetShader(ShaderType type);
	static void RenderTriangleSurfaceShadowVolume(glm::vec3 vertices[3], glm::vec3 surfacePos, glm::vec4 lightPos);
	static void draw_shadow();

private:
	static GLFWwindow* spWindow;

	static std::vector<unsigned int> sShaderProgramID;
	static unsigned int sCurrentShader;

};

