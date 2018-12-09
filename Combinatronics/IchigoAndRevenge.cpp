#include <vector>
#include <iostream>
using namespace std;

uint32_t const L = 100000;
uint32_t const M = 1000000007;

void addmod(uint32_t& a, uint32_t b)
{
    if ((a += b) >= M) a -= M;
}

uint32_t submod(uint32_t a, uint32_t b)
{
    return (a < b ? M : 0) + a - b;
}

uint32_t mulmod(uint32_t a, uint32_t b)
{
    return uint32_t((uint64_t(a) * b) % M);
}

uint32_t invmod(uint32_t a)
{
    for (uint32_t p = M - 2, rv = 1;;)
    {
        if (p & 1) rv = mulmod(rv, a);
        if (p >>= 1) a = mulmod(a, a);
        else return rv;
    }
}

class solver
{
public:
    solver() : fct_(L + 1), inv_(L + 1)
    {
        uint32_t fct = inv_[0] = fct_[0] = 1;
        for (uint32_t i = 1; i <= L; ++i)
            fct_[i] = fct = mulmod(fct, i);
        fct = invmod(fct);
        for (uint32_t i = L; i; --i)
            fct = mulmod(inv_[i] = fct, i);
    }
    uint32_t operator()(uint32_t u, uint32_t v, uint32_t k, uint32_t p) const
    {
        auto delta = binom(u, v), result = mulmod(
            invmod(p), submod(binom(u * p, v * p), delta));
        if (!k) addmod(result, delta); return result;
    }
private:
    uint32_t binom(uint32_t n, uint32_t k) const
    {
        return mulmod(fct_[n], mulmod(inv_[k], inv_[n - k]));
    }
private:
    vector<uint32_t> fct_, inv_;
};

uint32_t pick()
{
    uint32_t rv = 0; cin >> rv; return rv;
}

int main()
{
    solver answer;
    for (auto T = pick(); T; --T)
    {
        auto U = pick(); auto V = pick();
        auto K = pick(); auto P = pick();
        cout << answer(U, V, K, P) << endl;
    }
    return 0;
}
