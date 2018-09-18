#include "Material.h"
#ifndef LAMBERT
#define LAMBERT

class Lambert : public Material {
public:
	Vec3(albedo);
	Lambert(const Vec3& a) : albedo(a) {}

	virtual bool scatter(const Ray& ray_in, const hit_point& hp, Vec3& attenuation, Ray& scattered) const {
		Vec3 target = hp.point + hp.normal + random_in_unit_sphere();
		scattered = Ray(hp.point, target - hp.point);
		attenuation = albedo;
		return true;
	}
};

#endif