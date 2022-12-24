#pragma once
#include <vector>
#include <cstdlib>
#include "simple_mesh.hpp"
#include "../vmlib/vec3.hpp"
#include "../vmlib/mat44.hpp"
#include "../vmlib/mat33.hpp"

SimpleMeshData make_triangular_prism(
	Vec3f aSize = {1,1,1}, float angle =0.f, Vec3f aColor = {0,0,0}, Mat44f aPreTransform = kIdentity44f
);
