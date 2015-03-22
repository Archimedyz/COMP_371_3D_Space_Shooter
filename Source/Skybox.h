//
//  Skybox.h
//  COMP371_Framework
//
//  Created by Skyler Wittman on 2015-03-22.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#pragma once

#ifndef __COMP371_Framework__Skybox__
#define __COMP371_Framework__Skybox__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <stdio.h>

class Skybox
{
	Skybox(GLuint& texture);
	~Skybox();
};

#endif /* defined(__COMP371_Framework__Skybox__) */
