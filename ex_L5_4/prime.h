#ifndef PRIME_H_
#define PRIME_H_

namespace template_
{

	template<int P, int N>
	struct isprime_helper
	{
		static const int res = isprime_helper<P, P % N ? N - 1 : 0>::res;
	};

	template<int P>
	struct isprime_helper<P, 1>
	{
		static const int res = 1;
	};

	template<int P>
	struct isprime_helper<P, 0>
	{
		static const int res = 0;
	};

	template<int N>
	struct isprime
	{
		static const int res = isprime_helper<N, N - 1>::res;
	};

	template<int P>
	struct nextprime
	{
		static const int res = isprime<P>::res ? P : nextprime<P + 1>::res;
	};

}

namespace constexpr_
{

	constexpr bool isprime_helper(int p, int n)
	{
		return (n % p == 0) ? false :
			(p * p < n) ? isprime_helper(p + 2, n) : true;
	}

	constexpr bool isprime(int n)
	{
		return (n % 2 == 0) ? (n == 2) : isprime_helper(3, n);
	}

	constexpr int nextprime(int p)
	{
		return isprime(p) ? p : nextprime(p + 1);
	}

}

#endif  // PRIME_H_
