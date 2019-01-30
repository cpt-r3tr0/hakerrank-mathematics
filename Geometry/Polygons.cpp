#include <vector>
#include <iostream>
using namespace std;

uint32_t const p = 1000003;

uint32_t pick()
{
    uint32_t x; cin >> x; return x;
}

uint32_t addmod(uint32_t a, uint32_t b)
{
    if ((a += b) >= p) a -= p; return a;
}

uint32_t submod(uint32_t a, uint32_t b)
{
    if (a < b) a += p; return a - b;
}

uint32_t mulmod(uint32_t a, uint32_t b)
{
    return (uint64_t(a) * b) % p;
}

uint32_t invmod(uint32_t a)
{
    for (uint32_t rv = 1, k = p - 2;;)
    {
        if (k & 1) rv = mulmod(rv, a);
        if (k >>= 1) a = mulmod(a, a);
        else return rv;
    }
}

class binomials
{
public:
    binomials() : fct_(p), inv_(p)
    {
        uint32_t value = 0, factor = 1;
        for (inv_[0] = fct_[0] = 1; ++value < p;)
            fct_[value] = factor = mulmod(factor, value);
        for (factor = invmod(factor); --value;)
            factor = mulmod(inv_[value] = factor, value);
    }
    uint32_t operator()(uint32_t n, uint32_t k) const
    {
        return mulmod(get(n / p, k / p), get(n % p, k % p));
    }
private:
    uint32_t get(uint32_t n, uint32_t k) const
    {
        return n < k ? 0u : mulmod(fct_[n],
            mulmod(inv_[k], inv_[n - k]));
    }
    vector<uint32_t> fct_, inv_;
} const binom;

uint32_t answer(uint32_t n, uint32_t k)
{
    if (n < k + 3) return 0;
    auto result = binom(n + k - 1, k);
    if (auto u = (k + 1) % p)
    {
        result = mulmod(result, mulmod(
            binom(n - 3, k), invmod(u)));
    }
    else if (auto u = (n - 2) % p)
    {
        result = mulmod(result, mulmod(
            binom(n - 2, k + 1), invmod(u)));
    }
    else result = 0;
    return result;
}

int main()
{
    for (auto T = pick(); T; --T)
    {
        auto N = pick(), K = pick();
        cout << answer(N, K) << endl;
    }
    return 0;
}
