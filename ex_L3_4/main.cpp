#include <string>
#include <vector>
#include "spellchecker.h"
using namespace std;

void print_help()
{
	cout << "usage: spellchecker <dict-file> <input-file> ..." << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	if (argc < 3) {
		print_help();
		return 1;
	}

	spellchecker sc(args[1]);

	for (int i = 2; i < argc; i++) {
		sc.check_file(args[i]);
	}

	return 0;
}
