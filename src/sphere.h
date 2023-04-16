//
// Created by Rene on 2023-04-09.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include <utility>

#include "hittable.h"
#include "ray.h"

class Sphere : public Hittable {
public:
    Sphere() = default;
    Sphere(Point3 cen, double r, std::shared_ptr<Material> m)
        : center(cen), radius(r), mat_ptr(std::move(m)) {}

    bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    Point3 center;
    double radius{};
    shared_ptr<Material> mat_ptr;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    Vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() -  radius * radius;
    auto discriminant = half_b*half_b - a*c;
    if(discriminant < 0) {
        return false;
    }
    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd)/a;
    if(root < t_min || root > t_max) {
        root = (-half_b + sqrtd)/a;
        if(root < t_min || root > t_max)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif //RAY_TRACER_SPHERE_H


