//
// Created by Rene on 2023-04-15.
//

#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include "hittable.h"
#include "utils.h"

class Triangle : public Hittable {
public:
    Triangle() {}
    Triangle(Point3 v1, Point3 v2, Point3 v3, shared_ptr<Material> m)
            : a(v1), b(v2), c(v3), mat_ptr(m) {}

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    Point3 a;
    Point3 b;
    Point3 c;
    shared_ptr<Material> mat_ptr;
};

bool inside_triangle(Point3 v0, Point3 v1, Point3 v2, Point3 p, Vec3 N) {
    auto edge0 = v1 - v0;
    auto edge1 = v2 - v1;
    auto edge2 = v0 - v2;

    auto C0 = p - v0;
    auto C1 = p - v1;
    auto C2 = p - v2;

    return (dot(N, cross(edge0, C0)) > 0 &&
            dot(N, cross(edge1, C1)) > 0 &&
            dot(N, cross(edge2, C2)) > 0);
}

bool Triangle::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    auto ab = b - a;
    auto ac = c - a;
    auto normal = unit_vector(cross(ab, ac));

    auto r_dot_n_dir = dot(r.direction(), normal);
    if(fabs(r_dot_n_dir) < 1e-7) return false;
    double d = - dot(normal, a);
    double t = -(dot(r.origin(), normal) + d) / r_dot_n_dir;
    if(t < t_min || t > t_max) return false;
    auto p_hit = r.at(t);

    if(!inside_triangle(a, b, c, p_hit, normal)) return false;

    rec.t = t;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = normal;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    return true;
}
#endif //RAY_TRACER_TRIANGLE_H
