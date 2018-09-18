#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Ray.h"

using namespace std;

void produceImage(vector<string> rows);

Vec3 color(const Ray& ray) {
	Vec3 unit_direction = unit_vector(ray.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
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

	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {
			float u = float(j) / float(nx);
			float v = float(i) / float(ny);

			Ray ray(origin, lower_left_cover + u * horizontal + v * vertical);
			Vec3 col = color(ray);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			string temp = to_string(ir) + " " + to_string(ig) + " " + to_string(ib) + "\n";
			rows.push_back(temp);
		}
	}

	produceImage(rows);
	//system("pause");
}

void produceImage(vector<string> rows) {
	ofstream outputFile;
	outputFile.open("image.ppm");

	for (unsigned int i = 0; i < rows.size(); i++) {
		outputFile << rows[i];
	}

	outputFile.close();
}