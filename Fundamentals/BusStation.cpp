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

using namespace std;

#define rep(i,a,b) for(int i = a; i < b; i++)
#define S(x) scanf("%d",&x)
#define P(x) printf("%d\n",x)

typedef long long int LL;
int A[111111];
int n;

bool check(int x) {

	int sm = 0;
	rep(i,0,n) {
		sm += A[i];

		if(sm > x) {
			return false;
		}
		if(sm == x) {
			sm = 0;
		}
	}

	if(sm) return false;
	return true;

}

int main() {
	S(n);

	int sm = 0;

	rep(i,0,n) {
		S(A[i]);
		sm += A[i];
	}

	vector<int > a,b;

	for(int i = 1; i*i <= sm; i++) if(sm%i == 0) {

		if(check(i)) a.push_back(i);
		if(i*i != sm && check(sm/i)) b.push_back(sm/i);

	}

	rep(i,0,a.size()) printf("%d ",a[i]);
	rep(i,0,b.size()) printf("%d ",b[(int)b.size()-1-i]);

	return 0;
}
