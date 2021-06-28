#pragma once

#include "Math/Vec3.h"
#include "rtpch.h"
#include "Render/Hittable.h"

namespace RayT
{
    class Sphere : public Hittable
    {
    public:
        Sphere();
        Sphere(point3 center, double r, shared_ptr<Material> m)
			: m_Center(center), m_Radius(r), mat_ptr(m) {};

        virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &record) const override;

    private:
        point3 m_Center;
        double m_Radius;
        shared_ptr<Material> mat_ptr;
    };
}