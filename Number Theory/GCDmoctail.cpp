#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_set>
#include <unordered_map>
#include <memory.h>
#include <limits>
#include <list>

namespace algorithm_lib
{
	const int m1e9n7 = 1000000007;

	class number_theory_t
	{
	public:
		template<typename T>
		static T gcd(const T& a, const T& b)
		{
			T va = a;
			T vb = b;
			while (vb)
			{
				auto r = va % vb;
				va = vb;
				vb = r;
			}
			return va;
		}

		template<typename T, typename... U>
		static T gcd(const T& a, const T& b, const U&... others)
		{
			return gcd(gcd(a, b), others...);
		}

		template<typename T>
		static T lcm(const T& a, const T& b)
		{
			return T((int64_t)a * b / gcd(a, b));
		}

		template<typename T, typename... U>
		static T lcm(const T& a, const T& b, const U&... others)
		{
			return lcm(lcm(a, b), others...);
		}

		static std::vector<int> mobius(int n)
		{
			std::vector<int> r(n + 1, -1);
			r[1] = 1;
			for (int i = 2; i <= n; ++i)
				for (int j = i * 2; j <= n; j += i)
					r[j] -= r[i];
			return r;
		}

		static std::vector<std::vector<int>> batch_factors(const std::vector<int>& mu)
		{
			int n = (int)mu.size() - 1;
			std::vector<std::vector<int>> r(n + 1);
			for (int i = 1; i <= n; ++i)
			{
				if (mu[i])
					for (int j = i; j <= n; j += i)
						r[j].push_back(i);
			}
			return r;
		}

		static std::vector<std::vector<int>> batch_factors(int n)
		{
			std::vector<std::vector<int>> r(n + 1);
			for (int i = 1; i <= n; ++i)
			{
				for (int j = i; j <= n; j += i)
					r[j].push_back(i);
			}
			return r;
		}

		static std::vector<std::vector<int>> batch_prime_factors(int n)
		{
			std::vector<std::vector<int>> r(n + 1);
			for (int i = 2; i <= n; ++i)
			{
				if (0 != r[i].size())
					continue;
				for (int j = i; j <= n; j += i)
					r[j].push_back(i);
			}
			return r;
		}

		template<typename T>
		static std::vector<T> factors_within(T n)
		{
			std::vector<T> r((size_t)n + 1);
			for (T k = 1; k <= n; ++k)
				r[(size_t)k] = k;

			for (T i = 2; i <= n; ++i)
			{
				if (r[(size_t)i] != i)
					continue;
				for (T j = 2 * i; j <= n; j += i)
				{
					r[(size_t)j] = i;
				}
			}
			return r;
		}

		template<typename T>
		static std::vector<T> factors_of(T n)
		{
			auto factors = factors_within((T)sqrt(n));
			std::vector<T> r;
			for (size_t k = 1; k < factors.size(); ++k)
			{
				if ((T)k != factors[k])
					continue;
				if (n % (T)k == 0)
				{
					r.push_back((T)k);
					auto k2 = n / (T)k;
					if (k2 != (T)k)
						r.push_back(k2);
				}
			}
			return r;
		}

		template<typename T>
		static std::vector<T> prime_factors(T n)
		{
			std::vector<T> r;
			for (auto factor : { 2, 3, 5, 7 })
			{
				while (n && (n % factor == 0))
				{
					r.push_back(factor);
					n /= factor;
				}
			}

			auto factors = factors_within((T)sqrt(n));
			for (size_t k = 11; k < factors.size(); ++k)
			{
				if ((T)k != factors[k])
					continue;
				while (n % (T)k == 0)
				{
					r.push_back((T)k);
					n /= (T)k;
				}
			}
			if(1 != n)
				r.push_back(n);
			return r;
		}

		template<typename T>
		static bool is_prime(const T& n)
		{
			if (1 >= n)
				return false;
			return 1 == prime_factors(n).size();
		}

		template<typename T>
		static std::vector<T> distinct_prime_factors(const T& n)
		{
			auto r0 = prime_factors(n);
			std::unordered_set<T> r(r0.begin(), r0.end());
			return std::vector<T>(r.cbegin(), r.cend());
		}

		static std::vector<int> primes_within(int n)
		{
			std::vector<int> r;
			if (n < 2)
				return r;
			r.push_back(2);

			std::vector<int> factors_within((n - 1) / 2);
			for (int k = 3; k <= n; k += 2)
				factors_within[(k - 3) / 2] = k;

			for (int i = 3; i <= n; i += 2)
			{
				if (factors_within[(i - 3) / 2] != i)
					continue;
				for (int j = 3 * i; j <= n; j += i * 2)
				{
					factors_within[(j - 3) / 2] = i;
				}
			}

			for (size_t k = 0; k < factors_within.size(); ++k)
			{
				auto factor = (int)k * 2 + 3;
				if (factor == factors_within[k])
					r.push_back(factor);
			}
			return r;
		}

		template<typename T>
		static bool is_primitive_root(const T& p, const std::vector<T>& factors, const T& candidate)
		{
			for (auto factor : factors)
			{
				factor = (p - 1) / factor;
				if (power_mod<int64_t>(candidate, factor, p) == 1)
					return false;
			}
			return true;
		}

		template<typename T>
		static T find_primitive_root(const T& p, const std::vector<T>& factors, const T& start)
		{
			if (2 == p)
				return 3;
			for (T r = start; ; ++r)
			{
				for (auto factor : factors)
					if (is_primitive_root(p, factors, r))
						return r;
			}
			return 0;
		}

		template<typename T>
		static T find_primitive_root(const T& p, const T& start = 2)
		{
			auto factors = distinct_prime_factors(p - 1);
			return find_primitive_root(p, factors, start);
		}

		template<typename T = int64_t, typename U = int64_t>
		static T mod(const T& v, const U& m = m1e9n7)
		{
			if (v >= 0)
				return (T)(v % m);
			else
				return (T)((v % m + m) % m);
		}

		template<typename T, typename U>
		static T smod(const T& v, const U& m = m1e9n7)
		{
			return v % m;
		}

		template<size_t A, size_t B, size_t C>
		static void matrix_multiply(int64_t a[A][B], int64_t b[B][C], int64_t c[A][C], int64_t m = m1e9n7)
		{
			for (size_t k0 = 0; k0 < A; ++k0)
				for (size_t k2 = 0; k2 < C; ++k2)
				{
					int64_t sum = 0;
					for (size_t k1 = 0; k1 < B; ++k1)
						sum = smod(sum + a[k0][k1] * b[k1][k2], m);
					c[k0][k2] = sum;
				}
		}

		template<size_t A, size_t B, size_t C>
		static void matrix_multiply_inplace(int64_t a[A][B], int64_t b[B][C], int64_t c[A][C], int64_t m = m1e9n7)
		{
			int64_t c0[A][C];
			matrix_multiply<A, B, C>(a, b, c0, m);
			memcpy(c, c0, sizeof(c0));
		}

		template<size_t N, int64_t M = m1e9n7>
		static void matrix_power_mod(int64_t m[N][N], int64_t p)
		{
			if (0 == p)
			{
				for (size_t r = 0; r < N; ++r)
					for (size_t c = 0; c < N; ++c)
						m[r][c] = r == c;
				return;
			}
			if (1 == p)
				return;
			if (p & 1)
			{
				int64_t m1[N][N];
				memcpy(m1, m, sizeof(m1));
				matrix_power_mod<N>(m, p / 2);
				matrix_multiply_inplace<N, N, N>(m, m, m);
				matrix_multiply_inplace<N, N, N>(m, m1, m);
			}
			else
			{
				matrix_power_mod<N>(m, p / 2);
				matrix_multiply_inplace<N, N, N>(m, m, m);
			}
		}

		template<typename T>
		static T modular_multiplicative_inverse(const T& a, const T& m)
		{
			if (a >= m)
				return -1;

			int64_t mat[2][2] = { 1, 0, 0, 1 };
			T b = m;
			T va = a;
			do {
				auto r = va % b;
				auto q = va / b;
				va = b;
				b = r;
				int64_t mat0[2][2] = { 0, 1, 1, -q };
				matrix_multiply_inplace<2, 2, 2>(mat0, mat, mat, std::numeric_limits<int64_t>::max());
				if (1 == r)
					break;
			} while (true);
			return (T)mod(mat[1][0], m);
		}

		template<typename T>
		static T modular_multiplicative_inverse(const T& a, T b, const T& m)
		{
			b %= m;
			auto g = gcd(a, m);
			if (b / g * g != b)
				return -1;
			auto r = modular_multiplicative_inverse(a / g, m / g);
			r = (T)mod((int64_t)r * b / g, m / g);
			return r;
		}

		template<typename T>
		static T power_mod(const T& a, const T& p, const T& m = m1e9n7)
		{
			if (0 > p)
				return modular_multiplicative_inverse(power_mod(a, -p, m), m);

			if (1 == p)
				return a % m;
			if (0 == p)
				return 1;

			T r = power_mod(a, p / 2, m);
			r = (int)((int64_t)r * r % m);
			if (p & 1)
				return (int)((int64_t)r * a % m);
			else
				return r;
		}

		template<typename T>
		static std::unordered_map<T, size_t> dlog_precalc(const T& a, const T& n, T len = 0)
		{
			if (0 == len)
				len = (T)ceil(sqrt(n));
			else
				len = std::min(len, n);

			std::unordered_map<T, size_t> vmap;
			T s0 = 1;
			vmap[1] = 0;
			for (size_t k = 1; k < (size_t)len; ++k)
			{
				s0 = (T)mod((int64_t)s0 * a, n);
				vmap[s0] = k;
			}
			return vmap;
		}

		template<typename T>
		static T dlog(const T& a, const T& n, const T& e, const std::unordered_map<T, size_t>& precalc)
		{
			if (0 == a % n)
				return -1;

			T len = (T)precalc.size();
			auto ak = power_mod<int64_t>(a, -len, n);
			auto r = e;
			for (T k = 0; k < n; k += len)
			{
				auto it = precalc.find(r);
				if (precalc.end() != it)
					return mod(it->second + k, n - 1);
				r = (T)mod(r * ak, n);
			}

			return -1;
		}

		template<typename T>
		static T dlog(const T& a, const T& n, const T& e)
		{
			return dlog(a, n, e, dlog_precalc(a, n));
		}

		static std::vector<std::vector<int>> coprime_pairs(int n)
		{
			std::vector<std::vector<int>> r(n + 1);
			std::list<std::pair<int, int>> q;
			q.push_back({ 2, 1 });
			q.push_back({ 3, 1 });
			while (q.size())
			{
				auto& p = q.front();
				r[p.first].push_back(p.second);
				std::pair<int, int> p1 = { p.first * 2 - p.second, p.first };
				std::pair<int, int> p2 = { p.first * 2 + p.second, p.first };
				std::pair<int, int> p3 = { p.second * 2 + p.first, p.second };
				if (p1.first <= n)
					q.push_back(p1);
				if (p2.first <= n)
					q.push_back(p2);
				if (p3.first <= n)
					q.push_back(p3);
				q.pop_front();
			}

			return r;
		}
	};
}

namespace algorithm_lib
{
	class binomial_coefficient_t
	{
		std::vector<std::vector<int64_t>> _cache;
	public:
		binomial_coefficient_t(size_t size, int64_t moduli = 1000000007)
		{
			_cache.resize(size + 1);
			_cache[0].push_back(1);
			for (size_t k = 1; k <= size; ++k)
			{
				auto& last_row = _cache[k - 1];
				auto& row = _cache[k];
				row.resize(k + 1);
				row[0] = row[k] = 1;
				for (size_t i = 1; i < k; ++i)
					row[i] = (last_row[i - 1] + last_row[i]) % moduli;
			}
		}

		int64_t cnr(size_t n, size_t r)const { return r <= n ? _cache[n][r] : 0; }
	};
}

namespace gcd_mocktail
{
	const int moduli = 30000001;
	std::vector<int> power_l_coef(const algorithm_lib::binomial_coefficient_t& cnr, int l)
	{
		std::vector<int> r(l + 1);
		r[l] = algorithm_lib::number_theory_t::modular_multiplicative_inverse((int)cnr.cnr(l + 1, 1), moduli);

		for (int c = 2; c <= l + 1; ++c)
		{
			int64_t s = 0;
			for (int d = c; d > 1; --d)
			{
				auto delta = algorithm_lib::number_theory_t::mod((int64_t)r[l + d - c] * cnr.cnr(l + 1 + d - c, d), moduli);
				auto sign = (d & 1) ? -1 : 1;
				s = algorithm_lib::number_theory_t::mod(s + sign * delta, moduli);
			}
			r[l - c + 1] = algorithm_lib::number_theory_t::modular_multiplicative_inverse((int)cnr.cnr(l + 2 - c, 1), (int)s, moduli);
		}

		return r;
	}

	int sum(int n, const std::vector<int>& coef)
	{
		int64_t r = 0;
		int l = (int)coef.size() - 1;
		int64_t x = 1;

		for (auto cf : coef)
		{
			x = algorithm_lib::number_theory_t::mod(x * n, moduli);
			r += cf * x;
		}
		r = algorithm_lib::number_theory_t::mod(r, moduli);

		return (int)r;
	}

	int calc_f(int n, int d, std::unordered_map<int, int>& cache)
	{
		if (cache.count(n))
			return cache[n];

		if (1 == n)
		{
			cache[1] = 1;
			return 1;
		}

		int sqrt_n = (int)sqrt(n);
		int xd = algorithm_lib::number_theory_t::power_mod(n, d, moduli);
		int s0 = 0;
		for (int g = 2; g <= sqrt_n; ++g)
		{
			s0 = algorithm_lib::number_theory_t::mod(s0 + calc_f(n / g, d, cache), moduli);
		}
		int s1 = 0;
		for (int k = 1; k <= n / (sqrt_n + 1); ++k)
		{
			int64_t delta = calc_f(k, d, cache);
			auto range = n / k - n / (k + 1);
			delta = algorithm_lib::number_theory_t::mod(delta * range, moduli);
			s1 = (int)algorithm_lib::number_theory_t::mod(s1 + delta, moduli);
		}
		auto r = algorithm_lib::number_theory_t::mod(xd - s0 - s1, moduli);
		cache[n] = r;
		return r;
	}

	int calc_h(int n, int d, int l,
		const algorithm_lib::binomial_coefficient_t& cnr,
		std::unordered_map<int, int>& f_cache)
	{
		int sqrt_n = (int)sqrt(n);
		auto coef = power_l_coef(cnr, l);

		int64_t h0 = 0;
		for (int g = 1; g <= sqrt_n; ++g)
		{
			auto f = calc_f(n / g, d, f_cache);
			int64_t gl = algorithm_lib::number_theory_t::power_mod(g, l, moduli);
			h0 = algorithm_lib::number_theory_t::mod(h0 + f * gl, moduli);
		}
		int64_t h1 = 0;
		auto next_gl = sum(n, coef);

		for (int k = 1; k <= n / (sqrt_n + 1); ++k)
		{
			auto f = calc_f(k, d, f_cache);
			auto gl = next_gl;
			next_gl = sum(n / (k + 1), coef);
			int64_t range = algorithm_lib::number_theory_t::mod(gl - next_gl, moduli);
			h1 = algorithm_lib::number_theory_t::mod(h1 + f * range, moduli);
		}
		auto r = algorithm_lib::number_theory_t::mod(h0 + h1, moduli);
		return (int)r;
	}

	void solve(int n, int d, const std::vector<int>& ls,
		const algorithm_lib::binomial_coefficient_t& cnr)
	{
		std::unordered_map<int, int> f_cache;
		for (auto l : ls)
		{
			std::cout << calc_h(n, d, l, cnr, f_cache) << std::endl;
		}
	}

	void solve()
	{
		algorithm_lib::binomial_coefficient_t cnr(101, moduli);
		int t;
		std::cin >> t;
		while (t--)
		{
			int n, d, q;
			std::cin >> n >> d >> q;
			std::vector<int> ls;
			while (q--)
			{
				int l;
				std::cin >> l;
				ls.push_back(l);
			}
			solve(n, d, ls, cnr);
		}
	}
}

int main()
{
	gcd_mocktail::solve();
	return 0;
}
