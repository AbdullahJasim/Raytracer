#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "vec3.h"

using namespace std;

void produceImage(vector<string> rows);

int main() {
	int nx = 200;
	int ny = 100;

	vector<string> rows;
	rows.push_back("P3\n" + to_string(nx) + " " + to_string(ny) + "\n255\n");

	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {
			vec3 col(float(j) / float(nx), float(i) / float(ny), 0.2);

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

	for (int i = 0; i < rows.size(); i++) {
		outputFile << rows[i];
	}

	outputFile.close();
}