#pragma once
#include "Sphere.h"

//Spehere equation: r^2 = x^2 + y^2 + z^2
//Distance from center to point xyz = x-cx + y-cy + z-cz
//If the center is at cx, cy, cz: r^2 = (x-cx)^2 + (y-cy)^2 + (z-cz)^2
//Vector from sphere center to point = pointVector - centerVector
//Dot product of that vector = (x-cx)^2 + (y-cy)^2 + (z-cz)^2
//So r^2 = dot(pointVector - centerVector)
//We want to know if the ray we cast hits the sphere
//dot((pointVector(t) - centerVector), (pointVector(t) - centerVector)) = r^2, we want to find that t
//dot((A + t*B - centerVector), (A + t*B - centerVector)) = r^2
//With expansion we get:
//t^2 * dot(B, B) + 2 * t * dot(B, A-C) + dot(A-C, A-C) - r^2 = 0
//Solve for t
bool Sphere::hit(const Ray& ray, float t_min, float t_max, hit_point& hp) const {
	Vec3 oc = ray.origin() - center;

	//Quadratic formula
	float a = dot(ray.direction(), ray.direction());
	float b = dot(oc, ray.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp > t_min && temp < t_max) {
			hp.t = temp;
			hp.point = ray.point_at_parameter(hp.t);
			hp.normal = (hp.point - center) / radius;
			hp.material = material;
			return true;
		}

		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp > t_min && temp < t_max) {
			hp.t = temp;
			hp.point = ray.point_at_parameter(hp.t);
			hp.normal = (hp.point - center) / radius;
			hp.material = material;
			return true;
		}
	}

	return false;
}