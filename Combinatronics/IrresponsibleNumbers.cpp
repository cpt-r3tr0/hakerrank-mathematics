#include "bits/stdc++.h"
using namespace std;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
static const int INF = 0x3f3f3f3f; static const long long INFL = 0x3f3f3f3f3f3f3f3fLL;
typedef vector<int> vi; typedef pair<int, int> pii; typedef vector<pair<int, int> > vpii; typedef long long ll;
template<typename T, typename U> static void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> static void amax(T &x, U y) { if(x < y) x = y; }

template<int MOD>
struct ModInt {
	static const int Mod = MOD;
	unsigned x;
	ModInt() : x(0) {}
	ModInt(signed sig) { int sigt = sig % MOD; if(sigt < 0) sigt += MOD; x = sigt; }
	ModInt(signed long long sig) { int sigt = sig % MOD; if(sigt < 0) sigt += MOD; x = sigt; }
	int get() const { return (int)x; }

	ModInt &operator+=(ModInt that) { if((x += that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator-=(ModInt that) { if((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }

	ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
	ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
	ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
};
typedef ModInt<1000000007> mint;

struct Matrix {
	typedef mint Num;
	static const int MaxN = 4;
	int hei, wid;
	Num v[MaxN][MaxN];
	Matrix() {}
	Matrix(int n, int m) : hei(n), wid(m) {
		memset(v, 0, sizeof(m));
	}
	inline int height() const { return hei; }
	inline int width() const { return wid; }
	inline Num& at(int i, int j) { return v[i][j]; }
	inline const Num& at(int i, int j) const { return v[i][j]; }
	static Matrix identity(int n) {
		Matrix A(n, n);
		rep(i, n) A.at(i, i) = 1;
		return A;
	}
	inline static Matrix identity(const Matrix& A) { return identity(A.height()); }
	Matrix& operator*=(const Matrix& B) {
		int n = height(), m = B.width(), p = B.height();
		assert(p == width());
		const unsigned(*b)[MaxN] = reinterpret_cast<const unsigned(*)[MaxN]>(B.v);
		Num w[MaxN][MaxN];
		unsigned long long pp = (1ULL << 32) % mint::Mod;
		rep(i, n) {
			const unsigned *ai = reinterpret_cast<const unsigned*>(v[i]);
			rep(j, m) {
				unsigned x0 = 0; unsigned long long x1 = 0;
				rep(k, p) {
					unsigned long long y = (unsigned long long)ai[k] * b[k][j];
					unsigned long long t = x0 + y;
					x1 += t >> 32;
					x0 = t & 0xffffffff;
				}
				w[i][j].x = (x0 + x1 % mint::Mod * pp) % mint::Mod;
			}
		}
		memcpy(v, w, sizeof(v));
		return *this;
	}
};
Matrix operator^(const Matrix& t, ll k) {
	Matrix A = t, B = Matrix::identity(t);
	while(k) {
		if(k & 1) B *= A;
		A *= A;
		k >>= 1;
	}
	return B;
}

mint geometricSum(mint a, long long k) {
	mint smul = 1, mul = a, ret;
	while(k > 0) {
		if(k & 1)
			ret = ret * mul + smul;
		smul *= mul + 1;
		mul *= mul;
		k >>= 1;
	}
	return ret;
}

int main() {
	char x[1000002];
	long long n;
	while(~scanf("%s%lld", x, &n)) {
		int len = (int)strlen(x);
		Matrix matrices[10];
		rep(e, 10) {
			Matrix A(4, 4);
			rep(le, 2) rep(inc, 2) {
				int s = le * 2 + inc * 1;
				rep(d, 10) {
					int nle = d == e ? le : d < e ? 1 : 0;
					int ninc = d + inc >= 10 ? 1 : 0;
					int sum = d + ((d + inc) % 10) + 0;
					int ncarry = sum >= 10 ? 1 : 0;
					if(ncarry == 0) {
						int ns = nle * 2 + ninc * 1;
						A.at(s, ns) += 1;
					}
				}
			}
			matrices[e] = A;
		}
		Matrix X = Matrix::identity(4);
		for(int i = len - 1; i >= 0; -- i)
			X *= matrices[x[i] - '0'];
		Matrix A = X ^ n;
		Matrix b(1, 4);
		b.at(0, 3) = 1;
		b *= A;
		mint xm, pow10 = 1;
		rep(i, len) {
			xm = xm * 10 + (x[i] - '0');
			pow10 *= 10;
		}
		mint ans = xm * geometricSum(pow10, n) + 1;
		rep(le, 2) rep(inc, 2) {
			int s = le * 2 + inc * 1;
			if(le == 1)
				ans -= b.at(0, s);
		}
		printf("%d\n", ans.get());
	}
	return 0;
}
