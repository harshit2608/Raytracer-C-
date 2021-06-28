#pragma once

#include "Math/Vec3.h"
#include "rtpch.h"

namespace RayT
{
    class Ray
    {
    public:
        Ray() = default;
        Ray(const point3 &origin, const vec3 &direction)
            : m_Origin(origin), m_Direction(direction)
        {
        }

        point3 GetOrigin() const { return m_Origin; }
        vec3 GetDirection() const { return m_Direction; }

        point3 at(double t) const
        {
            return m_Origin + t * m_Direction;
        }

    private:
        point3 m_Origin;
        vec3 m_Direction;
    };
}