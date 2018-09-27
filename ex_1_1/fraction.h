#ifndef FRACTION_H_
#define FRACTION_H_

#include <iostream>

class fraction
{

	// counter
	int c;

	// denominator
	int d;

	friend std::ostream& operator<<(std::ostream& os, fraction f);
	friend std::istream& operator>>(std::istream& is, fraction& f);

public:

	fraction(int cnt = 0, int dnm = 1);

	operator double();
	operator float();

	int get_counter();
	int get_denominator();

	fraction operator+(fraction f);
	fraction operator-(fraction f);
	fraction operator*(fraction f);
	fraction operator/(fraction f);
	fraction operator*(int i);
	fraction operator/(int i);
	bool operator==(fraction f);
	bool operator!=(fraction f);

};

#endif  // FRACTION_H_
