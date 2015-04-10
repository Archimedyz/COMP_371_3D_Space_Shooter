#pragma once
#ifndef __COMP371_Framework__SkyboxModel__
#define __COMP371_Framework__SkyboxModel__

#include <stdio.h>
#include "Model.h"
#include "Renderer.h"
class SkyboxModel : public Model
{
public:
    SkyboxModel();
    SkyboxModel(glm::vec3 position, glm::vec3 scaling);
    ~SkyboxModel();
    void Update(float dt);
    void Draw();
protected:
    virtual bool ParseLine(const std::vector<ci_string> &token);
};

#endif /* defined(__COMP371_Framework__SkyboxModel__) */


