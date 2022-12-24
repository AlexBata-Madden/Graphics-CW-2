#pragma once

#include <cmath>
#include <cassert>
#include <cstdlib>

#include "vec3.hpp"
#include "mat44.hpp"

struct Mat33f
{
	float v[9];

	constexpr
		float& operator() (std::size_t aI, std::size_t aJ) noexcept
	{
		assert(aI < 3 && aJ < 3);
		return v[aI * 3 + aJ];
	}
	constexpr
		float const& operator() (std::size_t aI, std::size_t aJ) const noexcept
	{
		assert(aI < 3 && aJ < 3);
		return v[aI * 3 + aJ];
	}
};

// Identity matrix
constexpr Mat33f kIdentity33f = { {
	1.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f,
} };


constexpr
Mat33f operator*(Mat33f const& aLeft, Mat33f const& aRight) noexcept
{
	Mat33f result = kIdentity33f;


	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++) {

			float value = 0;

			for (size_t k = 0; k < 3; k++)
			{
				value += aLeft(i, k) * aRight(k, j);
			}
			result(i, j) = value;

		}
	}


	return result;
}

constexpr
Vec3f operator*(Mat33f const& aLeft, Vec3f const& aRight) noexcept
{
	Vec3f ret{};
	for (std::size_t j = 0; j < 3; ++j)
	{
		for (std::size_t i = 0; i < 3; ++i)
		{
			ret[j] += aLeft(j, i) * aRight[i];
		}
	}
	return ret;
}

inline
Mat33f make_rotation_axis(Vec3f axis, float aAngle) {

	float s = sin(aAngle);
	float c = cos(aAngle);

	Vec3f temp = (1 - c) * axis;


	return Mat33f{
		(c + temp.x * axis.x),(0 + temp.x * axis.y + s * axis.z), (0 + temp.x * axis.z - s * axis.y),
		(0 + temp.y * axis.x - s * axis.z),(c + temp.y * axis.y),(0 + temp.y * axis.z + s * axis.x),
		(0 + temp.z * axis.x + s * axis.y),(0 + temp.z * axis.y - s * axis.x),(c + temp.z * axis.z)
	};


}

inline
Mat33f mat44_to_mat33(Mat44f const& aM)
{
	Mat33f ret;
	for (std::size_t i = 0; i < 3; ++i)
	{
		for (std::size_t j = 0; j < 3; ++j)
			ret(i, j) = aM(i, j);
	}
	return ret;
}
