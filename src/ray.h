#pragma once

#include "pch.h"
#include "maths/vec3.h"

class Ray
{
public:
    Ray() {}
    Ray(const point3 &origin, const vec3 &direction)
        : orig(origin), dir(direction) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at(double t) const
    {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};

// Let’s think of a ray as a function P(t) = A + tb.Here P is a 3D position along a line in 3D. A is the ray origin and b is the ray direction.The ray parameter t is a real number(double in the code).Plug in a different t and P(t) moves the point along the ray.Add in negative t values and you can go anywhere on the 3D line.For positive t, you get only the parts in front of A, and this is what is often called a half - line or ray.