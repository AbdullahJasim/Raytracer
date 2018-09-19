#pragma once
#ifndef CAMERA
#define CAMERA

#define _USE_MATH_DEFINES
#include <math.h>  
#include "Ray.h"

Vec3 random_in_unit_disk() {
	Vec3 p;

	do {
		p = 2.0f * Vec3((float) rand() / RAND_MAX, (float)rand() / RAND_MAX, 0) - Vec3(1.0f, 1.0f, 0.0f);
	} while (dot(p, p) >= 1.0f);

	return p;
}

class Camera {
public:
	Vec3 origin;
	Vec3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	float lens_radius;

	Camera(Vec3 look_from, Vec3 look_at, Vec3 v_up, float vfov, float aspect, float aperture, float focus_dist) {
		lens_radius = aperture / 2.0f;
		float theta = vfov * (float) M_PI / 180.0f;
		float half_height = tan(theta/2);
		float half_width = aspect * half_height;

		origin = look_from;
		w = unit_vector(look_from - look_at);
		u = unit_vector(cross(v_up, w));
		v = cross(w, u);

		//lower_left_corner = Vec3(-half_width, -half_height, -1.0f);
		lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
		horizontal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;
	}

	Ray get_ray(float s, float t) { 
		Vec3 rd = lens_radius * random_in_unit_disk();
		Vec3 offset = u * rd.x() + v * rd.y();
		return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset); 
	}


};

#endif