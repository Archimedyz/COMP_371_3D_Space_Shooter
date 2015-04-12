//Skybox texture from here: https://hondadarrell.wordpress.com/2010/01/20/creating-3d-space-skyboxes/

#include "SkyboxModel.h"

//holders for buffers
std::vector<glm::vec3> SkyboxModel::vArray;
unsigned int SkyboxModel::vertexbuffer;
unsigned int SkyboxModel::uvbuffer;
unsigned int SkyboxModel::normalbuffer;
unsigned int SkyboxModel::elementbuffer;
std::vector<unsigned short> SkyboxModel::indices;

//initiate GLuint to hold skybox texture
GLuint singleSkyboxBMP;


void SkyboxModel::LoadBuffers()
{
#if defined(PLATFORM_OSX)
	const char * modelPath = "Resources/Models/Final_Skybox_V2.obj";
#else
	const char * modelPath = "../Resources/Models/Final_Skybox_V2.obj";
#endif
	Loader::loadModel(modelPath, SkyboxModel::vArray, SkyboxModel::vertexbuffer, SkyboxModel::uvbuffer, SkyboxModel::normalbuffer, SkyboxModel::elementbuffer, SkyboxModel::indices);
	
	// load texture for skybox
	singleSkyboxBMP = loadBMP_custom("../Resources/Textures/SkyboxTexture.bmp");
}

SkyboxModel::SkyboxModel() :Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f))
{
	//initializing skybox with lighting
	name = "SKYBOX";
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 15.0f;

	//skybox scaled to 50 units
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	mScaling = glm::vec3(125.0f, 125.0f, 125.0f);

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

	//world matrix info
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	glBindTexture(GL_TEXTURE_2D, singleSkyboxBMP);

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
	glDisableVertexAttribArray(2);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void SkyboxModel::RenderShadowVolume(glm::vec4 lightPos){

}
