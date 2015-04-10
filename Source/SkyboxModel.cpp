#include "SkyboxModel.h"
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Renderer.h"
#include "Texture.hpp"
#include "Objloader.hpp"
#include "VBOindexer.hpp"

std::vector<glm::vec3> SkyboxModel::vArray;
unsigned int SkyboxModel::vertexbuffer;
unsigned int SkyboxModel::uvbuffer;
unsigned int SkyboxModel::normalbuffer;
unsigned int SkyboxModel::elementbuffer;
std::vector<unsigned short> SkyboxModel::indices;


void SkyboxModel::LoadBuffers()
{
#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/skyboxRegularNormals.obj";
#else
	const char * modelPath = "../Resources/Models/skyboxRegularNormals.obj";
#endif
	Loader::loadModel(modelPath, SkyboxModel::vArray, SkyboxModel::vertexbuffer, SkyboxModel::uvbuffer, SkyboxModel::normalbuffer, SkyboxModel::elementbuffer, SkyboxModel::indices);
}

SkyboxModel::SkyboxModel() :Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f))
{
	name = "SKYBOX";
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 100.0f;

	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mScaling = glm::vec3(10.0f, 10.0f, 10.0f);

	CollisionsOn = false;
}

SkyboxModel::~SkyboxModel()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
}

void SkyboxModel::Update(float dt)
{

}

void SkyboxModel::Draw()
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

bool SkyboxModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}


void SkyboxModel::RenderShadowVolume(glm::vec4 lightPos){

}
