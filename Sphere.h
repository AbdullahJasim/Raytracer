#pragma once
#ifndef SPHERE
#define SPHERE

#include "Render_Surface.h"

class Sphere : public Render_Surface {
public:
	Vec3 center;
	float radius;

	Sphere() {}
	Sphere(Vec3 point, float r) : center(point), radius(r) {};
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_point& hp) const;
};

#endif