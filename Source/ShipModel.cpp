//--------------------------------------------------------------------------------------------------------------
// Contributors
// 
// 
//--------------------------------------------------------------------------------------------------------------

#include "ShipModel.h"
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "shader.hpp"
#include "texture.hpp"
#include "objloader.hpp"
#include "vboindexer.hpp"

std::vector<glm::vec3> ShipModel::vArray;
unsigned int ShipModel::vertexbuffer;
unsigned int ShipModel::uvbuffer;
unsigned int ShipModel::normalbuffer;
unsigned int ShipModel::elementbuffer;
std::vector<unsigned short> ShipModel::indices;

void ShipModel::LoadBuffers()
{
#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/newship.obj";
#else
	const char * modelPath = "../Resources/Models/X_WING_2.obj";
#endif
	Loader::loadModel(modelPath, ShipModel::vArray, ShipModel::vertexbuffer, ShipModel::uvbuffer, ShipModel::normalbuffer, ShipModel::elementbuffer, ShipModel::indices);
}


ShipModel::ShipModel() :Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f))
{
	name = "SHIP";
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 100.0f;

	mCollisionRadius = 2;
	CollisionsOn = true;
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


}

void ShipModel::Draw()
{
	Model::Draw();

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

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

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
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
	glDisableVertexAttribArray(2);
}

void ShipModel::RenderShadowVolume(glm::vec4 lightPos){

}