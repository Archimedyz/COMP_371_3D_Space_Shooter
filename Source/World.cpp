//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "World.h"
#include "Renderer.h"
#include "ParsingHelper.h"
#include "StaticCamera.h"
#include "ThirdPersonCamera.h"
#include "FreeRoamCamera.h"
#include "AsteroidFactory.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "Particle.h"
#include "ThrusterParticles.h"
#include "Path.h"
#include "Projectile.h"
#include "ShipModel.h"
#include "Loader.h"
#include "Text2D.h"

#include <GLFW/glfw3.h>
#include "EventManager.h"
#include "NewAsteroid.h"

using namespace std;
using namespace glm;

World* World::instance;
int World::addCounter;

// Light Coefficients. We are using directional light.
const vec3 lightColor(1.0f, 1.0f, 1.0f);
const float lightKc = 0.0f;
const float lightKl = 1.0f;
const float lightKq = 2.0f;
const vec4 lightPosition(0.0f, 10.0f, 0.0f, 0.0f);

World::World()
{
    instance = this;
	addCounter = 0;

	initText2D("../Resources/Textures/Holstein.dds");

	NewAsteroid::LoadBuffers();
	Projectile::LoadBuffers();
	ShipModel::LoadBuffers();
}

World::~World()
{
	// Models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		delete *it;
	}

	mModel.clear();

    // Paths
    for (vector<Path*>::iterator it = mPath.begin(); it < mPath.end(); ++it)
	{
		delete *it;
	}
	mPath.clear();

	// Camera
	for (vector<Camera*>::iterator it = mCamera.begin(); it < mCamera.end(); ++it)
	{
		delete *it;
	}
	mCamera.clear();

	cleanupText2D();
}

World* World::GetInstance()
{
    return instance;
}

void World::Update(float dt)
{
	if (Game::GetInstance()->GameOver() == false)
	{
		// User Inputs
		// 1 2 3 4 to change the Camera
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1) == GLFW_PRESS)
		{
			mCurrentCamera = 0;
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2) == GLFW_PRESS)
		{
			if (mCamera.size() > 1)
			{
				mCurrentCamera = 1;
			}
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3) == GLFW_PRESS)
		{
			if (mCamera.size() > 2)
			{
				mCurrentCamera = 2;
			}
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_4) == GLFW_PRESS)
		{
			// Ship Camera
			if (mCamera.size() > 3)
			{
				mCurrentCamera = 3;
			}
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_5) == GLFW_PRESS)
		{
			// Free roam camera
			if (mCamera.size() > 4)
			{
				mCurrentCamera = 4;
			}
		}


		// 0 and 9 to change the shader
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_0) == GLFW_PRESS)
		{
			Renderer::SetShader(SHADER_SOLID_COLOR);
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9) == GLFW_PRESS)
		{
			Renderer::SetShader(SHADER_PHONG);
		}

		// Update current Camera
		mCamera[mCurrentCamera]->Update(dt);

		// Update models
		for (int i = 0; i < mModel.size(); ++i)
		{
			mModel[i]->Update(dt);

			mModel[i]->CheckCollisions(mModel); // Check if the model is colliding with any other, and set their destroyed flags to true if they are.

			if (glm::distance(mModel[i]->GetPosition(), vec3(0.0f, 0.0f, 0.0f)) >= 500) // if things are too far frm the center, delete them or move player back to center
			{
				if (mModel[i]->GetName() != "SHIP")
					mModel[i]->SetDestroy(true);
			}
			if (mModel[i]->IsDestroyed())
			{
				// HANDLE COLLISIONS SOMEHOW
				// Probably override a method from model which each type of object handles separately.
				// Large asteroids fragment, projectiles explode, ship explodes and takes damage, etc.
				mModel.erase(mModel.begin() + i); // Finally deletes model.
			}
		}

		if (++addCounter > 100){
			mModel.push_back(AsteroidFactory::createNewAsteroid(0));
			addCounter = 0;
		}
	}
}

void World::Draw()
{
	Renderer::BeginFrame();
	
	//Setting variable for light:
	GLuint WorldMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	GLuint ViewMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewTransform");
	GLuint ProjMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ProjectonTransform");

	// Get a handle for Light Attributes uniform
	GLuint LightPositionID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldLightPosition");
	GLuint LightColorID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightColor");
	GLuint LightAttenuationID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightAttenuation");


	// Get a handle for shadow mapping attributes.
	GLuint LightMVPID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightMVP");

	// Set shader to use
	glUseProgram(Renderer::GetShaderProgramID());

	// This looks for the MVP Uniform variable in the Vertex Program
	GLuint VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform"); 

	// Send the view projection constants to the shader
	mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	// get the transformation matrices
	glm::mat4 worldMatrix(1.0f);
	glm::mat4 viewMatrix = mCamera[mCurrentCamera]->GetViewMatrix();
	glm::mat4 projectionMatrix = mCamera[mCurrentCamera]->GetProjectionMatrix();

	// transformation matrices for the lightMVP
	glm::mat4 lightProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	glm::mat4 lightViewMatrix = glm::lookAt(vec3(-lightPosition), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 lightModelMatrix = glm::mat4(1.0);
	glm::mat4 lightMVP = lightProjectionMatrix * lightViewMatrix * lightModelMatrix;

	glm::mat4 correctionMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	glm::mat4 correctedLightMVP = correctionMatrix*lightMVP;


	// assign the transform matrices for the shader.
	glUniformMatrix4fv(WorldMatrixID, 1, GL_FALSE, &worldMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Shader constants for Light
	glUniform4f(LightPositionID, lightPosition.x, lightPosition.y, lightPosition.z, lightPosition.w);
	glUniform3f(LightColorID, lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(LightAttenuationID, lightKc, lightKl, lightKq);

	// Shader constants for shading pass through.
	glUniformMatrix4fv(LightMVPID, 1, GL_FALSE, &lightMVP[0][0]);

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		// Draw model
		(*it)->Draw();
	}

	// Draw Path Lines
	
	// Set Shader for path lines
	unsigned int prevShader = Renderer::GetCurrentShader();
	Renderer::SetShader(SHADER_PATH_LINES);
	glUseProgram(Renderer::GetShaderProgramID());

	// Send the view projection constants to the shader
	VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform");
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	for (vector<Path*>::iterator it = mPath.begin(); it < mPath.end(); ++it)
	{
		// Draw model
		(*it)->Draw();
	}

	int hp_offset = 3;
	char text[256];
	char health[256];
	char score[256];
	health[0] = 'h';
	health[1] = 'p';
	health[2] = ':';
	for (int i = hp_offset; i < 8 + hp_offset; ++i)
	{
		if (i < Game::GetInstance()->GetHealth() + hp_offset)
			health[i] = '*';
		else
			health[i] = ' ';
	}

	sprintf_s(text, "%.2f", glfwGetTime());
	printText2D(text, 10, 570, 24);
	printText2D(health, 610, 570, 24);

	sprintf_s(score, "%i", Game::GetInstance()->GetScore());
	printText2D(score, 305, 570, 24);


	if (Game::GetInstance()->GameOver())
		printText2D("You lose!", 305, 285, 40);

	// Restore previous shader
	Renderer::SetShader((ShaderType) prevShader);

	// now we go about adding our shadow volumes
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		(*it)->RenderShadowVolume(lightPosition);
	}

	Renderer::EndFrame();

}

void World::LoadScene(const char * scene_path)
{
	// All the commented out code that was used for the assignment to load paths and things is at the end of this file.
	// I moved it there since it's just extra clutter to keep it here commented out, it can probably
	// be deleted. -Nick
    
	mModel.push_back(AsteroidFactory::createNewAsteroid(0));

	Projectile::SetLastFired(time(NULL)); // Start the timer of last fired to when the game starts.

	Projectile::SetLastFired(time(NULL)); // Start the timer of last fired to when the game starts.

	//Loader::loadModel();

    LoadCameras();
}

void World::LoadCameras()
{
    // Setup Camera
    mCamera.push_back(new StaticCamera(vec3(3.0f, 5.0f, 5.0f),  vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
    mCamera.push_back(new StaticCamera(vec3(10.0f, 30.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
    mCamera.push_back(new StaticCamera(vec3(0.5f,  0.5f, 5.0f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));

	// cube "space station" model at center on world
	CubeModel * spaceStation_model = new CubeModel();
	spaceStation_model->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	mModel.push_back(spaceStation_model);

	// ship Character controlled with Third Person Camera
	ShipModel * ship_model = new ShipModel();
	player = ship_model;
	ship_model->SetPosition(vec3(0.0f, -5.0f, 0.0f));
	ship_model->ActivateCollisions(true);
	mCamera.push_back(new ThirdPersonCamera(ship_model));
	mModel.push_back(ship_model);

	// test particle on space ship model
	vec3 thrusterPosition = spaceStation_model->GetPosition() + vec3(0.0f, 1.0f, 0.0f);
	ThrusterParticles * test_thrusters = new ThrusterParticles(thrusterPosition, vec3(0.0f, 1.0f, 0.0f));		// orientation here may need to be changed to the opposite of the ship's look at
	test_thrusters->setParentModel(spaceStation_model);
	test_thrusters->SetName("TEST THRUSTERS");
	mModel.push_back(test_thrusters);

	/*CubeModel * floor = new CubeModel();
	floor->SetPosition(vec3(-2.0f, -5.0f, 1.0f));
	floor->SetScaling(vec3(10.0f, 0.5f, 10.0f));
	floor->ActivateCollisions(false);
	mModel.push_back(floor);*/

    mCurrentCamera = 0;


	mCamera.push_back(new FreeRoamCamera(vec3(2.0f, 2.0f, 2.0f), vec3(-1.0f, -1.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f)));
}

Path* World::FindPath(ci_string pathName)
{
    for(std::vector<Path*>::iterator it = mPath.begin(); it < mPath.end(); ++it)
    {
        if((*it)->GetCIName() == pathName)
        {
            return *it;
        }
    }
    return nullptr;
}

Model* World::FindModelByIndex(unsigned int index)
{
    return mModel.size() > 0 ? mModel[index % mModel.size()] : nullptr;
}

void World::AddModel(Model* mdl)
{
	mModel.push_back(mdl);
}
