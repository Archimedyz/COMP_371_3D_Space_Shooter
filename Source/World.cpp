#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "EventManager.h"

#include "World.h"
#include "Renderer.h"
#include "ParsingHelper.h"

#include "StaticCamera.h"
#include "ThirdPersonCamera.h"

#include "AsteroidFactory.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "Path.h"
#include "Projectile.h"

#include "ShipModel.h"
#include "Loader.h"

#include "Texture.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Variables.h"

#include "ImageLoader.h"
#include "LoadCubemap.h"
#include "SkyBox.h"
#include "stb_image.h"

using namespace std;
using namespace glm;

const char* bmp_FT = "../Resources/GalaxySkybox/Galaxy_FT.bmp";
const char* bmp_BK = "../Resources/GalaxySkybox/Galaxy_BK.bmp";
const char* bmp_UP = "../Resources/GalaxySkybox/Galaxy_UP.bmp";
const char* bmp_DN = "../Resources/GalaxySkybox/Galaxy_DN.bmp";
const char* bmp_LT = "../Resources/GalaxySkybox/Galaxy_LT.bmp";
const char* bmp_RT = "../Resources/GalaxySkybox/Galaxy_RT.bmp";


GLuint make_big_cube () {
    float points[] = {
        -10.0f,  10.0f, -10.0f,
        -10.0f, -10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,
        10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,
        
        -10.0f, -10.0f,  10.0f,
        -10.0f, -10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f,  10.0f,
        -10.0f, -10.0f,  10.0f,
        
        10.0f, -10.0f, -10.0f,
        10.0f, -10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,
        
        -10.0f, -10.0f,  10.0f,
        -10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f, -10.0f,  10.0f,
        -10.0f, -10.0f,  10.0f,
        
        -10.0f,  10.0f, -10.0f,
        10.0f,  10.0f, -10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        -10.0f,  10.0f,  10.0f,
        -10.0f,  10.0f, -10.0f,
        
        -10.0f, -10.0f, -10.0f,
        -10.0f, -10.0f,  10.0f,
        10.0f, -10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,
        -10.0f, -10.0f,  10.0f,
        10.0f, -10.0f,  10.0f
    };
    GLuint vbo;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (
                  GL_ARRAY_BUFFER, 3 * 36 * sizeof (GLfloat), &points, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    return vao;
}

bool load_cube_map_side ( GLuint texture, GLenum side_target, const char* file_name)
{
    glBindTexture (GL_TEXTURE_CUBE_MAP, texture);
    
    int x, y, n;
    int force_channels = 4;
    unsigned char*  image_data = stbi_load (
                                            file_name, &x, &y, &n, force_channels);
    if (!image_data) {
        fprintf (stderr, "ERROR: could not load %s\n", file_name);
        return false;
    }
    // non-power-of-2 dimensions check
    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
        fprintf (
                 stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name
                 );
    }
    
    // copy image data into 'target' side of cube map
    glTexImage2D (
                  side_target,
                  0,
                  GL_RGBA,
                  x,
                  y,
                  0,
                  GL_RGBA,
                  GL_UNSIGNED_BYTE,
                  image_data
                  );
    free (image_data);
    return true;
}

void create_cube_map (
                      const char* front,
                      const char* back,
                      const char* top,
                      const char* bottom,
                      const char* left,
                      const char* right,
                      GLuint* tex_cube
                      ) {
    // generate a cube-map texture to hold all the sides
    glActiveTexture (GL_TEXTURE0);
    glGenTextures (1, tex_cube);
    
    // load each image and copy into a side of the cube-map texture
    assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front));
    assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back));
    assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top));
    assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom));
    assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left));
    assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right));
    // format cube map texture
    
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

World* World::instance;
int World::addCounter;
//Skybox* skyboxObj = new Skybox();

LoadCubemap* cubemap = new LoadCubemap();

// cube-map shaders
GLuint cubemapShader;
GLuint cube_vao;
GLuint cube_map_texture;

World::World()
{
    instance = this;
	addCounter = 0;
	//skyboxObj->initSkybox();
	cube_vao = make_big_cube();
    create_cube_map (bmp_FT, bmp_BK, bmp_UP, bmp_DN, bmp_LT, bmp_RT, &cube_map_texture);
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
}

World* World::GetInstance()
{
    return instance;
}

void World::Update(float dt)
{
	// User Inputs
	// 0 1 2 3 to change the Camera
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1 ) == GLFW_PRESS)
	{
		mCurrentCamera = 0;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 1)
		{
			mCurrentCamera = 1;
		}
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 2)
		{
			mCurrentCamera = 2;
		}
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_4 ) == GLFW_PRESS)
	{
        // Third Person Cam
		if (mCamera.size() > 3)
		{
			mCurrentCamera = 3;
		}
	}

	// 0 and 9 to change the shader
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_0 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_SOLID_COLOR);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_BLUE);
	}
    

	// Update current Camera
	mCamera[mCurrentCamera]->Update(dt);
	
	// Update models
	for (int i = 0; i < mModel.size(); ++i)
	{
		mModel[i]->Update(dt);

		mModel[i]->CheckCollisions(mModel); // Check if the model is colliding with any other, and set their destroyed flags to true if they are.

		if (mModel[i]->IsDestroyed())
		{
			// HANDLE COLLISIONS SOMEHOW
			// Probably override a method from model which each type of object handles separately.
			// Large asteroids fragment, projectiles explode, ship explodes and takes damage, etc.
			mModel.erase(mModel.begin() + i); // Finally deletes model.
		}
	}

	if (++addCounter > 100){
		mModel.push_back(AsteroidFactory::createAsteroid(0));
		addCounter = 0;
	}
	
}

void World::Draw()
{
	
	Renderer::BeginFrame();
    
    Renderer::SetShader(SHADER_SKYBOX);
    // note that this view matrix should NOT contain camera translation.
    //int cube_V_location = glGetUniformLocation (Renderer::GetCurrentShader(), "V");
    //int cube_P_location = glGetUniformLocation (Renderer::GetCurrentShader(), "P");
    
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable (GL_CULL_FACE); // cull face
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); // set counter-clock-wise vertex order to mean the front
    glClearColor (0.2, 0.2, 0.2, 1.0); // grey background to help spot mistakes
    
    glDepthMask (GL_FALSE);
    glUseProgram (Renderer::GetCurrentShader());
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_CUBE_MAP, cube_map_texture);
    glBindVertexArray (cube_vao);
    glDrawArrays (GL_TRIANGLES, 0, 36);
    glDepthMask (GL_TRUE);
    
	// Set shader to use
	//glUseProgram(Renderer::GetShaderProgramID());
    
	// This looks for the MVP Uniform variable in the Vertex Program
	GLuint VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform"); 

	// Send the view projection constants to the shader
	mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);
    
	// draw skybox
    
//	glTranslatef(25, 0, 25);
//	glScalef(75, 75, 75);
//	skyboxObj->drawSkybox();


	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		// Draw model
		(*it)->Draw();
	}
	// Send the view projection constants to the shader
	VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform");
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	for (vector<Path*>::iterator it = mPath.begin(); it < mPath.end(); ++it)
	{
		// Draw model
		(*it)->Draw();
	}

	Renderer::EndFrame();

}

void World::LoadScene(const char * scene_path)
{
	// Using case-insensitive strings and streams for easier parsing
	ci_ifstream input;
	input.open(scene_path, ios::in);

	// Invalid file
	if(input.fail() )
	{
		fprintf(stderr, "Error loading file: %s\n", scene_path);
		getchar();
		exit(-1);
	}

	ci_string item;
	while( std::getline( input, item, '[' ) )
	{
	       ci_istringstream iss( item );

		ci_string result;
		if( std::getline( iss, result, ']') )
		{
			if( result == "cube" )
			{
				// Box attributes
				CubeModel* cube = new CubeModel();
				cube->Load(iss);
				mModel.push_back(cube);
			}
	           else if( result == "sphere" )
	           {
	               SphereModel* sphere = new SphereModel();
	               sphere->Load(iss);
	               mModel.push_back(sphere);
	           }
	           else if( result == "path" )
			{
				Path* path = new Path();
				path->Load(iss);
	               mPath.push_back(path);
			}
			else if ( result.empty() == false && result[0] == '#')
			{
				// this is a comment line
			}
			else
			{
				fprintf(stderr, "Error loading scene file... !");
				getchar();
				exit(-1);
			}
	    }
	}
	input.close();

	// Set PATH vertex buffers
	for (vector<Path*>::iterator it = mPath.begin(); it < mPath.end(); ++it)
	{
		// Draw model
		(*it)->CreateVertexBuffer();
	}
}

void World::LoadGame()
{
	// All the commented out code that was used for the assignment to load paths and things is at the end of this file.
	// I moved it there since it's just extra clutter to keep it here commented out, it can probably
	// be deleted. -Nick
    
	mModel.push_back(AsteroidFactory::createAsteroid(0));

	Projectile::SetLastFired(time(NULL)); // Start the timer of last fired to when the game starts.

	//Loader::loadModel();

    LoadCameras();
}

void World::LoadCameras()
{
    // Setup Camera
    mCamera.push_back(new StaticCamera(vec3(3.0f, 5.0f, 5.0f),  vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
    mCamera.push_back(new StaticCamera(vec3(3.0f, 30.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
    mCamera.push_back(new StaticCamera(vec3(0.5f,  0.5f, 5.0f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
    
	CubeModel * character = new CubeModel();
    character->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	character->ActivateCollisions(false);
    mModel.push_back(character);

	//Ship Character controlled with Third Person Camera
	ShipModel * ship_model = new ShipModel(vec3(5.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));
	ship_model->ActivateCollisions(false);
	mCamera.push_back(new ThirdPersonCamera(ship_model));
	mModel.push_back(ship_model);

    mCurrentCamera = 0;
}

Path* World::FindPath(ci_string pathName)
{
    for(std::vector<Path*>::iterator it = mPath.begin(); it < mPath.end(); ++it)
    {
        if((*it)->GetName() == pathName)
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