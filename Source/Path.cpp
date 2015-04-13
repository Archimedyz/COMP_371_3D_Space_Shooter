//--------------------------------------------------------------------------------------------------------------
// Contributors
// Skyler Wittman (removed stuff we didn't need) 
// 
//--------------------------------------------------------------------------------------------------------------

#include "Path.h"
#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

Path::Path(vec3 size) : Model()
{
}

Path::~Path()
{
}

void Path::CreateVertexBuffer()
{
	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*mWaypoints.size(), &mWaypoints[0], GL_STATIC_DRAW);
}

void Path::Update(float dt)
{
}

void Path::Draw()
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

	// Draw the triangles !
	glDrawArrays(GL_LINE_LOOP, 0, mWaypoints.size());

	glDisableVertexAttribArray(0);
}

void Path::AddWaypoint(glm::vec3 point)
{
	mWaypoints.push_back(point);
}

void Path::ClearWaypoints()
{
	mWaypoints.clear();
}

vec3 Path::GetWaypoint(unsigned int index)
{
	// Need to consider the position/rotation/scaling of the path in the world
	// + the relative position of the waypoint
	return  vec3(GetWorldMatrix() *  vec4(mWaypoints[index % mWaypoints.size()], 1.0f));
}
