#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long s64;

const int MaxD = 200000;

const int MaxTN = 524288;
const int FFT_P = 1005060097;
const int FFT_G = 5;

inline int modpow(int a, s64 n)
{
    int t = a;
    int res = 1;
    for (s64 i = n; i > 0; i >>= 1)
    {
        if (i & 1)
            res = (s64)res * t % FFT_P;
        t = (s64)t * t % FFT_P;
    }
    return res;
}

int fftG[MaxTN];

void fft(int n, int step, int *a, int *out)
{
    if (n == 1)
    {
        out[0] = a[0];
        return;
    }

    int m = n >> 1;
    fft(m, step + 1, a, out);
    fft(m, step + 1, a + (1 << step), out + m);
    for (int i = 0; i < m; i++)
    {
        int e = out[i], o = (s64)out[i + m] * fftG[i << step] % FFT_P;
        out[i] = (e + o) % FFT_P;
        out[i + m] = (e + FFT_P - o) % FFT_P;
    }
}

void polymul(int n, int *a, int *b, int *c)
{
    int g = modpow(FFT_G, (FFT_P - 1) / n);
    fftG[0] = 1;
    for (int i = 1; i < n; i++)
        fftG[i] = (s64)fftG[i - 1] * g % FFT_P;

    static int fa[MaxTN];
    static int fb[MaxTN];

    fft(n, 0, a, fa);
    fft(n, 0, b, fb);

    reverse(fftG + 1, fftG + n);

    for (int i = 0; i < n; i++)
        fa[i] = (s64)fa[i] * fb[i] % FFT_P;

    fft(n, 0, fa, c);

    int revN = modpow(n, FFT_P - 2);
    for (int i = 0; i < n; i++)
        c[i] = (s64)c[i] * revN % FFT_P;

    /*
    fill(c, c + n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[(i + j) % n] = (c[(i + j) % n] + (s64)a[i] * b[j]) % FFT_P;*/
}

int calc(int n, int d)
{
    static int fact[MaxD + 1];
    fact[0] = 1;
    for (int x = 1; x <= d; x++)
        fact[x] = (s64)fact[x - 1] * x % FFT_P;
    static int rfact[MaxD + 1];
    rfact[1] = 1;
    for (int x = 2; x <= d; x++)
        rfact[x] = (FFT_P - (s64)(FFT_P / x) * rfact[FFT_P % x] % FFT_P) % FFT_P;
    rfact[0] = 1;
    for (int x = 1; x <= d; x++)
        rfact[x] = (s64)rfact[x] * rfact[x - 1] % FFT_P;

    static int a[MaxTN];
    static int b[MaxTN];

    int tn = 1;
    while (tn < (d + 1) * 2)
        tn <<= 1;

    fill(a, a + tn, 0);
    fill(b, b + tn, 0);

    for (int i = 0; i <= d; i++)
        a[i] = (s64)rfact[i] * modpow(i, d) % FFT_P;
    for (int i = 0; i <= d; i++)
        b[i] = (s64)rfact[i] * modpow(FFT_P - 1, i) % FFT_P;

    static int strl2[MaxTN];
    polymul(tn, a, b, strl2);


    int res = 0;
    for (int k = 0, n_k = 1; k <= min(d, n); n_k = (s64)n_k * (n - k) % FFT_P, k++)
    {
        int cur = (s64)strl2[k] * n_k % FFT_P * modpow(2, n - k) % FFT_P;
        res = (res + cur) % FFT_P;
    }
    return res;
}

int main()
{
    int nT;
    cin >> nT;
    while (nT--)
    {
        int n, d;
        scanf("%d %d", &n, &d);

        n--;
        int res = (s64)(n + 1) * modpow(2, (s64)n * (n - 1) / 2) % FFT_P;
        res = (s64)res * calc(n, d) % FFT_P;
        printf("%d\n", res);
    }

    return 0;
}
