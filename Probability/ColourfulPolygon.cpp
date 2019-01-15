#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <bitset>
#include <sstream>

using namespace std;

#define fore(i, l, r) for(int i = int(l); i < int(r); ++i)
#define forn(i, n) fore(i, 0, n)
#define fori(i, l, r) fore(i, l, (r) + 1)
#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair
#define X first
#define Y second

template<typename T> inline T abs(T a){ return ((a < 0) ? -a : a); }
template<typename T> inline T sqr(T a){ return a * a; }

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int NMAX = 110000;
const int mod = int(1e9) + 7;

int n, a[NMAX], usedPfx[NMAX], usedSfx[NMAX];

int d[NMAX];

void add(int& x, int y){
    x += y;
    while(x >= mod)
        x -= mod;
    while(x < 0)
        x += mod;
}

void upd(int i, int di){
    for(; i < NMAX; i = (i | (i + 1)))
        add(d[i], di);
}

int sum(int r){
    int ans = 0;
    for(; r >= 0; r = (r & (r + 1)) - 1)
        add(ans, d[r]);
    return ans;
}

int sum(int l, int r){
    return sum(r) - sum(l - 1);
}

int main() {
#ifdef ssu1
    assert(freopen("input.txt", "rt", stdin));
#endif
    cin >> n;
    forn(i, n){
        cin >> a[i];
        a[i]--;
    }


    {
        int maxdif = n + 1, starti = 0;
        vector<int> used(n);
        int j = 0;
        forn(i, n){
            while(j < n && !used[a[j]]){
                used[a[j]] = true;
                j++;
            }
            if(j != n && j - i < maxdif){
                maxdif = j - i;
                starti = i;
            }
            used[a[i]] = false;
        }

        rotate(a, a + starti, a + n);
    }

    vector<int> rg(n);
    {
        vector<int> used(n);
        int j = 0;
        forn(i, n){
            while(j < n && !used[a[j]]){
                used[a[j]] = true;
                j++;
            }
            rg[i] = j;
            used[a[i]] = false;
        }
    }

    int ans = 0;
    forn(fsPick, n){
        memset(d, 0, sizeof d);

        upd(fsPick, 1);
        upd(fsPick + 1, -1);

        fore(i, fsPick, n - 1){
            int cur = sum(i), ni = rg[i + 1];

            if(ni == n)
                ni--;

            upd(i + 1, cur);
            upd(ni + 1, -cur);
        }

        memcpy(usedSfx, usedPfx, sizeof(int) * n);
        for(int lastPick = n - 1; lastPick > fsPick; lastPick--){
            add(ans, sum(lastPick));
            if(usedSfx[a[lastPick]])
                break;
            usedSfx[a[lastPick]] = true;
        }

        if(usedPfx[a[fsPick]])
            break;
        usedPfx[a[fsPick]] = true;
    }

    cout << ans << endl;
    return 0;
}
