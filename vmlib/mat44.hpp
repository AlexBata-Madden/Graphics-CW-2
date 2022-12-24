#ifndef MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
#define MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA

#include <cmath>
#include <cassert>
#include <cstdlib>

#include "vec3.hpp"
#include "vec4.hpp"

/** Mat44f: 4x4 matrix with floats
 *
 * See vec2f.hpp for discussion. Similar to the implementation, the Mat44f is
 * intentionally kept simple and somewhat bare bones.
 *
 * The matrix is stored in row-major order (careful when passing it to OpenGL).
 *
 * The overloaded operator () allows access to individual elements. Example:
 *    Mat44f m = ...;
 *    float m12 = m(1,2);
 *    m(0,3) = 3.f;
 *
 * The matrix is arranged as:
 *
 *   ⎛ 0,0  0,1  0,2  0,3 ⎞
 *   ⎜ 1,0  1,1  1,2  1,3 ⎟
 *   ⎜ 2,0  2,1  2,2  2,3 ⎟
 *   ⎝ 3,0  3,1  3,2  3,3 ⎠
 */
struct Mat44f
{
	float v[16];

	constexpr
		float& operator() (std::size_t aI, std::size_t aJ) noexcept
	{
		assert(aI < 4 && aJ < 4);
		return v[aI * 4 + aJ];
	}
	constexpr
		float const& operator() (std::size_t aI, std::size_t aJ) const noexcept
	{
		assert(aI < 4 && aJ < 4);
		return v[aI * 4 + aJ];
	}
};

// Identity matrix
constexpr Mat44f kIdentity44f = { {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
} };

// Common operators for Mat44f.
// Note that you will need to implement these yourself.

inline
Mat44f make_identity() noexcept {
	return kIdentity44f;
}

constexpr
Mat44f operator*(Mat44f const& aLeft, Mat44f const& aRight) noexcept
{
	Mat44f result = kIdentity44f;


	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++) {

			float value = 0;

			for (size_t k = 0; k < 4; k++)
			{
				value += aLeft(i, k) * aRight(k, j);
			}
			result(i, j) = value;

		}
	}


	return result;
}

constexpr
Vec4f operator*(Mat44f const& aLeft, Vec4f const& aRight) noexcept
{
	Vec4f result = { 0.f, 0.f, 0.f, 0.f };


	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++) {

			float value = 0;

			for (size_t k = 0; k < 4; k++)
			{
				value += aLeft(i, k) * aRight[k];
			}
			result[i] = value;

		}
	}
	return result;
}

// Functions:

Mat44f invert(Mat44f const& aM) noexcept;

inline
Mat44f transpose(Mat44f const& aM) noexcept
{
	Mat44f ret = kIdentity44f;
	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
			ret(j, i) = aM(i, j);
	}
	return ret;
}

inline
Mat44f make_rotation_x(float aAngle) noexcept
{
		return Mat44f{ 1, 0, 0, 0,
				   0, cos(aAngle), -sin(aAngle), 0,
				   0, sin(aAngle), cos(aAngle), 0,
				   0, 0, 0, 1 };
}


inline
Mat44f make_rotation_y(float aAngle) noexcept
{
		return Mat44f{ cos(aAngle), 0, +sin(aAngle), 0,
				   0, 1, 0, 0,
				   -sin(aAngle), 0, cos(aAngle), 0,
				   0, 0, 0, 1 };
}

inline
Mat44f make_rotation_z(float aAngle) noexcept
{
		return Mat44f{ cos(aAngle), -sin(aAngle), 0, 0,
				   -sin(aAngle), cos(aAngle), 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1 };
}

inline
Mat44f make_translation(Vec3f aTranslation) noexcept
{
		return Mat44f{ 1, 0, 0, aTranslation.x,
				   0, 1, 0, aTranslation.y,
				   0, 0, 1, aTranslation.z,
				   0, 0, 0, 1 };
}

inline
Mat44f make_scaling(float aX, float aY, float aZ) {
	return Mat44f{ aX, 0, 0, 0,
				   0, aY, 0, 0,
				   0,  0, aZ, 0,
				   0,  0,  0, 1,
	};
}

inline
Mat44f make_perspective_projection(float aFovInRadians, float aAspect, float aNear, float aFar) noexcept
{
	float s = 1 / (tan(aFovInRadians / 2));
	float sx = s / aAspect;
	float a = -((aFar + aNear) / (aFar - aNear));
	float b = -2 * ((aFar * aNear) / (aFar - aNear));

	return Mat44f{ sx, 0, 0, 0,
				  0,  s, 0, 0,
				  0,  0, a, b,
				  0,  0,-1, 0 };
}

inline
float deg2rad(float deg)
{
	return deg * 3.1415926f / 180.0f;
}

#endif // MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
