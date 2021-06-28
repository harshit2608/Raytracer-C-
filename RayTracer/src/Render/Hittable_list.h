#pragma once

#include "Math/Vec3.h"
#include "rtpch.h"
#include "Render/Hittable.h"

namespace RayT
{
    using std::make_shared;
    using std::shared_ptr;

    class HittableList : public Hittable
    {
    public:
        HittableList() {}
        HittableList(shared_ptr<Hittable> object)
        {
            add(object);
        }

        void clear() { m_Object.clear(); }
        void add(shared_ptr<Hittable> object) { m_Object.push_back(object); }

        virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &record) const override;

    private:
        std::vector<shared_ptr<Hittable>> m_Object;
    };
}