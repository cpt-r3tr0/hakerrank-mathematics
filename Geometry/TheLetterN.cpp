#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2510;

void mod(int &x, const int M) {
    while (x >= M) {
        x -= M;
    }
    while (x < 0) {
        x += M;
    }
}

struct Point {
    int x, y;
    Point() {
        x = y = 0;
    }
    Point(int xx, int yy) {
        x = xx;
        y = yy;
    }
};

Point operator -(const Point &A, const Point &B) {
    return Point(A.x - B.x, A.y - B.y);
}

bool where(const Point &A) {
    return (A.y > 0 || (A.y == 0 && A.x > 0) );
}

int det(const Point &A, const Point &B) {
    return A.x*B.y - A.y*B.x;
}

bool cmpAngles(const Point &A, const Point &B) {
    bool whA = where(A), whB = where(B);
    if (whA != whB) {
        return whA;
    }
    return det(A, B) > 0;
}

bool cmp(const pair<Point, int> &A, const pair<Point, int> &B) {
    return cmpAngles(A.first, B.first);
}

int sgn(int x) {
    if (x > 0) {
        return 1;
    }
    if (x == 0) {
        return 0;
    }
    if (x < 0) {
        return -1;
    }
    return 0;
}

int cross(const Point &A, const Point &B) {
    return A.x*B.x + A.y*B.y;
}

bool goodAngle(const Point &A, const Point &B) {
    return det(A, B) < 0 && cross(A, B) >= 0;
}


int cntLeft[MAXN][MAXN];
Point a[MAXN];
int n;

int dist(int st, int fin, const int M) {
    if (st <= fin) {
        return fin - st;
    }
    else {
        return M - st + fin;
    }
}


int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        for (int j = 0; j < i; j++) {
            if ( a[j].x == a[i].x && a[j].y == a[i].y ) {
                assert(false);
            }
        }
    }

    for (int it = 0; it < n; it++) {
        vector< pair<Point, int> > v;
        for (int j = 0; j < n; j++) {
            if (it == j) {
                continue;
            }
            v.push_back( make_pair(a[j] - a[it], j) );
        }

        sort(v.begin(), v.end(), cmp);

        int u = 0;
        for (int i = 0; i < v.size(); i++) {
            int j = i + 1;
            while (j < v.size() && where(v[i].first) == where(v[j].first) && det(v[i].first, v[j].first) == 0 ) {
                j++;
            }
            j--;

            if (u >= i && u <= j) {
                u = j + 1;
                mod(u, v.size() );
            }

            while (u != i && !goodAngle(v[i].first, v[u].first) ) {
                u++;
                mod(u, v.size() );
            }
            int res = dist(u, i, v.size() );
            for (int k = i; k <= j; k++) {
                cntLeft[ it ][ v[k].second ] = res;
            }
            i = j;
        }
    }

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                ans += cntLeft[i][j]*cntLeft[j][i];
            }
        }
    }

    cout << ans/2 << endl;
    return 0;
}
