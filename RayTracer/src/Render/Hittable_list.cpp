#include "rtpch.h"

#include "Math/MathUtil.h"
#include "Math/Vec3.h"
#include "Render/Hittable_list.h"

namespace RayT
{
    bool HittableList::hit(const Ray &r, double t_min, double t_max, hit_record &record) const
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto &object : m_Object)
        {
            if (object->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                record = temp_rec;
            }
        }

        return hit_anything;
    }
}