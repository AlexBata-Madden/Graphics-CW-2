#include "cylinder.hpp"

SimpleMeshData make_cylinder(bool aCapped, std::size_t aSubdivs, Vec3f aColor, Mat44f aPreTransform)
{
	std::vector<Vec3f> pos;
	std::vector<Vec3f> norms;

	Mat33f const N = mat44_to_mat33(transpose(invert(aPreTransform)));

	float prevY = std::cos(0.f);
	float prevZ = std::sin(0.f);

	for (std::size_t i = 0; i < aSubdivs; ++i)
	{
		float const angle = (i + 1) / float(aSubdivs) * 2.f * 3.1415926f;

		float y = std::cos(angle);
		float z = std::sin(angle);

		if (aCapped == true) {

			pos.emplace_back(Vec3f{ 0.f, y, z });
			pos.emplace_back(Vec3f{ 0, 0, 0 });
			pos.emplace_back(Vec3f{ 0.f, prevY, prevZ });

			pos.emplace_back(Vec3f{ 1.f, 0, 0 });
			pos.emplace_back(Vec3f{ 1.f,y, z });
			pos.emplace_back(Vec3f{ 1.f,prevY, prevZ });

			Vec3f norm1 = Vec3f{ -1, 0, 0 };
			Vec3f norm2 = Vec3f{ 1, 0, 0 };

			norm1 = N * norm1;
			norm2 = N * norm2;

			norm1 = normalise(norm1);
			norm2 = normalise(norm2);

			norms.emplace_back(norm1);
			norms.emplace_back(norm1);
			norms.emplace_back(norm1);

			norms.emplace_back(norm2);
			norms.emplace_back(norm2);
			norms.emplace_back(norm2);

		}

		pos.emplace_back(Vec3f{ 0.f, prevY, prevZ });
		pos.emplace_back(Vec3f{ 1.f, prevY, prevZ });
		pos.emplace_back(Vec3f{ 0.f, y, z });

		pos.emplace_back(Vec3f{ 0.f, y, z });
		pos.emplace_back(Vec3f{ 1.f, prevY, prevZ });
		pos.emplace_back(Vec3f{ 1.f, y, z });

		Vec3f norm1 = Vec3f{ 0.5f, prevY, prevZ } - Vec3f{ 0.5f, 0, 0 };
		Vec3f norm2 = Vec3f{ 0.5f, y, z } - Vec3f{ 0.5f, 0, 0 };

		norm1 = N * norm1;
		norm2 = N * norm2;

		norm1 = normalise(norm1);
		norm2 = normalise(norm2);

		norms.emplace_back(norm1);
		norms.emplace_back(norm1);
		norms.emplace_back(norm2);


		norms.emplace_back(norm2);
		norms.emplace_back(norm1);
		norms.emplace_back(norm2);

		prevY = y;
		prevZ = z;
	}
	std::vector<Vec3f> col(pos.size(), aColor);
	std::vector<float> alpha(pos.size(), 1.f);
	std::vector<Vec2f> texture(pos.size(), Vec2f{0.0,0.0});

	for (std::size_t i = 0; i < pos.size(); ++i)
	{
		Vec4f p4{ pos[i].x, pos[i].y, pos[i].z, 1.f };
		Vec4f t = aPreTransform * p4;
		t /= t.w;

		pos[i] = Vec3f{ t.x, t.y, t.z };


	}

	return SimpleMeshData{ std::move(pos), std::move(col), std::move(norms), std::move(alpha), std::move(texture)};
}
