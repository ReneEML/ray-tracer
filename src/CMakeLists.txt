cmake_minimum_required(VERSION 3.24)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray_tracer main.cpp vec3.h color.h ray.h hittable.h sphere.h hittable_list.h utils.h camera.h material.h triangle.h)
