#include <string>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <stack>
#include <deque>
#include <cmath>
#include <memory.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <utility>
using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define RFOR(i, b, a) for(int i = (b) - 1; i >= (a); --i)
#define REP(i, N) FOR(i, 0, N)
#define RREP(i, N) RFOR(i, N, 0)

#define ALL(V) V.begin(), V.end()
#define SZ(V) (int)V.size()
#define PB push_back
#define MP make_pair
#define Pi 3.14159265358979

typedef long long Int;
typedef unsigned long long UInt;
typedef vector <int> VI;
typedef pair <int, int> PII;

const Int MOD = 1000000007;

int gcd(int x, int y)
{
	while (x && y)
	{
		if (x > y)
			x%=y;
		else
			y%=x;
	}
	return x+y;
}

int CNK[3333][3333];

Int solve(int n, int m, int k, int i, int j, int pi, int pj)
{
	Int res = 0;
	int cnt = k-2;
	while (i <= n && j <= m)
	{
		res = (res + 1LL*((n-i) + (m-j+1))*CNK[cnt][k-2])%MOD;

		i += pi;
		j += pj;
		++cnt;
	}

	if (i != 0 && j != 0)
		res = (res * 2) % MOD;

	return res;
}

int main()
{

	FOR(i,0,3333)
	{
		CNK[i][0] = CNK[i][i] = 1;

		FOR(j,1,i)
		{
			CNK[i][j] = CNK[i-1][j-1] + CNK[i-1][j];

			if (CNK[i][j] >= MOD)
				CNK[i][j] -= MOD;
		}
	}

	int n, m, k;
	cin>>n>>m>>k;

	Int res = 0;

	FOR(i,0,n+1)
	{
		FOR(j,0,m+1)
		{
			int cnt = gcd(i,j);

			if (cnt != 1)
				continue;

			int I = i * (k-1);
			int J = j * (k-1);

			Int buf = solve(n,m,k,I,J,i,j) + solve(n-1,m-1,k,I,J,i,j);

			if (buf >= MOD)
				buf -= MOD;

			res = res + buf;

			if (res >= MOD)
				res -= MOD;
		}
	}

	cout << res << endl;

	return 0;
}
