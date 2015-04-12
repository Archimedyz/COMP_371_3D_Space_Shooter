#include "AsteroidModel.h"
#include "World.h"
#include "AsteroidFactory.h"
#include "Variables.h"
#include "Renderer.h"
#include "Loader.h"
#include <iostream>
#include <string>
#include "texture.hpp"
#include "shader.hpp"

// Include GLEW - OpenGL Extension Wrangler
using namespace glm;

AsteroidModel::AsteroidModel() : Model()
{

#if defined(PLATFORM_OSX)
	std::string modelPath = "Models/asteroid";
#else
	std::string modelPath = "../Resources/Models/asteroid";
#endif


	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders("../Shaders/TransformVertexShader.vertexshader", "../Shaders/TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	/*GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");*/

	// Load the texture
	GLuint Texture = loadBMP_custom("../Resources/Textures/AM1.BMP");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(Renderer::GetShaderProgramID(), "myTextureSampler");


	int random = 1;
	modelPath = modelPath + std::to_string(random) + ".obj";
	Loader::loadModelAsteroid(modelPath.c_str());

	//std::cout << "created" << std::endl;
	destroyed = false;
	// Create Vertex Buffer for all the verices of the Cube
	/*vec3 halfSize = vec3(1.0f, 1.0f, 1.0f) * 0.5f;

	Vertex vertexBuffer[] = {  // position,                normal,                  color
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) }, //left - red
		{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },

		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },

		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) }, // far - blue
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },

		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },
		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f) },

		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) }, // bottom - turquoise
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },

		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
		{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
		{ vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },

		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) }, // near - green
		{ vec3(-halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) }, // right - purple
		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },

		{ vec3(halfSize.x, -halfSize.y, -halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
		{ vec3(halfSize.x, -halfSize.y, halfSize.z), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) }, // top - yellow
		{ vec3(halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },

		{ vec3(halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
		{ vec3(-halfSize.x, halfSize.y, -halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
		{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) }
	};

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(2, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);*/
}

AsteroidModel::~AsteroidModel()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void AsteroidModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	//mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	//Update posiion and rotation per frame.
	mPosition += normalize(mDirection)*mSpeed*dt;
	mYRotationAngleInDegrees += mRotationSpeed*dt;
	if (glm::length(mDirection) <= 0.01){
		Destroy();
	}


	//Model::Update(dt);
}

void AsteroidModel::Draw()
{
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Loader::vertexbufferAst);
	glVertexAttribPointer(
		0, // attribute
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
		);
	
	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Loader::normalbufferAst);
	glVertexAttribPointer(
		1, // attribute
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
		);

	// 3rd. UV buffer data.
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, Loader::uvbufferAst);
	glVertexAttribPointer(
		2, // attribute
		2, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
		);
	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Loader::elementbufferAst);
	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES, // mode
		Loader::indicesAst.size(), // count
		GL_UNSIGNED_SHORT, // type
		(void*)0 // element array buffer offset
		);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

bool AsteroidModel::ParseLine(const std::vector<ci_string> &token)
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

void AsteroidModel::SetDirection(vec3 direction){
	mDirection = direction;
}

void AsteroidModel::RandomizedDirection()
{
	float scale_x = 0.5f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (2.5f - 0.5f));
	float scale_y = 0.5f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (2.5f - 0.5f));
	float scale_z = 0.5f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (2.5f - 0.5f));

	glm::vec3 direction = glm::vec3(scale_x, scale_y, scale_z);
	mDirection = direction;
}

void AsteroidModel::Destroy(){
	destroyed = true;

	AsteroidModel* smallAsteroid = AsteroidFactory::createAsteroid(1);
	AsteroidModel* smallAsteroid2 = AsteroidFactory::createAsteroid(1);

	glm::vec3 scale = glm::vec3(mScaling.x * 3, mScaling.y * 3, mScaling.z * 3);
	smallAsteroid->SetScaling(scale);
	smallAsteroid2->SetScaling(scale);


	smallAsteroid->SetPosition(mPosition);
	smallAsteroid2->SetPosition(mPosition);

	smallAsteroid->RandomizedDirection();
	smallAsteroid2->RandomizedDirection();


	smallAsteroid->ActivateCollisions(false);
	World::GetInstance()->AddModel(smallAsteroid);

	smallAsteroid2->ActivateCollisions(false);
	World::GetInstance()->AddModel(smallAsteroid2);

	std::cout<<"Hello";
	

	// perform any remining destruction actions here.
}

bool AsteroidModel::isDestroyed(){
	return destroyed;
}
void AsteroidModel::SetRotationSpeed(float rotationSpeed){
	mRotationSpeed = rotationSpeed;
}
float AsteroidModel::GetRotationSpeed(){
	return mRotationSpeed;
}