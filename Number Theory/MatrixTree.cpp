#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <bitset>
#include <numeric>
#include <ctime>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pct __builtin_popcount

#define P 1000000007
#define N 1000010
int a[N],n;
int he[N],ne[N*2],ad[N*2],q[N],f[N];

void addE(int x, int y) {
    static int t = 0;
    ++t, ne[t] = he[x], he[x] = t, ad[t] = y;
    ++t, ne[t] = he[y], he[y] = t, ad[t] = x;
}

int main () {
    scanf("%d",&n);
    for (int i = 1; i <= n; i ++) scanf("%d",a+i);
    for (int i = 1; i < n; i ++) {
        int x, y;
        scanf("%d%d",&x,&y);
        addE(x,y);
    }
    int l = 0, r = 0;
    q[r++] = 1;
    while (l < r) {
    int x = q[l++];
    for (int p = he[x]; p; p = ne[p])
        if (ad[p] != f[x]) {
            q[r++] = ad[p];
            f[ad[p]] = x;
        }
    }
    int S = 1;
    for (int i = 1; i <= n; i ++)
        S = (ll)S*((a[i]-a[f[i]]+P)%P)%P;
    cout << S << endl;
    return 0;
}
