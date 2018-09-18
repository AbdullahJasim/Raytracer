#include "Material.h"
#ifndef METAL
#define METAL

class Metal : public Material {
public:
	Vec3 albedo;
	Metal(const Vec3& a) : albedo(a) {}

	virtual bool scatter(const Ray& ray_in, const hit_point& hp, Vec3& attenuation, Ray& scattered) const {
		Vec3 reflected = reflect(unit_vector(ray_in.direction()), hp.normal);
		scattered = Ray(hp.point, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), hp.normal) > 0);
	}
};

#endif