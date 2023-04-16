//
// Created by Rene on 2023-04-16.
//

#ifndef RAY_TRACER_RECTANGULAR_PRISM_H
#define RAY_TRACER_RECTANGULAR_PRISM_H

#include "utils.h"
#include "hittable_list.h"

class Triangle;

class RectangularPrism : public HittableList {
public:
    RectangularPrism() {}
    RectangularPrism(Point3 bottom_left, double width, double length, double height, shared_ptr<Material> m) {
        Point3 bottom_left_front = bottom_left;
        Point3 bottom_left_back = bottom_left_front + Vec3(0,0,-length);
        Point3 bottom_right_front = bottom_left_front + Vec3(width,0,0);
        Point3 bottom_right_back = bottom_right_front + Vec3(0,0,-length);
        Point3 top_left_front = bottom_left_front + Vec3(0, height, 0);
        Point3 top_left_back = top_left_front + Vec3(0,0,-length);
        Point3 top_right_front = top_left_front + Vec3(width,0,0);
        Point3 top_right_back = top_right_front + Vec3(0,0,-length);

        // Bottom Face
        add(make_shared<Triangle>(bottom_left_front, bottom_left_back, bottom_right_front, m));
        add(make_shared<Triangle>(bottom_right_back, bottom_left_back, bottom_right_front, m));
        // Top Face
        add(make_shared<Triangle>(top_left_front, top_left_back, top_right_front, m));
        add(make_shared<Triangle>(top_right_back, top_left_back, top_right_front, m));
        // Front Face
        add(make_shared<Triangle>(top_left_front, bottom_right_front, top_right_front, m));
        add(make_shared<Triangle>(top_left_front, bottom_right_front,bottom_left_front,  m));
        // Back Face
        add(make_shared<Triangle>(top_left_back, top_right_back, bottom_left_back, m));
        add(make_shared<Triangle>(bottom_right_back, top_right_back, bottom_left_back, m));
        // Left Face
        add(make_shared<Triangle>(top_left_front, bottom_left_back, top_left_back, m));
        add(make_shared<Triangle>(top_left_front, bottom_left_back, bottom_left_front, m));
        // Right Face
        add(make_shared<Triangle>(top_right_back, bottom_right_front, bottom_right_back, m));
        add(make_shared<Triangle>(top_right_back, bottom_right_front, top_right_front, m));
    }
};

#endif //RAY_TRACER_RECTANGULAR_PRISM_H
