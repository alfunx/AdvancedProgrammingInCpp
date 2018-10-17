#include <iostream>
using namespace std;

void swap(int& i, int& j)
{
	int t = i;
	i = j;
	j = t;
}

int main(int argc, char** argv)
{
	int i = 1;
	int j = 2;

	cout << "i=" << i << ", j=" << j << endl;

	swap(i, j);

	cout << "i=" << i << ", j=" << j << endl;

	return 0;
}
