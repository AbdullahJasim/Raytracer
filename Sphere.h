#pragma once
#ifndef SPHERE
#define SPHERE

//#include "Render_Surface.h"
#include "Material.h"

class Sphere : public Render_Surface {
public:
	Vec3 center;
	float radius;
	Material *material;

	Sphere() {}
	Sphere(Vec3 point, float r, Material *mat) : center(point), radius(r), material(mat) {};
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_point& hp) const;
};
#endif