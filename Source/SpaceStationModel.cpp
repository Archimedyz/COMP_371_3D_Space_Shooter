
//--------------------------------------------------------------------------------------------------------------
// Contributors
// Andrey Uspenskiy
// Nicholas Dudek
// Skyler Wittman
//--------------------------------------------------------------------------------------------------------------
//model from http://blenderartists.org/forum/showthread.php?142414-A-Quick-amp-Simple-Borg-Cube

#include "SpaceStationModel.h"


//holders for buffers
std::vector<glm::vec3> SpaceStationModel::vArray;
unsigned int SpaceStationModel::vertexbuffer;
unsigned int SpaceStationModel::uvbuffer;
unsigned int SpaceStationModel::normalbuffer;
unsigned int SpaceStationModel::elementbuffer;
std::vector<unsigned short> SpaceStationModel::indices;

//initiate GLuint to hold skybox texture
GLuint spaceStationBMP;


void SpaceStationModel::LoadBuffers()
{
#if defined(PLATFORM_OSX)
    const char * modelPath = "Resources/Models/Final_Skybox_V3.obj";
#else
    const char * modelPath = "../Resources/Models/Final_Skybox_V3.obj";
#endif
    Loader::loadModel(modelPath, SpaceStationModel::vArray, SpaceStationModel::vertexbuffer, SpaceStationModel::uvbuffer, SpaceStationModel::normalbuffer, SpaceStationModel::elementbuffer, SpaceStationModel::indices);
    
    // load texture for skybox
    spaceStationBMP = loadBMP_custom("../Resources/Textures/SpaceStationTexture.bmp");
}

SpaceStationModel::SpaceStationModel() :Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f))
{
    //initializing space station with lighting
    name = "SPACESTATION";
    ka = 0.5f;
    kd = 0.3f;
    ks = 0.7f;
    n = 15.0f;
    
    //skybox scaled to 50 units
    mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    mScaling = glm::vec3(15.0f, 15.0f, 15.0f);
    
    CollisionsOn = false;
}

SpaceStationModel::~SpaceStationModel()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &elementbuffer);
}

void SpaceStationModel::Update(float dt)
{
    
}

void SpaceStationModel::Draw()
{
    Model::Draw();
    
    //world matrix info
    GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);
    
    glBindTexture(GL_TEXTURE_2D, spaceStationBMP);
    
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
    glDisableVertexAttribArray(3);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void SpaceStationModel::RenderShadowVolume(glm::vec4 lightPos){
    
}
