//--------------------------------------------------------------------------------------------------------------
// Contributors
// 
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once


#include "ParsingHelper.h"
#include <vector>
#include <time.h>

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
    void LoadCameras();

	void AddModel(Model*);

private:
    static World* instance;

	Model* player;
	std::vector<Model*> mModel;
    std::vector<Path*> mPath;
	std::vector<Camera*> mCamera;
	unsigned int mCurrentCamera;

};
