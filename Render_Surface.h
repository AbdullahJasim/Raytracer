#pragma once
#ifndef RENDER_SURFACE
#define RENDER_SURFACE

#include "Ray.h"

class Material;

struct hit_point {
	float t;
	Vec3 point;
	Vec3 normal;
	Material *material;
};

class Render_Surface {
public:
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_point& point) const = 0;
};
#endif