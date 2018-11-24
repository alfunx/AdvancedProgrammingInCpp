#ifndef FIB_H_
#define FIB_H_

namespace template_non_tail_
{

	template<unsigned int N>
	struct fib
	{
		static const unsigned int res = fib<N - 1>::res + fib<N - 2>::res;
	};

	template<>
	struct fib<1>
	{
		static const unsigned int res = 1;
	};

	template<>
	struct fib<0>
	{
		static const unsigned int res = 0;
	};

};

namespace template_
{

	template<unsigned int N, unsigned int A, unsigned int B>
	struct fib_helper
	{
		static const unsigned int res = fib_helper<N - 1, B, A + B>::res;
	};

	template<unsigned int A, unsigned int B>
	struct fib_helper<1, A, B>
	{
		static const unsigned int res = B;
	};

	template<unsigned int A, unsigned int B>
	struct fib_helper<0, A, B>
	{
		static const unsigned int res = A;
	};

	template<unsigned int N>
	struct fib
	{
		static const unsigned int res = fib_helper<N, 0, 1>::res;
	};

};

namespace constexpr_non_tail_
{

	constexpr unsigned long long fib(unsigned long long n)
	{
		if (n < 2)
			return n;
		return fib(n - 1) + fib(n - 2);
	}

}

namespace constexpr_
{

	constexpr unsigned long long fib(unsigned long long n,
			unsigned long long a = 0,
			unsigned long long b = 1)
	{
		if (n == 0)
			return a;
		if (n == 1)
			return b;
		return fib(n - 1, b, a + b);
	}

}

#endif  // FIB_H_
