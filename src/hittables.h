#pragma once

#include "pch.h"
#include "hittable.h"

using std::make_shared;
using std::shared_ptr;

class hittable_list : public Hittable
{
public:
    hittable_list() {}
    hittable_list(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(
        const Ray &r, double t_min, double t_max, hit_record &rec) const override;

public:
    std::vector<shared_ptr<Hittable>> objects;
};

bool hittable_list::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}