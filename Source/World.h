#pragma once

#include "ParsingHelper.h"
#include <vector>
#include <time.h>

#include "Skybox.h"

class Camera;
class Model;
class Path;

class World
{
public:
	World();
	~World();
	
    static World* GetInstance();
	static int addCounter;

	void Update(float dt);
	void Draw();

	void LoadScene(const char * scene_path);
	void LoadGame();
    void LoadCameras();

    Path* FindPath(ci_string pathName);
    Model* FindModelByIndex(unsigned int index);

	void AddModel(Model*);
    
    void drawSkybox(double D);

private:
    static World* instance;
    //static Skybox* skybox;
    
	std::vector<Model*> mModel;
    std::vector<Path*> mPath;
	std::vector<Camera*> mCamera;
	unsigned int mCurrentCamera;

	clock_t Clock;
};
