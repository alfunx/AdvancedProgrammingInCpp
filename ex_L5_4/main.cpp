#include <iostream>
#include <vector>
#include "prime.h"
#include "gcd.h"
#include "fib.h"

using namespace std;

void print_help()
{
	cout << "usage: meta [prime | gcd | fib]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	if (argc < 2) {
		print_help();
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if ("prime" == args[i]) {

			cout << "template:\n"
				<< "  isprime(23)     = " << template_::isprime<23>::res << '\n'
				<< "  isprime(24)     = " << template_::isprime<24>::res << '\n'
				<< "  isprime(547)    = " << template_::isprime<547>::res << '\n' << endl;

			constexpr int isprime1 = constexpr_::isprime(23);
			constexpr int isprime2 = constexpr_::isprime(24);
			constexpr int isprime3 = constexpr_::isprime(547);
			constexpr int isprime4 = constexpr_::isprime(105943);

			cout << "constexpr:\n"
				<< "  isprime(23)     = " << isprime1 << '\n'
				<< "  isprime(24)     = " << isprime2 << '\n'
				<< "  isprime(547)    = " << isprime3 << '\n'
				<< "  isprime(105943) = " << isprime4 << endl;

		} else if ("gcd" == args[i]) {

			cout << "template:\n"
				<< "  gcd(25, 15)  = " << template_::gcd<25, 15>::res << '\n'
				<< "  gcd(20, 60)  = " << template_::gcd<20, 60>::res << '\n'
				<< "  gcd(547, 24) = " << template_::gcd<547, 23>::res << '\n' << endl;

			constexpr int gcd1 = constexpr_::gcd(25, 15);
			constexpr int gcd2 = constexpr_::gcd(20, 60);
			constexpr int gcd3 = constexpr_::gcd(547, 23);

			cout << "constexpr:\n"
				<< "  gcd(25, 15)  = " << gcd1 << '\n'
				<< "  gcd(20, 60)  = " << gcd2 << '\n'
				<< "  gcd(547, 24) = " << gcd3 << endl;

		} else if ("fib" == args[i]) {

			cout << "template:\n"
				<< "  fib(5)  = " << template_::fib<5>::res << '\n'
				<< "  fib(10) = " << template_::fib<10>::res << '\n'
				<< "  fib(20) = " << template_::fib<20>::res << '\n'
				<< "  fib(30) = " << template_::fib<30>::res << '\n' << endl;

			constexpr unsigned long long fib1 = constexpr_::fib(5);
			constexpr unsigned long long fib2 = constexpr_::fib(10);
			constexpr unsigned long long fib3 = constexpr_::fib(20);
			constexpr unsigned long long fib4 = constexpr_::fib(30);
			constexpr unsigned long long fib5 = constexpr_::fib(90);

			cout << "constexpr:\n"
				<< "  fib(5)  = " << fib1 << '\n'
				<< "  fib(10) = " << fib2 << '\n'
				<< "  fib(20) = " << fib3 << '\n'
				<< "  fib(30) = " << fib4 << '\n'
				<< "  fib(90) = " << fib5 << endl;

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
