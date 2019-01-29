#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
using namespace std;

typedef long long ll;
#define debug(a) cout << #a << ": " << (a) << endl;
#define A first
#define B second
#define MP make_pair

typedef pair<int, int> pii;
const int INF   = 0x3f3f3f3f;
const int MOD = 1000000007;
const int MAXN = 1515;
const int START = MOD - 506944448;
int N;
bool A[MAXN][MAXN];

// fills in br and returns #full
int create(int br[MAXN][MAXN])
{
    int nfull = 0;
    int high[MAXN];
    memset(high, 0, sizeof high);
    for (int row=0; row<N; row++) {
        // set up high
        for (int i=0; i<N; i++)
            if (A[row][i]) high[i]++;
            else high[i] = 0;

        // put a row into out
        stack<pii> S; // (left, height)
        S.push(MP(-1, 0)); // makes things easier
        int area = 0;
        int fback = 0;
        for (int r=0; r<=N; r++) {
            fback = r;
            while (high[r] < S.top().B) {
                fback = S.top().A;
                int A = S.top().A, B = r, h1 = S.top().B;
                int w = r - S.top().A;
                area -= w * S.top().B;
                S.pop();
                int h0 = max(high[r], S.top().B)+1;
                area += w * max(high[r], S.top().B);

                // enter the math
                ll full_here = START;
                full_here = full_here * (A - B - 3) % MOD;
                full_here = full_here * (A - B - 2) % MOD;
                full_here = full_here * (A - B - 1) % MOD;
                full_here = full_here * (A - B) % MOD;
                full_here = full_here * (h0 - h1 - 1) % MOD;
                full_here = full_here * (h0*h0 + h0*(h1+1) + h1*(h1+2)) % MOD;
                full_here = (full_here + MOD) % MOD;

                nfull = (nfull+full_here) % MOD;
            }
            if (high[r] > S.top().B) {
                S.push(MP(fback, high[r]));
                area += high[r];
            } else {
                area += high[r];
            }
            br[row][r] = area;
        }
        assert(S.size() == 1);
    }
    return (nfull+MOD)%MOD;
}

int BR[MAXN][MAXN], BL[MAXN][MAXN], TR[MAXN][MAXN], TL[MAXN][MAXN];
bool tmp[MAXN][MAXN];

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin >> N;
    for (int i=0; i<N; i++)
    {
        string s; cin >> s;
        for (int j=0; j<N; j++)
        {
            tmp[i][j] = (s[j] == '1');
        }
    }
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            A[i][j] = tmp[i][j];
    ll nfull = create(BR);

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            A[i][j] = tmp[i][N-j-1];
    create(BL);
    for (int i=0; i<N; i++)
        for (int j=0; j < N-j-1; j++)
            swap(BL[i][j], BL[i][N-j-1]);

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            A[i][j] = tmp[N-i-1][j];
    create(TR);
    for (int i=0; i < N-i-1; i++)
        for (int j=0; j<N; j++)
            swap(TR[i][j], TR[N-i-1][j]);

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            A[i][j] = tmp[N-i-1][N-j-1];
    create(TL);
    for (int i=0; i<N; i++)
        for (int j=0; j < N-j-1; j++)
            swap(TL[i][j], TL[i][N-j-1]);
    for (int i=0; i < N-i-1; i++)
        for (int j=0; j<N; j++)
            swap(TL[i][j], TL[N-i-1][j]);

    ll nrects = 0;
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            nrects = (nrects + BR[i][j]) % MOD;
    ll npairs = nrects + nrects*(nrects-1)/2 % MOD;

    ll nsep = 0;
    ll below = nrects;
    for (int i=0; i<N; i++) {
        ll cur = 0;
        for (int j=0; j<N; j++) {
            cur = (cur + BR[i][j]) % MOD;
            below = (below - TR[i][j]) % MOD;
        }
        nsep = (nsep + cur * below) % MOD;
    }
    ll right = nrects;
    for (int i=0; i<N; i++)
    {
        ll cur = 0;
        for (int j=0; j<N; j++)
        {
            cur = (cur + BR[j][i]) % MOD;
            right = (right - BL[j][i]) % MOD;
        }
        nsep = (nsep + cur * right) % MOD;
    }

    int sum[MAXN];
    memset(sum, 0, sizeof sum);
    for (int i=0; i+1<N; i++)  {
        int psum = 0;
        for (int j=0; j+1<N; j++) {
            sum[j] = (sum[j] + BR[i][j]) % MOD;
            sum[j] = (sum[j] + psum) % MOD;
            psum = (psum + BR[i][j]) % MOD;

            nsep = (nsep - TL[i+1][j+1] * (ll)sum[j]) % MOD;
        }
    }
    memset(sum, 0, sizeof sum);
    for (int i=0; i+1<N; i++)  {
        int psum = 0;
        for (int j=N-1; j>0; j--)  {
            sum[j] = (sum[j] + BL[i][j]) % MOD;
            sum[j] = (sum[j] + psum) % MOD;
            psum = (psum + BL[i][j]) % MOD;
            nsep = (nsep - TR[i+1][j-1] * (ll)sum[j]) % MOD;
        }
    }
    cout << ((2*(npairs - nfull - nsep) % MOD) + MOD)%MOD << '\n';
    return 0;
}
