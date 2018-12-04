#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int mul(ll x,ll y,int p) {
    return x * y % p;
}

int powermod(ll x,ll y,int p) {  //x ^ y mod p
    if (x == 0) {
        return 0;
    }
    if (y == 0) {
        return 1;
    }
    if (y & 1) {
        return mul(powermod(x, y ^ 1, p), x, p);
    }
    x = powermod(x, y >> 1, p);
    return mul(x, x, p);
}

pair<int,int> help(int a,int b,ll x,int p) { // (a + b  * sqrt(5)) ^ n mod p
    if (x == 0) {
        return make_pair(1, 0);
    }
    pair<int,int> A, B;
    if (x & 1) {
        A = help(a, b, x - 1, p);
        B = make_pair(a, b);
    }
    else {
        A = B = help(a, b, x >> 1, p);
    }
    a = mul(A.first, B.first, p) + mul(5, mul(A.second,B.second, p), p);
    if (a >= p) {
        a -= p;
    }
    b = mul(A.first, B.second, p) + mul(A.second , B.first, p);
    if (b >= p) {
        b -= p;
    }
    return make_pair(a, b);
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
int z;
    for (scanf("%d",&z);z;--z) {
        int a,b,p;
        ll x;
        scanf("%d%d%d",&a,&b,&p);
        if (mul(a,a,p) == mul(mul(b,b,p),5,p)) {
            puts("-1");
            continue;
        }
        else if (powermod(5, p >> 1, p) == 1) {
            x = p - 1;
            x *= (p - 1);


        }
        else {
            x = p;
            x *= x;
            --x;
        }
        ll answer = -1;
        pair<int,int> temp;
        for (ll i = 1; i * i <= x; ++i) {
            if (x % i) {
                continue;
            }
            if ((answer < 0) || (i < answer)) {
                temp = help(a,b,i,p);
                if ((temp.first == 1) && (temp.second == 0)) {
                    answer = i;
                }
            }
            if ((answer < 0) || (x / i < answer)) {
                temp = help(a,b,x / i,p);
                if ((temp.first == 1) && (temp.second == 0)) {
                    answer = x / i;
                }

            }
        }
        printf("%lld\n",answer);

    }
    return 0;
}
