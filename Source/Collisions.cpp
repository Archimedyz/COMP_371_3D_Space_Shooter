//--------------------------------------------------------------------------------------------------------------
// Contributors
// Nicholas Dudek
// 
//--------------------------------------------------------------------------------------------------------------



#include "Collisions.h"
#include "Model.h"

using namespace glm;

#define macrodot(uu,vv)   ((uu).x * (vv).x + (uu).y * (vv).y + (uu).z * (vv).z)

int Collisions::triangle_ray_collision(vec3 a0, vec3 a1, vec3 a2, vec3 b0, vec3 b1)
{
	// This method heavily based on the following:
	// http://geomalgorithms.com/a06-_intersect-2.html

	// Copyright 2001 softSurfer, 2012 Dan Sunday
	// This code may be freely used and modified for any purpose
	// providing that this copyright notice is included with it.
	// SoftSurfer makes no warranty for this code, and cannot be held
	// liable for any real or imagined damage resulting from its use.
	// Users of this code must verify correctness for their application.

	vec3 I, u, v, n, dir, w0, w;
    float     r, a, b;              // params to calc ray-plane intersect
    
    // get triangle edge vectors and plane normal
    u = a1 - a0;
    v = a2 - a0;
    n.x = u.y*v.z - u.z*v.y;
    n.y = u.z*v.x - u.x*v.z;
    n.z = u.x*v.y - u.y*v.x;
    
    dir = b1 - b0;              // ray direction vector
    w0 = b0 - a0;
    a = -macrodot(n,w0);
    b = macrodot(n,dir);
    
    if (fabs(b) < .00000001) {     // ray is  parallel to triangle plane
        
        if (a == 0) // ray lies in triangle plane
            return 2;
        else return 0;              // ray disjoint from plane

        return 0;
    }
    
    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                    // ray goes away from triangle
        return 0;                   // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect
    if (r > 1.0)
        return 0;
    
    I = b0 + r * dir;            // intersect point of ray and plane
    
    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = macrodot(u,u);
    uv = macrodot(u,v);
    vv = macrodot(v,v);
    w = I - a0;
    wu = macrodot(w,u);
    wv = macrodot(w,v);
    D = uv * uv - uu * vv;
    
    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // I is outside T
        return 0;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return 0;

    return 1;                       // I is in T
    
}

bool Collisions::triangle_triangle_collision(vec3 a0, vec3 a1, vec3 a2, vec3 b0, vec3 b1, vec3 b2)
{
	// skip one line per 2 triangles. each collision has min 2 lines colliding
    //if(triangle_ray_collision(a0, a1, a2, b0, b1) > 0)
      //  return true;
    if(triangle_ray_collision(a0, a1, a2, b1, b2) > 0)
        return true;
    if(triangle_ray_collision(a0, a1, a2, b0, b2) > 0)
        return true;
    if(triangle_ray_collision(b0, b1, b2, a0, a1) > 0)
        return true;
    if(triangle_ray_collision(b0, b1, b2, a1, a2) > 0)
        return true;
    if(triangle_ray_collision(b0, b1, b2, a0, a2) > 0)
        return true;
    return false;
}

#define STATICSIZE 2000
bool Collisions::collide_objects(Model* a, Model* b)
{
    long n = a->get_varray().size();
    long m = b->get_varray().size();

    std::vector<vec3> aav = a->get_varray();
    std::vector<vec3> bbv = b->get_varray();

    vec4 temp;

    static std::vector<vec3> aa(STATICSIZE);
    static std::vector<vec3> bb(STATICSIZE);

    mat4 wm = a->GetWorldMatrix();
    for(int i = 0; i < n ; ++i)
    {
        temp = wm * vec4(aav[i], 1);
        temp.x = temp.x/temp.w;
        temp.y=temp.y/temp.w;
        temp.z=temp.z/temp.w;

		aa[i]=vec3(temp);
    }
    wm = b->GetWorldMatrix();
    for(int i = 0; i < m ; ++i)
    {
        temp = wm * vec4(bbv[i], 1);
        temp.x = temp.x/temp.w;
        temp.y=temp.y/temp.w;
        temp.z=temp.z/temp.w;

        bb[i]  = vec3(temp);
    }
    
    for(int i=0; i < n-3; i+=3)
    {
        for(int j=0; j < m-3; j+=3)
        {
            if(triangle_triangle_collision(aa[i], aa[i+1], aa[i+2], bb[j], bb[j+1], bb[j+2]))
                return true;
        }
    }
    return false;
}
