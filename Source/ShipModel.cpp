//--------------------------------------------------------------------------------------------------------------
// Contributors
// 
// 
//--------------------------------------------------------------------------------------------------------------

//Space ship model from: http://st.depositphotos.com/1757833/1959/i/950/depositphotos_19594413-Blue-spaceship-body-Seamless-texture.jpg

#include "ShipModel.h"
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "texture.hpp"
#include "objloader.hpp"
#include "vboindexer.hpp"

std::vector<glm::vec3> ShipModel::vArray;
unsigned int ShipModel::vertexbuffer;
unsigned int ShipModel::uvbuffer;
unsigned int ShipModel::normalbuffer;
unsigned int ShipModel::elementbuffer;
std::vector<unsigned short> ShipModel::indices;

// positions of the lasers relative to the ship positioned at (0,0,0) and scaled to (0.5,0.5,0.5)
const glm::vec3 ShipModel::upperLeftLaserPosition = vec3(2.3f, 0.65f, 1.6f);
const glm::vec3 ShipModel::upperRightLaserPosition = vec3(-2.3f, 0.65f, 1.6f);
const glm::vec3 ShipModel::lowerLeftLaserPosition = vec3(-2.3f, 0.65f, 1.6f);
const glm::vec3 ShipModel::lowerRightLaserPosition = vec3(-2.3f, -0.7f, 1.6f);

GLuint mShipTexture;

void ShipModel::LoadBuffers()
{
#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/newship.obj";
#else
	const char * modelPath = "../Resources/Models/newship.obj";
#endif
	Loader::loadModel(modelPath, ShipModel::vArray, ShipModel::vertexbuffer, ShipModel::uvbuffer, ShipModel::normalbuffer, ShipModel::elementbuffer, ShipModel::indices);

	mShipTexture = loadBMP_custom("../Resources/Textures/SpaceShipTexture.bmp");
}

ShipModel::ShipModel() :Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f))
{
	//initializing ship with lighting
	name = "SHIP";
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 100.0f;

	mCollisionRadius = 2;
	CollisionsOn = true;
}

ShipModel::ShipModel(glm::vec3 position, glm::vec3 scaling) : Model(position, scaling)
{
	LoadBuffers();
}

ShipModel::~ShipModel()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
}

void ShipModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	//mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	Model::Update(dt);
}

void ShipModel::Draw()
{
	Model::Draw();

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	glBindTexture(GL_TEXTURE_2D, mShipTexture);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// 4th attribute buffer : UVs
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		3,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
		);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void ShipModel::RenderShadowVolume(glm::vec4 lightPos){

}