#pragma once
#ifndef GLOBAL_VEC_OPERATIONS
#define GLOBAL_VEC_OPERATIONS

#include "Vec3.h"

//+
inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

//-
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

//multiplication
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

//division
inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

//multiplication by constant (both orders)
inline Vec3 operator* (float t, const Vec3 &v) {
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator* (const Vec3 &v, float t) {
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

//division by constant
inline Vec3 operator/ (const Vec3 &v, float t) {
	return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

//dot product
inline float dot(const Vec3 &v1, const Vec3 &v2) {
	return (v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2]);
}

//cross product
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(
		v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0],
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
	);
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - (2 * dot(v, n) * n);
}

//+=
inline Vec3& Vec3::operator+=(const Vec3 &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

//-=
inline Vec3& Vec3::operator-=(const Vec3 &v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

//*=
inline Vec3& Vec3::operator*=(const Vec3 &v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

///=
inline Vec3& Vec3::operator/=(const Vec3 &v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

//* constant
inline Vec3& Vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

///= constant
inline Vec3& Vec3::operator/=(const float t) {
	float k = 1.0f / t;

	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

//unit vector
inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

inline Vec3 random_in_unit_sphere() {
	Vec3 p;

	//Keep creating random vectors until we get one inside the unit sphere
	do {
		p = 2.0f * Vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX) - Vec3(1.0f, 1.0f, 1.0f);
	} while (p.squared_length() >= 1.0f);

	return p;
}
#endif