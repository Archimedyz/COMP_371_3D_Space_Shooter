//
//  Collisions.h
//  COMP371_Framework
//
//  Created by Nick Dudek on 2015-04-05.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#pragma once

class Model;

#include <stdio.h>
#include <glm/glm.hpp>

class Collisions
{
public:
    static bool collide_objects(Model *a, Model *b);
    static int triangle_ray_collision(glm::vec3 a1, glm::vec3 a2, glm::vec3 a3, glm::vec3 b1, glm::vec3 b2);
    static bool triangle_triangle_collision(glm::vec3 ,glm::vec3 ,glm::vec3 ,glm::vec3 ,glm::vec3 ,glm::vec3);
};


