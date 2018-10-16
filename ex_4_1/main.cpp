#include "fraction.h"
#include "pset.h"
#include "pvector.h"
using namespace std;

void pvector_test()
{
	pvector<fraction> pv("pvector.txt");

	for (const fraction &f : pv) {
		cout << f << endl;
	}

	fraction f;
	double i = f;
	cout << ">>> ";
	cin >> f;
	pv.push_back(f);
}

void pset_test()
{
	pset<fraction> ps("pset.txt");

	for (const fraction &f : ps) {
		cout << f << endl;
	}

	fraction f;
	cout << ">>> ";
	cin >> f;

	auto it = ps.insert(f);
	if (!it.second)
		cout << " already exists: " << *it.first << endl;
}

void print_help()
{
	cout << "usage: traits [-s] [-v]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	for (int i = 1; i < argc; i++) {
		if ("-v" == args[i]) {
			pvector_test();
			return 0;
		} else if ("-s" == args[i]) {
			pset_test();
			return 0;
		} else if ("-h" == args[i]) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	return 0;
}
