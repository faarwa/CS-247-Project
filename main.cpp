#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	int randomSeed = 0;
	if (argc > 1) {
		randomSeed = argv[1];
	}

	while (!cin.eof()) {
		Command cmd = Command();
		cout << "Enter command:";
		cin >> cmd;
	}

	return 0;
}