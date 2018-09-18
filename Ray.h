#pragma once
#ifndef RAY
#define RAY

#include "Vec3.h"
#include "GlobalVec3Operators.cpp"

class Ray {
public:
	Ray() {}
	Ray(const Vec3& v1, const Vec3& v2) { A = v1, B = v2; }
	Vec3 origin() const { return A; }
	Vec3 direction() const { return B; }
	Vec3 point_at_parameter(float t) const { return A + t * B; }

	Vec3 A;
	Vec3 B;
};

#endif