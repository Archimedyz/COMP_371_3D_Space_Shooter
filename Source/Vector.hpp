

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <math.h>

// ===============
// 2D Vector Class
// ===============

class Vec2 {
    
public:
    
    union {
        struct {
            float x;
            float y;
        };
        float v[2];
    };
    
public:
    
    Vec2();
    Vec2(float X, float Y);
    Vec2(const Vec2 & r);
    
    Vec2 & operator = (float Val);
    Vec2 & operator = (const Vec2 & r);
    
    bool operator == (const Vec2 & r) const;
    bool operator != (const Vec2 & r) const;
    
public:
    
    // Linear interpolation between this vector and 'vec'.
    Vec2 Lerp(const Vec2 & vec, float t) const;
    
    // Dot product between this vector and 'r'.
    float DotProduct(const Vec2 & r) const;
    
    // The absolute length of this vector.
    float Length() const;
    
    // Normalize this vector. (Divide it by it's length).
    void Normalize();
    
    // Scale the vector by a given factor. (vector = vector * factor)
    void Scale(float factor);
    
    // Negate the vector. (vector = -vector)
    void Negate();
};

// ===============
// 3D Vector Class
// ===============

class Vec3 {
    
public:
    
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float v[3];
    };
    
public:
    
    Vec3();
    Vec3(float X, float Y, float Z);
    Vec3(const Vec3 & r);
    
    Vec3 & operator = (float Val);
    Vec3 & operator = (const Vec3 & r);
    
    bool operator == (const Vec3 & r) const;
    bool operator != (const Vec3 & r) const;
    
public:
    
    // Dot product between this vector and 'r'.
    float DotProduct(const Vec3 & r) const;
    
    // The absolute length of this vector.
    float Length() const;
    
    // Computes the cross product of this vector and 'vec' and return the result as a new vector.
    Vec3 CrossProduct(const Vec3 & vec) const;
    
    // Linear interpolation between this vector and 'vec'.
    Vec3 Lerp(const Vec3 & vec, float t) const;
    
    // Normalize this vector. (Divide it by it's length).
    void Normalize();
    
    // Scale the vector by a given factor. (vector = vector * factor)
    void Scale(float factor);
    
    // Negate the vector. (vector = -vector)
    void Negate();
};

#endif // __VECTOR_HPP__
