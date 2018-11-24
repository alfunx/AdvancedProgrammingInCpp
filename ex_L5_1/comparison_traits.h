#ifndef COMPARISON_TRAITS_H_
#define COMPARISON_TRAITS_H_

#include <complex>

template<typename T>
struct comparison_traits
{

	static bool equal(const T& a, const T& b)
	{
		return a == b;
	}

	static bool lower(const T& a, const T& b)
	{
		return a < b ;
	}

	static bool greater(const T& a, const T& b)
	{
		return a > b ;
	}

	static T min(T a, T b)
	{
		return lower(a, b) ? a : b;
	}

	static T max(T a, T b)
	{
		return greater(a, b) ? a : b;
	}

};

template<typename T>
struct comparison_traits<std::complex<T>>
{

	static bool equal(const std::complex<T>& a, const std::complex<T>& b)
	{
		return norm(a) == norm(b) ;
	}

	static bool lower(const std::complex<T>& a, const std::complex<T>& b)
	{
		return norm(a) < norm(b) ;
	}

	static bool greater(const std::complex<T>& a, const std::complex<T>& b)
	{
		return norm(a) > norm(b) ;
	}

	static std::complex<T> min(std::complex<T> a, std::complex<T> b)
	{
		return lower(a, b) ? a : b;
	}

	static std::complex<T> max(std::complex<T> a, std::complex<T> b)
	{
		return greater(a, b) ? a : b;
	}

};

#endif  // COMPARISON_TRAITS_H_
