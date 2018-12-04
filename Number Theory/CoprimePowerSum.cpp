#include <stdio.h>
#include <cstring>
#include <stdlib.h>

#define LIM 100001
#define MOD 1000000007

int n, S[12][12];
long long ar[52], power[52], dp[52][LIM];

int compare(const void* a, const void* b){
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x == y) return 0;
    else return ((x < y) ? -1 : 1);
}

long long faulhaber(long long n, int k){
    if (!k) return (n % MOD);

    int i, j, l;
    long long z, res = 0;
    for (j = 0; j <= k; j++){
        for (l = j + 1, i = 0, z = 1; (i - 1) < j; i++){
            if ((l > 1) && !((n - i + 1) % l)){
                z = (z * (((n - i + 1) / l) % MOD) ) % MOD;
                l = 1;
            }
            else z = (z * ((n - i + 1) % MOD) ) % MOD;
        }
        res = (res + (z * S[k][j])) % MOD;
    }
    return res;
}

long long count(int n, long long m, int k){
    if (n == 0) return faulhaber(m, k);
    if (m < LIM && dp[n][m] != -1) return dp[n][m];
    int res = (count(n - 1, m, k) - ((count(n - 1, m / ar[n], k) * power[n]) % MOD) + MOD) % MOD;
    if (m < LIM) dp[n][m] = res;
    return res;
}

long long solve(long long m, int k){
    int i, j;
    memset(dp, -1, sizeof(dp));
    qsort(ar + 1, n, sizeof(long long), compare);

    for (i = 1; i <= n; i++){
        long long y = ar[i] % MOD, x = 1;
        for (j = 0; j < k; j++) x = (x * y) % MOD;
        power[i] = x;
    }
    return count(n, m, k);
}

void Generate(){
    int i, j;
    for (i = 1, S[0][0] = 1; i < 12; i++){
        for (j = 1, S[i][0] = 0; j <= i; j++){
            S[i][j] = ( ((long long)S[i - 1][j] * j) + S[i - 1][j - 1]) % MOD;
        }
    }
}

int main(){
    Generate();
    int t, i, j, k, l;
    long long m, x, y, z, res;

    scanf("%d", &t);
    while (t--){
        scanf("%d %d %lld", &n, &k, &m);
        for (i = 1; i <= n; i++) scanf("%lld", &ar[i]);
        printf("%lld\n", solve(m, k));
    }
    return 0;
}
