#include "ShipModel.h"
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "assimp_model.h"
#include "shaders.h"

//#include "Mesh.h"

CAssimpModel amModels;

ShipModel::ShipModel()
{
#if defined(PLATFORM_OSX)
    const char * modelPath = "Models/X_WING_2.obj";
#else
    const char * modelPath = "../Resources/Models/X_WING_2.obj";
#endif
    //Loader::loadModel(modelPath);
    //amModels[0].LoadModelFromFile("Models/X_WING_2.obj");
    
    amModels.LoadModelFromFile("Models/X_WING_2.obj");
    printf("Create Model.");
    CAssimpModel::FinalizeVBO();
}


ShipModel::~ShipModel()
{
}

void ShipModel::Update(float dt)
{
	Model::Update(dt);
}

void ShipModel::Draw()
{
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);
    
    GLuint iLoc = glGetUniformLocation(Renderer::GetShaderProgramID(), "gSampler");
    glUniform1i(iLoc, 0);
    
    glm::vec4 vVector(1,1,1,1);
    GLuint iLoc2 = glGetUniformLocation(Renderer::GetShaderProgramID(), "vColor");
    glUniform4fv(iLoc2, 1, (GLfloat*)&vVector);

    CAssimpModel::BindModelsVAO();
    amModels.RenderModel();
    printf("RENDER");
/*
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Loader::vertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, Loader::uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                         // array buffer offset
		);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, Loader::normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                        // array buffer offset
		);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Loader::elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		Loader::indices.size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
		);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);*/
}


