#include "Material.h"
#ifndef DIELECTRIC
#define DIELECTRIC

class Dielectric : public Material {
public:
	float ref_index;

	Dielectric(float ri) : ref_index(ri) {}

	virtual bool scatter(const Ray& ray_in, const hit_point& hp, Vec3& attenuation, Ray& scattered) const {
		Vec3 outward_normal;
		Vec3 reflected = reflect(ray_in.direction(), hp.normal);
		attenuation = Vec3(1.0f, 1.0f, 1.0f);

		float ni_over_nt;
		float reflect_prob;
		float cosine;
		Vec3 refracted;

		if (dot(ray_in.direction(), hp.normal) > 0) {
			outward_normal = -hp.normal;
			ni_over_nt = ref_index;
			cosine = dot(ray_in.direction(), hp.normal) / ray_in.direction().length();
			cosine = cosine * ref_index;
			//cosine = sqrt(1 - ref_index * ref_index * (1 - cosine * cosine));
		} else {
			outward_normal = hp.normal;
			ni_over_nt = 1.0f / ref_index;
			cosine = -dot(ray_in.direction(), hp.normal) / ray_in.direction().length();
		}

		if (refract(ray_in.direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, ref_index);
			//scattered = Ray(hp.point, refracted);
		} else {
			reflect_prob = 1.0f;
			//return false;
		}

		if ((float) rand() / RAND_MAX < reflect_prob) {
			scattered = Ray(hp.point, reflected);
		} else {
			scattered = Ray(hp.point, refracted);
		}

		return true;
	}
};

#endif