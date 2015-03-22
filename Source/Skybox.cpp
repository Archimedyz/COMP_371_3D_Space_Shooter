//
//  Skybox.cpp
//  COMP371_Framework
//
//  Created by Skyler Wittman on 2015-03-22.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "Skybox.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>

void initSkybox()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //GL_TEXTURE_MAG_FILTER(GL_NEAREST);
    //GL_TEXTURE_MIN_FILTER(GL_NEAREST);
    
    glPushMatrix();
    
    glLoadIdentity();
    //gluLookAt(
    //          0,0,0,
    //          camera->x(),camera->y(),camera->z(),
    //          0,1,0);
}

