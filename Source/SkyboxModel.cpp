#include "SkyboxModel.h"
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Objloader.hpp"
#include "VBOindexer.hpp"

SkyboxModel::SkyboxModel() : SkyboxModel(glm::vec3(40.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f))
{}

SkyboxModel::SkyboxModel(glm::vec3 position, glm::vec3 scaling) : Model(position, scaling)
{
#if defined(PLATFORM_OSX)
    const char * modelPath = "Models/skyboxRegularNormals.obj";
#else
    const char * modelPath = "../Resources/Models/skyboxRegularNormals.obj";
#endif
    Loader::loadModel(modelPath);
}


SkyboxModel::~SkyboxModel()
{
}

void SkyboxModel::Update(float dt)
{
    // If you are curious, un-comment this line to have spinning cubes!
    // That will only work if your world transform is correct...
    //mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second
    
    Model::Update(dt);
}

void SkyboxModel::Draw()
{
    GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, Loader::vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, Loader::uvbuffer);
    glVertexAttribPointer(
                          1,                                // attribute
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, Loader::normalbuffer);
    glVertexAttribPointer(
                          2,                                // attribute
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Loader::elementbuffer);
    
    // Draw the triangles !
    glDrawElements(
                   GL_TRIANGLES,      // mode
                   Loader::indices.size(),    // count
                   GL_UNSIGNED_SHORT,   // type
                   (void*)0           // element array buffer offset
                   );
    
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

bool SkyboxModel::ParseLine(const std::vector<ci_string> &token)
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

