// include DevIL for image loading
#include <IL/il.h>



// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

#include <GLFW/glfw3.h>

// assimp include files. These three are usually needed.
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/PostProcess.h"
#include "assimp/Scene.h"


#include <math.h>
#include <fstream>
#include <map>
#include <string>
#include <vector>

// Information to render each assimp node
struct MyMesh{
    
    GLuint vao;
    GLuint texIndex;
    GLuint uniformBlockIndex;
    int numFaces;
};

std::vector<struct MyMesh> myMeshes;

// This is for a shader uniform block
struct MyMaterial{
    
    float diffuse[4];
    float ambient[4];
    float specular[4];
    float emissive[4];
    float shininess;
    int texCount;
};