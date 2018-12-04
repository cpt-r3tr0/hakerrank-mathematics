#include <iostream>

uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m)
{
    return uint64_t(((unsigned __int128)a * b) % m);
}

uint64_t powmod(uint64_t a, uint64_t b, uint64_t m)
{
    for (uint64_t rv = 1;;)
    {
        if (b & 1) rv = mulmod(rv, a, m);
        if (b >>= 1) a = mulmod(a, a, m);
        else return rv;
    }
}

template <class F> void factor(uint64_t n, F f)
{
    if (!(n % 2)) for (f(2); !((n /= 2) % 2););
    if (!(n % 3)) for (f(3); !((n /= 3) % 3););
    for (uint64_t p = 5, k = 2; p * p <= n; p += k, k ^= 6)
        if (!(n % p)) for (f(p); !((n /= p) % p););
    if (n > 1) f(n);
}

uint64_t answer(uint64_t n)
{
    uint32_t x, result = 0;
    for (x = 0; !(n % 2); ++x, n /= 2);
    if (x > 2) result = x - 2;
    for (x = 0; !(n % 5); ++x, n /= 5);
    if (result < x) result = x;
    uint64_t order = (n *= 9);
    factor(order,
        [&](uint64_t p)->void
        {
            order -= order / p;
        });
    factor(order,
        [&](uint64_t p)->void
        {
            while (!((order /= p) % p));
            for (uint64_t g = powmod(10, order, n); g != 1;
                g = powmod(g, p, n), order *= p);
        });
    return order * 2 + result;
}

int main()
{
    uint32_t T = 0;
    for (std::cin >> T; T; --T)
    {
        uint64_t N; std::cin >> N;
        std::cout << answer(N) << std::endl;
    }
    return 0;
}
