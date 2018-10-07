#include <iostream>
using namespace std;

inline int factorial(int n)
{
	return (n < 2) ? n : n * factorial(n - 1);
}

int main(int argc, char** argv)
{
	cout << factorial(10000) << endl;

	return 0;
}
