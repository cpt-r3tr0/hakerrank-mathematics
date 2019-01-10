#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

#define FOR(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
#define SZ(c) ((int)(c).size())

typedef long long LL;

int main(void) {
    int T;
    scanf("%d", &T);
    assert(1 <= T && T <= 100);
    while(T--) {
        LL n;
        cin >> n;
        assert(1 <= n && n <= 1e12);
        vector<int> B;
        B.push_back(0);
        int m=0;
        while(n>0) {
            ++m;
            //try 'a'
            LL p = m-B.back();
            if(SZ(B)>=2) p += (m-B.back() <= B.back()-B[SZ(B)-2]-1);
            if(SZ(B)>=3) p += (m-B.back() <= B[SZ(B)-2]-B[SZ(B)-3]-1);
            if(p <= n) { n -= p; continue; }
            //try 'b'
            p = 1;
            if(SZ(B)>=2) p += 1;
            if(p <= n) { n -= p; B.push_back(m); continue; }
            //try 'c' (assert n == 1)
            p = 1;
            if(p <= n) { n -= p; continue; }
        }
        printf("%d\n", (int)m);
    }
    return 0;
}
