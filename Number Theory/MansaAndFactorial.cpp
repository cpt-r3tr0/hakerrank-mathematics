#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long ll;

ll f(ll x) {
    ll sum = 0;
    while(x) {
        x /= 5;
        sum += x;
    }
    return sum;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++test) {
        ll n;
        cin >> n;
        ll l = 1, r = 100*n;
        while (r - l > 1) {
            ll x = (l+r) / 2;
            if (f(x) < n) l = x;
            else r = x;
        }
        cout << r << endl;
    }
    return 0;
}
