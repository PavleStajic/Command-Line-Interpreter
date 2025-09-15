#include "Touch.h"
#include <fstream>

void Touch::execut(string& argument, string& option, string& filepath) {
	if (fileExists(filepath)) {
		print(filepath, "Error: File already exists.");
	}
	else {
		ofstream newFile(filepath);
	}
}

bool Touch::fileExists(const string& filepath) {
	ifstream file(filepath);
	return file.good();
}