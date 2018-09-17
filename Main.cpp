#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Ray.h"

using namespace std;

void produceImage(vector<string> rows);

vec3 color(const Ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main() {
	int nx = 200;
	int ny = 100;

	vector<string> rows;
	rows.push_back("P3\n" + to_string(nx) + " " + to_string(ny) + "\n255\n");

	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {
			vec3 col(float(j) / float(nx), float(i) / float(ny), 0.2f);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			string temp = to_string(ir) + " " + to_string(ig) + " " + to_string(ib) + "\n";
			rows.push_back(temp);
		}
	}

	produceImage(rows);
	system("pause");
}

void produceImage(vector<string> rows) {
	ofstream outputFile;
	outputFile.open("image.ppm");

	for (unsigned int i = 0; i < rows.size(); i++) {
		outputFile << rows[i];
	}

	outputFile.close();
}