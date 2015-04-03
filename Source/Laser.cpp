
#include "Laser.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>

Laser::Laser()
{
}

Laser::Laser(glm::vec3 h, glm::vec3 t)
{
	points.push_back( h);
	points.push_back(t);
	speed = 1;
	std::cout << "created" << std::endl;
	CollisionsOn = false;
}


Laser::~Laser()
{
}

void Laser::CreateVertexBuffer()
{
	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*2, &points[0], GL_STATIC_DRAW);
}

void Laser::Update(float dt)
{
	std::cout << "updated" << std::endl;
	glm::vec3 dir = glm::normalize(points[0] - points[1]) * dt * speed;
	points[0] += dir;
	points[1] += dir;
}

void Laser::Draw()
{
	std::cout << "drawn" << std::endl;
	unsigned int prevShader = Renderer::GetCurrentShader();
	Renderer::SetShader(SHADER_PATH_LINES);
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(0,
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(glm::vec3), // stride
		(void*)0        // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);
	Renderer::SetShader((ShaderType)prevShader);

}