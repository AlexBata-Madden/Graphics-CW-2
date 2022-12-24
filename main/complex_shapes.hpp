#pragma once

#include <vector>
#include <cstdlib>

#include "simple_mesh.hpp"
#include "../vmlib/vec3.hpp"
#include "../vmlib/mat44.hpp"
#include "../vmlib/mat33.hpp"
#include "cylinder.hpp"
#include "cuboid.hpp"
#include "triangular_prism.hpp"

SimpleMeshData make_clock();

SimpleMeshData make_pendulum();

SimpleMeshData make_house();

SimpleMeshData make_table();
