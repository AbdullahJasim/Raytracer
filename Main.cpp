#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "float.h"
#include "Sphere.h"
#include "Surfaces_List.h"

using namespace std;

void save_image(vector<string> rows);

Vec3 color(const Ray& ray, Render_Surface* surfaces_list) {
	hit_point hp;

	if (surfaces_list->hit(ray, 0.0f, FLT_MAX, hp)) {
		return 0.5 * Vec3(hp.normal.x() + 1, hp.normal.y() + 1, hp.normal.z() + 1);
	} else {
		Vec3 unit_direction = unit_vector(ray.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}

int main() {
	int nx = 200;
	int ny = 100;

	vector<string> rows;
	rows.push_back("P3\n" + to_string(nx) + " " + to_string(ny) + "\n255\n");

	Vec3 lower_left_cover(-2.0f, -1.0f, -1.0f);
	Vec3 horizontal(4.0f, 0.0f, 0.0f);
	Vec3 vertical(0.0f, 2.0f, 0.0f);
	Vec3 origin(0.0f, 0.0f, 0.0f);

	Render_Surface *list[2];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
	Render_Surface *surfaces_list = new Surfaces_List(list, 2);

	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {
			float u = float(j) / float(nx);
			float v = float(i) / float(ny);

			Ray ray(origin, lower_left_cover + u * horizontal + v * vertical);
			Vec3 col = color(ray, surfaces_list);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			string temp = to_string(ir) + " " + to_string(ig) + " " + to_string(ib) + "\n";
			rows.push_back(temp);
		}
	}

	save_image(rows);
	//system("pause");
}

void save_image(vector<string> rows) {
	ofstream outputFile;
	outputFile.open("image.ppm");

	for (unsigned int i = 0; i < rows.size(); i++) {
		outputFile << rows[i];
	}

	outputFile.close();
}