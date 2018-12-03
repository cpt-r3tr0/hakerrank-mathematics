#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


template<typename R, typename T>
struct castT {
    static R of(const T& x) {
        return R(x);
    }
    static R of(const R& ref, const T& x) {
        return of(x);
    }
};
template<typename T>
struct nopCastT {
    static const T& of(const T& x) {
        return x;
    }
    static const T& of(const T& ref, const T& x) {
        return x;
    }
};
template<typename R, typename T>
R castOf(const T& x) { return castT<R, T>::of(x); }
template<typename R, typename T>
R castOf(const R& ref, const T& x) { return castT<R, T>::of(ref, x); }

template<typename T>
struct identityT {
    static T of(const T& x) {
        return T(1);
    }
};
template<typename T>
T identityOf(const T& x) { return identityT<T>::of(x); }

template<typename T>
struct zeroT {
    static T of(const T& x) {
        return T(0);
    }
};
template<typename T>
T zeroOf(const T& x) { return zeroT<T>::of(x); }

template<typename T, typename I>
T powT(T x, I y) {
    T e1 = identityOf(x);
    T r = e1;
    for (; y > 0; y /= 2) {
        if (y % 2 != 0) r *= x;
        x *= x;
    }
    return r;
}

template<typename T>
T gcd(T a, T b) {
    T e0 = zeroOf(a);
    while (a != e0) { T r = b % a; b = a; a = r; }
    return b;
}

template<typename T>
T gcd_ex(const T& a, const T& b, T *x = 0, T *y = 0) {
    T e0 = zeroOf(a), e1 = identityOf(a);
    T r, q, g = a, h = b;
    T xo = e0, xn = e1;
    T yo = e1, yn = e0;
    while (h != e0) {
        q = g / h;
        r = g  - q * h;  g  = h;  h  = r;
        r = xn - q * xo; xn = xo; xo = r;
        r = yn - q * yo; yn = yo; yo = r;
//        T gn = a * xn + b * yn;
    }
    if (x) *x = xn;
    if (y) *y = yn;
//    if (y) *y = (b != e0) ? (g - a * xn) / b : e0;
    return g;
}





// modulo normalization
template<typename T>
void modulo_normalize(T* v, const T& M) { *v %= M; }
// integral type specializations
template<typename I>
void modulo_normalize_int(I* v, I M) { *v %= M; if (*v < 0) *v += M; }
inline void modulo_normalize(int64_t* v, int64_t M) { modulo_normalize_int(v, M); }
inline void modulo_normalize(int32_t* v, int32_t M) { modulo_normalize_int(v, M); }

// modulo addition
template<typename T>
T modulo_add(const T& x, const T& y, const T& M) { return (x + y) % M; }

// modulo subtraction
template<typename T>
T modulo_sub(const T& x, const T& y, const T& M) { return (x - y) % M; }
// integral type specializations, input is assumed to be normalized
template<typename I>
I modulo_sub_int(I x, I y, I M) { return (x + (M - y)) % M; }
inline int64_t modulo_sub(int64_t x, int64_t y, int64_t M) { return modulo_sub_int(x, y, M); }
inline int32_t modulo_sub(int32_t x, int32_t y, int32_t M) { return modulo_sub_int(x, y, M); }

// modulo multiplication
template<typename T>
T modulo_mul(const T& x, const T& y, const T& M) { return (x * y) % M; }
// integral type specializations, input is assumed to be normalized
template<typename I>
I modulo_mul_int_long(I x, I y, I M) {
    I r = 0;
    for (; y > 0; y >>= 1) {
        if (y & 1) r += x, r %= M;
        x += x, x %= M;
    }
    return r;
}
inline int64_t modulo_mul(int64_t x, int64_t y, int64_t M) {
    return ((x | y) >> 31 == 0) ? (x * y) % M : modulo_mul_int_long(x, y, M);
}
inline int32_t modulo_mul(int32_t x, int32_t y, int32_t M) {
    return (int64_t(x) * y) % M;
}

// modulo inversion
template<typename T> T modulo_inv(const T& v, const T& M) {
    T vi; T g = gcd_ex(v, M, &vi);
    if (g != 1) vi /= g;
    return vi;
}
// integral type specializations, input is assumed to be normalized
template<typename I> I modulo_inv_int(I v, I M) {
    I vi; gcd_ex(v, M, &vi);
    modulo_normalize_int(&vi, M);
    return vi;
}
inline int64_t modulo_inv(int64_t v, int64_t M) { return modulo_inv_int(v, M); }
inline int32_t modulo_inv(int32_t v, int32_t M) { return modulo_inv_int(v, M); }

// modulo division
template<typename T> T modulo_div(const T& x, const T& y, const T& M) {
    return modulo_mul(x, modulo_inv(y, M), M);
}
// integral type specializations, input is assumed to be normalized
template<typename I>
I modulo_div_int(I x, I y, I M) {
    if (y != 0 && x % y == 0) return x / y; // fast path if y divides x
    I yi; I g = gcd_ex(y, M, &yi);
    if (g != 1) { // uh oh, y and M are not coprime, try common gcd
        g = gcd(x, g);
        x /= g; y /= g;
        gcd_ex(y, I(M / g), &yi); // == k
        // if (k != 1), there is no result, or more precisely,
        // the result will be `k` times bigger than it should.
    }
    modulo_normalize_int(&yi, I(M / g));
    return modulo_mul(x, yi, M);
}
inline int64_t modulo_div(int64_t x, int64_t y, int64_t M) { return modulo_div_int(x, y, M); }
inline int32_t modulo_div(int32_t x, int32_t y, int32_t M) { return modulo_div_int(x, y, M); }


// modulo storage type

namespace modulo_storage {
    enum type { INSTANCE, STATIC, CONSTANT };
}

template<typename T, int ID, int STORAGE_TYPE>
struct modulo_members;

template<typename T, int ID>
struct modulo_members<T, ID, modulo_storage::INSTANCE> {
    T _M;
    modulo_members(const T& _M = 0) : _M(_M) {}
    const T& M() const { return _M; }
    T& M() { return _M; }
};

template<typename T, int ID>
struct modulo_members<T, ID, modulo_storage::STATIC> {
    static T _M;
    modulo_members(const T& _M = 0) {}
    static T& M() { return _M; }
};

template<typename T, int ID>
struct modulo_members<T, ID, modulo_storage::CONSTANT> {
    modulo_members(const T& _M = 0) {}
    static T M() { return T(ID); }
};

template<typename T, int ID, int STORAGE_TYPE = modulo_storage::STATIC>
class modulo : public modulo_members<T, ID, STORAGE_TYPE> {
    typedef modulo_members<T, ID, STORAGE_TYPE> my_modulo_members;
public:
    T v;

    // construct from int, but only if T is not integral to avoid constructor clashing
    template <typename I = T, typename = std::enable_if_t<!std::is_integral<I>::value>>
    modulo(int v) : my_modulo_members(1), v(v) { if (STORAGE_TYPE != modulo_storage::INSTANCE) normalize(); }
    modulo(const T& v = 0) : my_modulo_members(1), v(v) { if (STORAGE_TYPE != modulo_storage::INSTANCE) normalize(); }
    modulo(const T& v, const T& M) : my_modulo_members(M), v(v) { normalize(); }
    modulo(const modulo& rhs) : my_modulo_members(rhs.M()), v(rhs.v) {}

    void normalize() { modulo_normalize(&v, this->M()); }

    bool operator == (const modulo &rhs) const { return (v == rhs.v); }
    bool operator != (const modulo &rhs) const { return (v != rhs.v); }
    bool operator <  (const modulo &rhs) const { return (v <  rhs.v); }
    bool operator >  (const modulo &rhs) const { return (v >  rhs.v); }
    bool operator <= (const modulo &rhs) const { return (v <= rhs.v); }
    bool operator >= (const modulo &rhs) const { return (v >= rhs.v); }

    modulo  operator +  (const modulo &rhs) const { modulo t(*this); t += rhs; return t; }
    modulo  operator -  (const modulo &rhs) const { modulo t(*this); t -= rhs; return t; }
    modulo  operator -  ()                  const { modulo t(-v, this->M());   return t; }
    modulo  operator *  (const modulo &rhs) const { modulo t(*this); t *= rhs; return t; }
    modulo  operator /  (const modulo &rhs) const { modulo t(*this); t /= rhs; return t; }
    modulo  operator %  (const modulo &rhs) const { modulo t(*this); t %= rhs; return t; }

    modulo& operator += (const modulo &rhs) { v = modulo_add(v, rhs.v, this->M()); return *this; }
    modulo& operator -= (const modulo &rhs) { v = modulo_sub(v, rhs.v, this->M()); return *this; }
    modulo& operator *= (const modulo &rhs) { v = modulo_mul(v, rhs.v, this->M()); return *this; }
    modulo& operator /= (const modulo &rhs) { v = modulo_div(v, rhs.v, this->M()); return *this; }
    modulo& operator %= (const modulo &rhs) { v %= rhs.v;                          return *this; }

    modulo inv() const { return modulo_inv(v, this->M()); }
};

template<typename T>
using moduloX = modulo<T, 0, modulo_storage::INSTANCE>;

template<typename T, int ID>
T modulo_members<T, ID, modulo_storage::STATIC>::_M = castOf<T>(ID);

template<typename T, int ID, int STORAGE_TYPE, typename I>
struct castT<modulo<T, ID, STORAGE_TYPE>, I> {
    typedef modulo<T, ID, STORAGE_TYPE> mod;
    static mod of(const I& x) {
        return mod(castOf<T>(x % mod::M()));
    }
    static mod of(const mod& ref, const I& x) {
        return mod(castOf(ref.v, x % ref.M()), ref.M());
    }
};
template<typename T, int ID, int STORAGE_TYPE>
struct castT<modulo<T, ID, STORAGE_TYPE>, modulo<T, ID, STORAGE_TYPE>> : nopCastT<modulo<T, ID, STORAGE_TYPE>>{};

template<typename T, int ID, int STORAGE_TYPE>
struct identityT<modulo<T, ID, STORAGE_TYPE>> {
    typedef modulo<T, ID, STORAGE_TYPE> mod;
    static mod of(const mod& x) {
        return mod(identityOf(x.v), x.M());
    }
};

template<typename T, int ID, int STORAGE_TYPE>
struct zeroT<modulo<T, ID, STORAGE_TYPE>> {
    typedef modulo<T, ID, STORAGE_TYPE> mod;
    static mod of(const mod& x) {
        return mod(zeroOf(x.v), x.M());
    }
};

template<typename T>
T modT(T v, const T& m) { modulo_normalize(&v, m); return v; }

template<typename T, typename I>
T modulo_power(const T& x, const I& y, const T& M) {
    return powT(moduloX<T>(x, M), y).v;
}





template<typename It, typename T = typename std::iterator_traits<It>::value_type>
void inv_factorials(It begin, It end, T id = T(1)) {
    T fact = id, i = id;
    for (It it = begin; it != end; ++it) {
        fact *= i; i += id;
    }
    T ifact = id / fact;
    for (It it = end; it != begin; ) {
        i -= id; ifact *= i; *--it = ifact;
    }
}
template<typename T>
std::vector<T> inv_factorials(int n, T id = T(1)) {
    std::vector<T> v(n, id);
    inv_factorials(v.begin(), v.end(), id);
    return v;
}
template<typename It, typename T = typename std::iterator_traits<It>::value_type>
void inverses(It begin, It end, T id = T(1)) {
    inv_factorials(begin, end, id);
    T fact = id, i = id;
    *begin = zeroT<T>::of(id);
    for (It it = ++begin; it != end; ++it) {
        *it *= fact; fact *= i; i += id;
    }
}
template<typename T>
std::vector<T> inverses(int n, T id = T(1)) {
    std::vector<T> v(n, id);
    inverses(v.begin(), v.end(), id);
    return v;
}

typedef modulo<int, 1000000007, modulo_storage::CONSTANT> mod;

int main() {
    auto inv = inverses(5000009, mod(1));
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int64_t n, m; cin >> n >> m;
        if (n > m) swap(n, m); // now n <= m
        mod nn = n % mod::M(), mm = m % mod::M();
        mod r = 0, bn = 1, bm = 1, w2 = 1;
        for (int i = 0; i <= n; i++) {
            r += bn * bm * w2;
            bn *= (nn - i) * inv[i + 1];
            bm *= (mm - i) * inv[i + 1];
            w2 *= 2;
        }
        cout << r.v << endl;
    }
    return 0;
}
