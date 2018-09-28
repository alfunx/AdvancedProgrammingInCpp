#include "fraction.h"
#include "pvector.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	pvector<fraction> pv("pvector.txt");

	for (const fraction &f : pv) {
		cout << f << endl;
	}

	return 0;
}
