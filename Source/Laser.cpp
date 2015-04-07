/*
Contributors:

Nicholas Dudek





*/


#include "Laser.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>

Laser::Laser()
{
}

Laser::Laser(glm::vec3 t, glm::vec3 h)
{
	points.push_back(h);
	points.push_back(t);
	points.push_back(h + glm::vec3(.1, 0, 0));
	mPosition = t;
	speed = 10;
	CreateVertexBuffer();
	name = "LASER";
	mCollisionRadius = 1;
	//CollisionsOn = false;
}


Laser::~Laser()
{
	std::cout << "deleting laser\n";
}

void Laser::CreateVertexBuffer()
{
	Vertex vb[] = { { points[0], glm::vec3(1.0f, 0.0f, 0.0f) }, { points[1], glm::vec3(1.0f, 0.0f, 0.0f) }, { points[2], glm::vec3(1.0f, 0.0f, 0.0f) } };

	for (int i = 0; i < sizeof(vb) / sizeof(vb[0]); ++i)
	{
		vArray.push_back(vb[i].pos);
	}

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*points.size(), vb, GL_STATIC_DRAW);
}

void Laser::Update(float dt)
{
	glm::vec3 dir = glm::normalize(points[0] - points[1]) * dt * speed;
	mPosition = mPosition + dir;

	if (glm::distance(glm::vec3(0, 0, 0), mPosition) > 500)
		mDestroyed = true;
}

void Laser::Draw()
{
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
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
		);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(2,
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(Vertex), // stride
		(void*)(2 * sizeof(glm::vec3))        // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);

}