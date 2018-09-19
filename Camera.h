#pragma once
#ifndef CAMERA
#define CAMERA

#define _USE_MATH_DEFINES
#include <math.h>  
#include "Ray.h"

class Camera {
public:
	Camera(Vec3 look_from, Vec3 look_at, Vec3 v_up, float vfov, float aspect) {
		Vec3 u, v, w;

		float theta = vfov * (float) M_PI / 180.0f;
		float half_height = tan(theta/2);
		float half_width = aspect * half_height;

		origin = look_from;
		w = unit_vector(look_from - look_at);
		u = unit_vector(cross(v_up, w));
		v = cross(w, u);

		//lower_left_corner = Vec3(-half_width, -half_height, -1.0f);
		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2 * half_width * u;
		vertical = 2 * half_height * v;
	}

	Ray get_ray(float u, float v) { return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

	Vec3 origin;
	Vec3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
};

#endif