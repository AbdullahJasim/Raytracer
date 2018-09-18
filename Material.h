#pragma once
#ifndef MATERIAL
#define MATERIAL

//#include "Ray.h"
#include "Render_Surface.h"
//#include "Sphere.h"
//#include "Render_Surface.h"

class Material {
public:
	virtual bool scatter(const Ray& ray_in, const hit_point& hp, Vec3& attenuation, Ray& scattered) const = 0;
};

#endif