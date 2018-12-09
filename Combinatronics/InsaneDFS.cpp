#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

typedef long long LL;
typedef vector<int> VI;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)

const LL MOD = 1000000007;
const int MAX = 1000000;
LL inv[MAX+1], fact[MAX+1], fact_inv[MAX+1];

void init() {
    inv[1] = 1;
    for (int i=2; i<=MAX; i++) inv[i] = inv[MOD%i] * (MOD-MOD/i) % MOD;

    fact[0] = fact_inv[0] = 1;
    for (int i=1; i<=MAX; i++) {
	fact[i] = fact[i-1] * i % MOD;
	fact_inv[i] = fact_inv[i-1] * inv[i] % MOD;
    }
}
LL nCk(int n, int k) {
    if (n < 0 || k < 0 || n < k) return 0;
    return fact[n] * fact_inv[k] % MOD * fact_inv[n-k] % MOD;
}

int N, A[100011];
char buf[99];

int main() {
    init();
    scanf("%d", &N);
    REP (i, N) {
	scanf("%s", buf);
	if (buf[0] == '?') A[i] = -1;
	else sscanf(buf, "%d", A+i);
    }

    int root = 0;
    for (int i=1; i<N; i++) if (A[i] == 0) root++;
    if (root || A[0] > 0 || (N>=2 && A[1] > 1)) {
	puts("0");
	return 0;
    }

    A[1] = 1;
    A[N] = 1;

    LL ans = 1;
    for (int p=1, q=0; p<N; p=q) {
	for (q=p+1; A[q] == -1; q++);
	int Y = q-p-1, X = A[p] - A[q] + 1 + Y;
	int Y2 = X - (A[p]+1), X2 = Y + (A[p]+1);

	if (X < 0) ans = 0;
	LL go = nCk(X+Y, X);
	LL bad = nCk(X2+Y2, X2);
	ans *= go - bad;
	ans %= MOD;
    }

    ans = (ans + MOD) % MOD;
    printf("%d\n", (int)ans);

    return 0;
}
