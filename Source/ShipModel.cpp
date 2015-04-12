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