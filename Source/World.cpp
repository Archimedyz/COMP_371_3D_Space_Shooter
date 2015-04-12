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

// boolean to display shadow volumes. Can be toggled on or off during runtime.
bool show_shadow_volumes = false;
// main shader type. This allows for changing type during runtime.
ShaderType main_shader = SHADER_PHONG;
// frame buffer to be used when capturing depth information from the light's perspective.
GLuint FrameBufferID = 0;

World::World()
{
    instance = this;
	addCounter = 0;

	initText2D("../Resources/Textures/Holstein.dds");

	NewAsteroid::LoadBuffers();
	Projectile::LoadBuffers();
	ShipModel::LoadBuffers();
	
	// generate the buffer, it's Id in the above variable.
	glGenFramebuffers(1, &FrameBufferID);
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
			main_shader = SHADER_SOLID_COLOR;
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9) == GLFW_PRESS)
		{
			main_shader = SHADER_PHONG;
		}
		else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_8) == GLFW_PRESS){
			show_shadow_volumes = !show_shadow_volumes;
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
				else
					mModel[i]->SetPosition(vec3(0.0f, 0.0f, 0.0f));
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

	//Bind the frame buffer so we render into it instead of the screen.
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);

	// Create a texture to which we will render the depth information.
	GLuint DepthTextureID;
	glGenTextures(1, &DepthTextureID);

	// now we bind this texture so that all drawing modifies this texture.
	glBindTexture(GL_TEXTURE_2D, DepthTextureID);

	// create a blank image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	// Some form of filtering. Not too sure honestly what it does, but according to the tutorial, it's needed.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureID, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "FRAME BUFFER NOT OKAY!" << std::endl;
		return;
	}

	// getting variable handles for transforms:
	GLuint WorldMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	GLuint ViewMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewTransform");
	GLuint ProjMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ProjectonTransform");

	// Get a handle for Light Attributes uniform
	GLuint LightPositionID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldLightPosition");
	GLuint LightColorID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightColor");
	GLuint LightAttenuationID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightAttenuation");

	// This looks for the MVP Uniform variable in the Vertex Program
	GLuint VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform"); 

	// Send the view projection constants to the shader
	mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();

	// get the transformation matrices
	glm::mat4 worldMatrix(1.0f);
	glm::mat4 viewMatrix = mCamera[mCurrentCamera]->GetViewMatrix();
	glm::mat4 projectionMatrix = mCamera[mCurrentCamera]->GetProjectionMatrix();

	/*
		This variable is needed for the calculation the the depthMVP (shown after.)
		In the tutorial, the light's direction is randomly chosen, and as a result, 
		the up vector chosen for the light's up vector is (0, 1, 0). However, when
		using Light that is not angled and parallel to (0, 1, 0), the lookAt 
		function will fail. 

		The below variable will adjust itself if the light vetor is parallel to (0, 1, 0)
	*/
	glm::vec3 relativeUp = vec3(0.0f, 1.0f, 0.0f);
	if (isParallel(vec3(lightPosition), relativeUp)){
		// if the light's direction is parallel to (0, 1, 0), then set the Up to (1, 0, 0) instead.
		relativeUp = vec3(1.0f, 0.0f, 0.0f);
	}

	// variables and transformations necessary for the shadow mapping
	// for the specific method I'm using, the light needs to be directional.
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	glm::mat4 depthViewMatrix = glm::lookAt(vec3(-lightPosition), glm::vec3(0, 0, 0), relativeUp);
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Use the main shader
	Renderer::SetShader(main_shader);
	glUseProgram(Renderer::GetShaderProgramID());

	// set ViewProjection transform for shaders
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	// assign the transform matrices for the shader.
	glUniformMatrix4fv(WorldMatrixID, 1, GL_FALSE, &worldMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Shader constants for Light
	glUniform4f(LightPositionID, lightPosition.x, lightPosition.y, lightPosition.z, lightPosition.w);
	glUniform3f(LightColorID, lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(LightAttenuationID, lightKc, lightKl, lightKq);
	
	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
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

	//// now we go about adding our shadow volumes
	//for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	//{
	//	(*it)->RenderShadowVolume(lightPosition);
	//}

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

	// Cube "ship" Character controlled with Third Person Camera
	//CubeModel * ship_model = new CubeModel();
	ShipModel * ship_model = new ShipModel();
	player = ship_model;
	ship_model->SetPosition(vec3(0.0f, -5.0f, 0.0f));
	ship_model->ActivateCollisions(true);
	mCamera.push_back(new ThirdPersonCamera(ship_model));
	mModel.push_back(ship_model);

	CubeModel * floor = new CubeModel();
	floor->SetPosition(vec3(0.0f, -5.0f, 0.0f));
	floor->SetScaling(vec3(20.0f, 0.5f, 20.0f));
	floor->ActivateCollisions(false);
	mModel.push_back(floor);

	CubeModel * topCube = new CubeModel();
	topCube->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	topCube->ActivateCollisions(false);
	mModel.push_back(topCube);

	CubeModel * bottomCube = new CubeModel();
	bottomCube->SetPosition(vec3(0.0f, -10.0f, 0.0f));
	bottomCube->ActivateCollisions(false);
	mModel.push_back(bottomCube);
	
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

bool World::isParallel(glm::vec3 v1, glm::vec3 v2){
	v1 = glm::normalize(v1);
	v2 = glm::normalize(v2);

	// because the dot product of 2 vectors is equal to cos(alpha)*length(v1)*length(v2)
	// we can check to see if the dot of the two normalized vectors is 1 (or -1).

	return (glm::abs(glm::dot(v1, v2)) == 1.0f);
}