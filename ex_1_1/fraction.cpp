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

inline bool check_char(std::istream& is, char ch, bool badbit = true)
{
	char c;
	is >> c;

	if (c != ch) {
		is.putback(c);

		if (badbit)
			is.setstate(std::ios::badbit);

		return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, fraction f)
{
	os << '(' << f.c << '/' << f.d << ')';
	return os;
}

std::istream& operator>>(std::istream& is, fraction& f)
{
	fraction g;

	if (check_char(is, '(', false)) {
		is >> g.c;
	} else {
		is >> g.c;
		if (is)
			f = g;
		return is;
	}

	if (check_char(is, '/', false)) {
		is >> g.d;
	} else if (check_char(is, ')')) {
		if (is)
			f = g;
		return is;
	}

	check_char(is, ')');

	if (is)
		f = g;

	return is;
}

fraction::operator double()
{
	return (double)c / d;
}

fraction::operator float()
{
	return (float)c / d;
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
