#include <iostream>
#include "fraction.h"

fraction::fraction(int cnt, int dnm) : c(cnt), d(dnm)
{
	/* void */
}

int gcf(int a, int b)
{
	return b == 0 ? a : gcf(b, a % b);
}

int lcm(int a, int b)
{
	return (a * b) / gcf(a, b);
}

inline void check_char(std::istream& is, char ch)
{
	char c;
	is >> c;

	if (c != ch) {
		is.putback(c);
		is.setstate(std::ios::badbit);
	}
}

std::ostream& operator<<(std::ostream& os, fraction f)
{
	os << '(' << f.c << '/' << f.d << ')';
	return os;
}

std::istream& operator>>(std::istream& is, fraction& f)
{
	fraction g;
	check_char(is, '(');
	is >> g.c;
	check_char(is, '/');
	is >> g.d;
	check_char(is, ')');

	if (is)
		f = g;

	return is;
}

int fraction::get_counter()
{
	return c;
}

int fraction::get_denominator()
{
	return d;
}

fraction fraction::operator+(fraction f)
{
	int dnm = lcm(d, f.get_denominator());
	int cnt = c * dnm / d + f.get_counter() * dnm / f.get_denominator();

	return fraction(cnt, dnm);
}

fraction fraction::operator-(fraction f)
{
	int dnm = lcm(d, f.get_denominator());
	int cnt = c * dnm / d + -f.get_counter() * dnm / f.get_denominator();

	return fraction(cnt, dnm);
}

fraction fraction::operator*(fraction f)
{
	int n = gcf(c, f.get_denominator());
	int m = gcf(f.get_counter(), d);

	return fraction((c / n) * (f.get_counter() / m),
			(d / m * (f.get_denominator() / n)));
}

fraction fraction::operator/(fraction f)
{
	int n = gcf(c, f.get_counter());
	int m = gcf(f.get_denominator(), d);

	return fraction((c / n) * (f.get_denominator() / m),
			(d / m * (f.get_counter() / n)));
}

fraction fraction::operator*(int i)
{
	return *this * fraction(i);
}

fraction fraction::operator/(int i)
{
	return *this / fraction(i);
}

bool fraction::operator==(fraction f)
{
	return (double)c / f.get_counter() == (double)d / f.get_denominator();
}

bool fraction::operator!=(fraction f)
{
	return (double)c / f.get_counter() != (double)d / f.get_denominator();
}
