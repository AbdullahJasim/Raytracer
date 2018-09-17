#pragma once
#ifndef RAY
#define RAY

#include "vec3.h"
#include "GlobalVec3Operators.cpp"

class Ray {
public:
	Ray() {}
	Ray(const vec3& v1, const vec3& v2) { A = v1, B = v2; }
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_parameter(float t) const { return A + t * B; }

	vec3 A;
	vec3 B;
};

#endif