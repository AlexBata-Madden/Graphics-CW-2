#ifndef SIMPLE_MESH_HPP_C6B749D6_C83B_434C_9E58_F05FC27FEFC9
#define SIMPLE_MESH_HPP_C6B749D6_C83B_434C_9E58_F05FC27FEFC9

#include <glad.h>

#include <vector>

#include "../vmlib/vec3.hpp"
#include "../vmlib/vec4.hpp"
#include "../vmlib/vec2.hpp"

struct SimpleMeshData
{
	std::vector<Vec3f> positions;
	std::vector<Vec3f> colors;
	std::vector<Vec3f> normals;
	std::vector<float> alphas;
	std::vector<Vec2f> textures;
};

SimpleMeshData concatenate(SimpleMeshData, SimpleMeshData const&);

SimpleMeshData merge_meshes(std::vector<SimpleMeshData> const& meshes);

GLuint create_vao(SimpleMeshData const&);

GLuint create_vao(std::vector<SimpleMeshData> const& meshes);

#endif // SIMPLE_MESH_HPP_C6B749D6_C83B_434C_9E58_F05FC27FEFC9

