#include "vec3.h"

//+
inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

//-
inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

//multiplication
inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

//division
inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

//multiplication by constant (both orders)
inline vec3 operator* (float t, const vec3 &v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator* (const vec3 &v, float t) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

//division by constant
inline vec3 operator/ (const vec3 &v, float t) {
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

//dot product
inline float dot(const vec3 &v1, const vec3 &v2) {
	return (v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2]);
}

//cross product
inline vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3(
		v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0],
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
	);
}

//+=
inline vec3& vec3::operator+=(const vec3 &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

//-=
inline vec3& vec3::operator-=(const vec3 &v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

//*=
inline vec3& vec3::operator*=(const vec3 &v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

///=
inline vec3& vec3::operator/=(const vec3 &v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

//* constant
inline vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

///= constant
inline vec3& vec3::operator/=(const float t) {
	float k = 1.0f / t;

	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

//unit vector
inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}