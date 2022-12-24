#include "cuboid.hpp"

SimpleMeshData make_cuboid(Vec3f aSize, Vec3f aColor, Mat44f aPreTransform, float alpha, bool textured)
{
	// 0: 		Vec3f{ -aSize.x / 2, aSize.y / 2, -aSize.z / 2 },
	// 1:		Vec3f{ -aSize.x / 2, aSize.y / 2, aSize.z / 2 },
	// 2:		Vec3f{ aSize.x / 2, aSize.y / 2, aSize.z / 2 },
	// 3:		Vec3f{ aSize.x / 2, aSize.y / 2, -aSize.z / 2 },
	
	// 4: 		Vec3f{ -aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
	// 5:		Vec3f{ -aSize.x / 2, -aSize.y / 2, aSize.z / 2 },
	// 6:		Vec3f{ aSize.x / 2, -aSize.y / 2, aSize.z / 2 },
	// 7:		Vec3f{ aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },

	std::vector<Vec3f> pos =
	{
		Vec3f{ -aSize.x / 2, aSize.y / 2, -aSize.z / 2 }, // 0
		Vec3f{ -aSize.x / 2, aSize.y / 2, aSize.z / 2 }, // 1
		Vec3f{ aSize.x / 2, aSize.y / 2, aSize.z / 2 }, //	2
		Vec3f{ aSize.x / 2, aSize.y / 2, aSize.z / 2 }, //  2
		Vec3f{ aSize.x / 2, aSize.y / 2, -aSize.z / 2 }, //	3
		Vec3f{ -aSize.x / 2, aSize.y / 2, -aSize.z / 2 }, // 0

		Vec3f{ -aSize.x / 2, aSize.y / 2, aSize.z / 2 }, // 1
		Vec3f{ -aSize.x / 2, -aSize.y / 2, aSize.z / 2 }, // 5
		Vec3f{ aSize.x / 2, aSize.y / 2, aSize.z / 2 }, // 2
		Vec3f{ -aSize.x / 2, -aSize.y / 2, aSize.z / 2 }, // 5
		Vec3f{ aSize.x / 2, -aSize.y / 2, aSize.z / 2 }, // 6
		Vec3f{ aSize.x / 2, aSize.y / 2, aSize.z / 2 }, // 2

		Vec3f{ aSize.x / 2, aSize.y / 2, -aSize.z / 2 }, //3
		Vec3f{ aSize.x / 2, -aSize.y / 2, -aSize.z / 2 }, //7
		Vec3f{ -aSize.x / 2, -aSize.y / 2, -aSize.z / 2 }, //4
		Vec3f{ aSize.x / 2, aSize.y / 2, -aSize.z / 2 }, // 3
		Vec3f{ -aSize.x / 2, -aSize.y / 2, -aSize.z / 2 }, // 4
		Vec3f{ -aSize.x / 2, aSize.y / 2, -aSize.z / 2 }, // 0

		Vec3f{ aSize.x / 2, aSize.y / 2, aSize.z / 2 },
		Vec3f{ aSize.x / 2, -aSize.y / 2, aSize.z / 2 },
		Vec3f{ aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
		Vec3f{ aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
		Vec3f{ aSize.x / 2, aSize.y / 2, -aSize.z / 2 },
		Vec3f{ aSize.x / 2, aSize.y / 2, aSize.z / 2 },

		Vec3f{ -aSize.x / 2, aSize.y / 2, -aSize.z / 2 },
		Vec3f{ -aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
		Vec3f{ -aSize.x / 2, aSize.y / 2, aSize.z / 2 },
		Vec3f{ -aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
		Vec3f{ -aSize.x / 2, -aSize.y / 2, aSize.z / 2 },
		Vec3f{ -aSize.x / 2, aSize.y / 2, aSize.z / 2 },


		Vec3f{ -aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
		Vec3f{ aSize.x / 2, -aSize.y / 2, aSize.z / 2 },
		Vec3f{ -aSize.x / 2, -aSize.y / 2, aSize.z / 2 },
		Vec3f{ -aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
		Vec3f{ aSize.x / 2, -aSize.y / 2, -aSize.z / 2 },
		Vec3f{ aSize.x / 2, -aSize.y / 2, aSize.z / 2 },
	};

	Mat33f const N = mat44_to_mat33(transpose(invert(aPreTransform)));

	Vec3f face1 = N * normalise(cross(pos[1] - pos[0], pos[2] - pos[0]));
	Vec3f face2 = N * normalise(cross(pos[7] - pos[6], pos[8] - pos[6]));
	Vec3f face3 = N * normalise(cross(pos[13] - pos[12], pos[14] - pos[12]));
	Vec3f face4 = N * normalise(cross(pos[19] - pos[18], pos[20] - pos[18]));
	Vec3f face5 = N * normalise(cross(pos[25] - pos[24], pos[26] - pos[24]));
	Vec3f face6 = N * normalise(cross(pos[31] - pos[30], pos[32] - pos[30]));


	std::vector<Vec3f> norms = {
		face1,face1,face1,face1,face1,face1,

		face2,face2,face2,face2,face2,face2,

		face3,face3,face3,face3,face3,face3,

		face4,face4,face4,face4,face4,face4,

		face5,face5,face5,face5,face5,face5,

		face6,face6,face6,face6,face6,face6,

	};

	// Create the colors of the cuboid vertices.
	std::vector<Vec3f> col(pos.size(), aColor);

	std::vector<float> alphas(pos.size(), alpha);

	// Apply the pre-transform matrix to the cuboid vertices.
	for (auto& p : pos)
	{
		Vec4f p4{ p.x, p.y, p.z, 1.0f };
		Vec4f t = aPreTransform * p4;
		t /= t.w;

		p = Vec3f{ t.x, t.y, t.z };
	}

	if (textured == true)
	{

		std::vector<Vec2f> tex = {
			// top face
			Vec2f{0.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,1.0},
			Vec2f{0.0,1.0},

			//front face
			Vec2f{0.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,1.0},

			// back face
			Vec2f{0.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{0.0,1.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,1.0},

			// right face
			Vec2f{0.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,1.0},
			Vec2f{0.0,1.0},

			// left face
			Vec2f{0.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,1.0},

			//bottom face
			Vec2f{0.0,0.0},
			Vec2f{1.0,1.0},
			Vec2f{0.0,1.0},
			Vec2f{0.0,0.0},
			Vec2f{1.0,0.0},
			Vec2f{1.0,1.0},

		};
		return SimpleMeshData{ std::move(pos), std::move(col), std::move(norms), std::move(alphas), std::move(tex) };
	}

	else
	{
		std::vector<Vec2f> tex = {
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		Vec2f{ 0.0,0.0 },
		};

		return SimpleMeshData{ std::move(pos), std::move(col), std::move(norms), std::move(alphas), std::move(tex) };
	}

};