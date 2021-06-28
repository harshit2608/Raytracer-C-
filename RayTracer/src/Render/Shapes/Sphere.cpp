#include "rtpch.h"

#include "Math/MathUtil.h"
#include "Math/Vec3.h"
#include "Render/Shapes/Sphere.h"

namespace RayT
{
    bool Sphere::hit(const Ray &r, double t_min, double t_max, hit_record &record) const
    {
        vec3 oc = r.GetOrigin() - m_Center;
        auto a = r.GetDirection().length_squared();
        auto half_b = dot(oc, r.GetDirection());
        auto c = oc.length_squared() - m_Radius * m_Radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0)
            return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        record.t = root;
        record.p = r.at(record.t);
        vec3 outward_normal = (record.p - m_Center) / m_Radius;
        record.set_face_normal(r, outward_normal);
        record.mat_ptr = mat_ptr;

        return true;
    }
}