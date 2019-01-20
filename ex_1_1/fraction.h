#ifndef FRACTION_H_
#define FRACTION_H_

#include <iostream>

class fraction
{

	// counter
	int c;

	// denominator
	int d;

	friend std::ostream& operator <<(std::ostream& os, fraction f);
	friend std::istream& operator >>(std::istream& is, fraction& f);

public:

	fraction(int cnt = 0, int dnm = 1);

	int get_counter() const;
	int get_denominator() const;

	template<typename T>
	operator T() const
	{
		return (T)c / d;
	}

	fraction operator +(const fraction f) const;
	fraction operator -(const fraction f) const;
	fraction operator *(const fraction f) const;
	fraction operator /(const fraction f) const;
	fraction operator *(const int i) const;
	fraction operator /(const int i) const;
	bool operator ==(const fraction f) const;
	bool operator !=(const fraction f) const;
	bool operator <(const fraction f) const;
	bool operator >(const fraction f) const;

};

#endif  // FRACTION_H_
