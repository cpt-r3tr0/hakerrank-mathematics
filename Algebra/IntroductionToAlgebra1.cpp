#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int get(int n, const std::vector<int> &v, int x, int y) {
    return v[x*n+y];
}
void put(int n, std::vector<int> &v, int x, int y, int i) {
    v[x*n+y] = i;
}
int inc(int n, std::vector<int> &v, int x, int y) {
    return ++v[x*n+y];
}
int solve(int n, const std::vector<int> &v) {
    if (n == 1) return 255;
    int S;
    const int c_quasi = 1, c_loop = 2, c_semi = 4, c_monoid = 8, c_group = 16, c_abelian = 32, c_rack = 64, c_quandle = 128;

    bool quasi = true;
    bool rack = true;
    bool quandle = true;

    std::vector<int> q(n*n);
    std::vector<std::set<int>> el(n), er(n);
    std::set<int> r;
    bool symmetric = true;
    for (int i = 0; i < n; i++) {
        std::vector<int> c(n);
        for (int j = 0; j < n; j++) {
            int val = get(n,v,i,j);
            c[val] ++;
            if (c[val] > 1) {
                quasi = false;
                rack = false;
            }
            if (inc(n,q,j,val) > 1) {
                quasi = false;
            }
            if (val == i) {
                er[i].insert(j);
            }
            if (val == j) {
                el[j].insert(i);
            }
            if (val != get(n,v,j,i)) symmetric = false;
            if (i == j && val != i) quandle = false;
        }
        if (i == 0) {
            r = er[i];
        } else {
            std::set<int> rn;
            std::set_intersection(r.begin(), r.end(), er[i].begin(), er[i].end(), std::inserter(rn, rn.end()));
            r.swap(rn);
        }
    }

    for (int j = 0; j < n; j++) {
        std::set<int> rn;
        std::set_intersection(r.begin(), r.end(), el[j].begin(), el[j].end(), std::inserter(rn, rn.end()));
        r.swap(rn);
    }

    int e = r.size() == 1? *r.begin() : -1;

    bool loop = quasi && (e>=0);

    bool semi = true;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = get(n,v,i,j);
            for (int k = 0; k < n; k++) {
                int val2 = get(n, v, j, k);
                int val3 = get(n, v, i, val2);
                if (val3 != get(n, v, val, k)) {
                    semi = false;
                }
                if (val3 != get(n,v, val, get(n,v,i,k))) {
                    rack = false;
                }
            }
        }
    }

    bool monoid = semi && (e >= 0);

    bool group = monoid && loop;

    bool abelian = group && symmetric;

    quandle = quandle && rack;

    return (quasi ? c_quasi : 0) +
        (loop ? c_loop : 0) +
        (semi ? c_semi : 0) +
        (monoid ? c_monoid : 0) +
        (group ? c_group : 0) +
        (abelian ? c_abelian : 0) +
        (rack ? c_rack : 0) +
        (quandle ? c_quandle : 0);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T,n;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        std::cin >> n;
        std::vector<int> v(n*n);
        for (int j = 0; j < n*n; j++) {
            std::cin >> v[j];
        }
        std::cout << solve(n, v) << std::endl;
    }
    return 0;
}
