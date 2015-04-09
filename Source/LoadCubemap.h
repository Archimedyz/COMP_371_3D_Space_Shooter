//
//  LoadCubemap.h
//  COMP371_Framework
//
//  Created by Skyler Wittman on 2015-04-09.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#ifndef __COMP371_Framework__LoadCubemap__
#define __COMP371_Framework__LoadCubemap__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "stb_image.h"


class LoadCubemap
{
public:
    LoadCubemap();
    ~LoadCubemap();
    void create_cube_map (const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube);
    bool load_cube_map_side ( GLuint texture, GLenum side_target, const char* file_name);
    
private:
    
};

#endif /* defined(__COMP371_Framework__LoadCubemap__) */
