#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "float.h"
#include "Sphere.h"
#include "Surfaces_List.h"
#include "Camera.h"
#include "Material.h"
#include "Lambert.cpp"
#include "Metal.cpp"
#include "Dielectric.cpp"

using namespace std;

void save_image(vector<string> rows);

Vec3 color(const Ray& ray, Render_Surface* surfaces_list, int depth) {
	hit_point hp;

	if (surfaces_list->hit(ray, 0.001f, FLT_MAX, hp)) {
		//Add diffusion and reflection
		Ray scattered;
		Vec3 attenuation;

		if (depth < 50 && hp.material->scatter(ray, hp, attenuation, scattered)) {
			return attenuation * color(scattered, surfaces_list, depth +1);
		} else {
			return Vec3(0.0f, 0.0f, 0.0f);
		}
	} else {
		Vec3 unit_direction = unit_vector(ray.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}

Render_Surface *random_scene() {
	int n = 500;
	Render_Surface **list = new Render_Surface*[n + 1];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambert(Vec3(0.5f, 0.5f, 0.5f)));

	int i = 1;

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = (float)rand() / RAND_MAX;
			Vec3 center(a + 0.9f * (float)rand() / RAND_MAX, 0.2f, b + 0.9f * (float)rand() / RAND_MAX);

			if (choose_mat < 0.8) {
				list[i++] = new Sphere(center, 0.2f, new Lambert(Vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX)));
			}
			else if (choose_mat < 0.95) {
				list[i++] = new Sphere(center, 0.2f, new Metal(Vec3(0.5f * (1 + (float)rand() / RAND_MAX), 0.5f * (1 + (float)rand() / RAND_MAX), 0.5f * (1 + (float)rand() / RAND_MAX)), 0.5f * (float)rand() / RAND_MAX));
			}
			else {
				list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
			}
		}
	}

	list[i++] = new Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5));
	list[i++] = new Sphere(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, new Lambert(Vec3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(Vec3(4.0f, 1.0f, 0.0f), 1.0f, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.0f));

	return new Surfaces_List(list, i);
}

int main() {
	int nx = 200;
	int ny = 100;
	int ns = 100;

	vector<string> rows;
	rows.push_back("P3\n" + to_string(nx) + " " + to_string(ny) + "\n255\n");

	/*
	Render_Surface *list[5];
	list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, new Lambert(Vec3(0.1f, 0.2f, 0.5f)));
	list[1] = new Sphere(Vec3(0, -100.5, -1.0f), 100.0f, new Lambert(Vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 0.0f));
	list[3] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f));
	list[4] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), -0.45f, new Dielectric(1.5f));
	Render_Surface *surfaces_list = new Surfaces_List(list, 5);
	*/

	Render_Surface *surfaces_list = random_scene();

	Vec3 look_from(3, 3, 2);
	Vec3 look_at(0, 0, -1);
	float dist_to_focus = (look_from - look_at).length();
	float aperture = 2.0;
	Camera cam(look_from, look_at, Vec3(0, 1, 0), 20, float(nx)/float(ny), aperture, dist_to_focus);

	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {
			Vec3 col(0.0f, 0.0f, 0.0f);
			
			for (int s = 0; s < ns; s++) {
				float u = float(j + (float) rand() / RAND_MAX) / float(nx);
				float v = float(i + (float)rand() / RAND_MAX) / float(ny);

				Ray ray = cam.get_ray(u, v);
				Vec3 p = ray.point_at_parameter(2.0f);
				col += color(ray, surfaces_list, 0);
			}

			col = col / float(ns);
			//Gamma correction
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			string temp = to_string(ir) + " " + to_string(ig) + " " + to_string(ib) + "\n";
			rows.push_back(temp);
		}
	}

	save_image(rows);
	system("pause");
}

void save_image(vector<string> rows) {
	ofstream outputFile;
	outputFile.open("image.ppm");

	for (unsigned int i = 0; i < rows.size(); i++) {
		outputFile << rows[i];
	}

	outputFile.close();
}