#pragma once

#include <vector>
#include <cstdlib>
#include "simple_mesh.hpp"
#include "../vmlib/vec3.hpp"
#include "../vmlib/mat44.hpp"
#include "../vmlib/mat33.hpp"

SimpleMeshData make_cuboid(
    Vec3f aSize = { 1.f, 1.f, 1.f },
    Vec3f aColor = { 1.f, 1.f, 1.f },
    Mat44f aPreTransform = kIdentity44f,
    float alpha = 1.f,
    bool textured = false
);
