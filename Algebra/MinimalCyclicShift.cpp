#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
const int Q = 998244353;
const int M = 262144 << 1;
int n , K;
int a[M] , b[M] , X[M] , A[M] , B[M];

int I[N] , m , s[N] , t[N] , f[N];

int inverse(int x) {
    return x == 1 ? 1 : (LL)(Q - Q / x) * inverse(Q % x) % Q;
}
int power(int A , int B) {
    int res = 1;
    for ( ; B ; A = (LL)A * A % Q , B >>= 1) {
        if (B & 1) {
            res = (LL)res * A % Q;
        }
    }
    return res;
}
void FFT(int P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m << 1;
        int unit_p0 = power(3 , Q - 1 >> d + 1);
        if (oper == -1)
            unit_p0 = inverse(unit_p0);
        for (int i = 0; i < n; i += m2) {
            int unit = 1;
            for (int j = 0; j < m; j++) {
                int &P1 = P[i + j + m], &P2 = P[i + j];
                int t = (LL)unit * P1 % Q;
                P1 = P2 - t + Q;
                if (P1 >= Q) P1 -= Q;
                P2 = P2 + t;
                if (P2 >= Q) P2 -= Q;
                unit = (LL)unit * unit_p0 % Q;
            }
        }
    }
}

int main() {
    scanf("%d%d" , &n , &K);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d" , &a[i]);
        a[i + n] = a[i];
    }
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d" , &b[i]);
        b[i + n] = b[i];
    }
    ++ K;
    if (K >= n) {
        puts("0");
        return 0;
    }
    I[0] = I[1] = 1;
    for (int i = 2 ; i <= n + n ; ++ i) {
        I[i] = (LL)(Q - Q / i) * I[Q % i] % Q;
    }
    for (int i = 2 ; i <= n + n ; ++ i) {
        I[i] = (LL)I[i] * I[i - 1] % Q;
    }
    int len = 1;
    while (len < n + n + K + 5) {
        len <<= 1;
    }
    int inv = inverse(len);
    for (int i = 0 ; i <= K ; ++ i) {
        X[i] = (LL)I[i] * I[K - i] % Q;
        if (i & 1) {
            X[i] = (Q - X[i]) % Q;
        }
    }
    FFT(X , len , 1);
    for (int i = 0 ; i < n + n ; ++ i) {
        A[i] = a[i];
        B[i] = b[i];
    }
    FFT(A , len , 1);
    FFT(B , len , 1);
    for (int i = 0 ; i < len ; ++ i) {
        A[i] = (LL)A[i] * X[i] % Q;
        B[i] = (LL)B[i] * X[i] % Q;
    }
    FFT(A , len , -1);
    FFT(B , len , -1);
    int m = n - K;
    for (int i = 0 ; i < n - K ; ++ i) {
        s[i] = A[i + K];
    }
    for (int i = 0 ; i < n ; ++ i) {
        t[i] = t[i + n] = B[i + K];
    }
    f[0] = f[1] = 0;
    for (int i = 1 ; i < m ; ++ i) {
        int j = f[i];
        while (j && s[i] != s[j])
            j = f[j];
        f[i + 1] = s[i] == s[j] ? j + 1 : 0;
    }
    for (int i = 0 , j = 0 ; i < n + n ; ++ i) {
        while (j && t[i] != s[j])
            j = f[j];
        j += (t[i] == s[j]);
        if (j == m) {
            printf("%d\n", i - m + 1);
            return 0;
        }
    }
    puts("-1");
}
