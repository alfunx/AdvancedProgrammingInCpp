#ifndef GCD_H_
#define GCD_H_

namespace template_
{

	template<int A, int B>
	struct gcd
	{
		static const int res = (B == 0) ? A : gcd<B, A % B>::res;
	};

	template<int A>
	struct gcd<A, 0>
	{
		static const int res = A;
	};

}

namespace constexpr_
{

	constexpr int gcd(int a, int b)
	{
		return (b == 0) ? a : gcd(b, a % b);
	}

}

#endif  // GCD_H_
