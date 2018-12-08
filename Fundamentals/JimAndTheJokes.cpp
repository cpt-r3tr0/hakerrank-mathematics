#include <cstdio>
#include <cmath>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

#define rep(i,a,b) for(int i = a; i < b; i++)
#define S(x) scanf("%d",&x)
#define P(x) printf("%d\n",x)

typedef long long int LL;
int X[1000];

int dec(int base, int num) {

	int res = 0;
	vector<int > v;
	while(num) {
		int r = num % 10;
		if(r >= base) return 0;
		v.push_back(r);
		num /= 10;
	}
	reverse(v.begin(), v.end());

	rep(i,0,v.size()) {
		res = res * base + v[i];
	}
	return res;

}

int main() {
	int n;
	S(n);
	rep(i,0,n) {
		int m,d;
		scanf("%d%d",&m,&d);
		if(m == 10) X[d]++;
		else X[dec(m,d)]++;
	}

	LL ans = 0;
	rep(i,1,1000) {
		ans += X[i] * 1LL * (X[i] - 1) / 2;
	}
	printf("%lld\n",ans);
}
