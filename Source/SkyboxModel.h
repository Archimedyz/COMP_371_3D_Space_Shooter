// Contributors:
//Skyler Wittman
//Nicholas Dudek
//Andrey Uspenskiy

#pragma once
#ifndef __COMP371_Framework__SkyboxModel__
#define __COMP371_Framework__SkyboxModel__

#include <stdio.h>
#include "Model.h"
#include "Renderer.h"
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Texture.hpp"
#include "Objloader.hpp"
#include "VBOindexer.hpp"

class SkyboxModel : public Model
{
public:
    SkyboxModel();
    ~SkyboxModel();
    void Update(float dt);
    void Draw();
	void RenderShadowVolume(glm::vec4 lightPos);

	static void LoadBuffers();
	std::vector < glm:: vec3> get_varray() { return SkyboxModel::vArray; }
protected:

	// drawing buffers. each subclass has a set of these buffers which contain the modelspace coordinates of the vertices. 
	static std::vector<glm::vec3> vArray;
	static unsigned int vertexbuffer;
	static unsigned int uvbuffer;
	static unsigned int normalbuffer;
	static unsigned int elementbuffer;
	static std::vector<unsigned short> indices;
};

#endif /* defined(__COMP371_Framework__SkyboxModel__) */


