//
// Created by Rene on 2023-04-09.
//

#ifndef RAY_TRACER_HITTABLE_LIST_H
#define RAY_TRACER_HITTABLE_LIST_H

#include "hittable.h"

#include "memory"
#include "vector"

using std::shared_ptr;
using std::make_shared;
class HittableList : public Hittable {
public:
    HittableList() = default;
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); };
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_record& rec
            ) const override;

public:
    std::vector<shared_ptr<Hittable>> objects;

};

bool HittableList::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(const auto& object: objects) {
        if(object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //RAY_TRACER_HITTABLE_LIST_H
