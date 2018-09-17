#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void produceImage(vector<string> rows);

int main() {
	int nx = 200;
	int ny = 100;

	vector<string> rows;
	rows.push_back("P3\n" + to_string(nx) + " " + to_string(ny) + "\n255\n");

	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {
			float r = float(j) / float(nx);
			float g = float(i) / float(ny);
			float b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);

			//cout << ir << " " << ig << " " << ib << "\n";
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