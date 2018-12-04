#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
#define SZ(x) ((int)(x).size())

int L, W, H, a, b, c, d, e, f, p, q, r, N;
int inv_tbl[105][105], u_inv_tbl[105][105];

int inv(int x, int y, int P, int Q, int R, int S) {
if(y==0) return P;
    return inv(y, x%y, R, S, P-R*(x/y), Q-S*(x/y));
}

//cache the inversion results (note that 1 <= M <= 200)
int inv(int x, int M) {
    if(!u_inv_tbl[x][M]) {
        u_inv_tbl[x][M] = 1;
        inv_tbl[x][M] = (inv(x, M, 1, 0, 0, 1)%M+M)%M;
    }
    return inv_tbl[x][M];
}

int sol[105], qb, qe;
void getsol(int ql, int qr, int &modulo, int u, int x, int p, int M) {
// u + ?x = p or -p (mod) M
// ? = sol (mod) modulo

if (x < 0) { u = -u; x = -x; }
int p1 = ((p-u)%M+M)%M;
int p2 = ((-p-u)%M+M)%M;

int G = __gcd(M, x);
M/=G; x/=G;
int g = __gcd(modulo, M), MM = M / g;
int ret_modulo = modulo * MM;
modulo /= g;
int MMInv = inv(modulo%MM, MM);

if (p1 % G == 0) {
    p1 = p1/G * inv(x, M);
    for(int it=ql;it<qr;it++) {
        int t = sol[it];
        // ? = p1 (mod) MM
        // ? = t (mod) modulo
        if ((p1 - t) % g) continue;
        int tmp = ((p1 - t) * MMInv * modulo + t) % ret_modulo;
        tmp = (tmp+ret_modulo)%ret_modulo;
        sol[qe++] = tmp;
    }
}
if (p2 % G == 0) {
    p2 = p2/G * inv(x, M);
    for(int it=ql;it<qr;it++) {
        int t = sol[it];
        // ? = p2 (mod) M
        // ? = t (mod) modulo
        if ((p2 - t) % g) continue;
        int tmp = ((p2 - t) * MMInv * modulo + t) % ret_modulo;
        tmp = (tmp+ret_modulo)%ret_modulo;
        sol[qe++] = tmp;
    }
}
qb = qr;
modulo = ret_modulo;
}

void ask(int &min_pos, int &min_neg, int u, int v, int w, int x, int y, int z) {
    int modulo = 1;
    // initialize the solution queue
    sol[0] = 0;
    qb = 0, qe = 1;

    // p + ?x = u or -u (mod) 2L
    // q + ?y = v or -v (mod) 2W
    // r + ?z = w or -w (mod) 2H
    getsol(qb, qe, modulo, p, x, u, 2*L);
    getsol(qb, qe, modulo, q, y, v, 2*W);
    getsol(qb, qe, modulo, r, z, w, 2*H);

    if (qb == qe) { min_pos = min_neg = -1; return; }
    min_pos = *min_element(sol + qb, sol + qe);
    min_neg = modulo - *max_element(sol + qb, sol + qe);
}

int muls[105][105][105];
int main(void) {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &L, &W, &H);
        scanf("%d%d%d", &a, &b, &c);
        scanf("%d%d%d", &d, &e, &f);
        scanf("%d%d%d", &p, &q, &r);
        scanf("%d", &N);
        memset(muls, 0, sizeof(muls));

        const int offset = 50;
        int cSergey = 0, cChen = 0;
        // caculate multiplicity
        for(int x=-N;x<=N;x++) for(int y=-N;y<=N;y++) for(int z=-N;z<=N;z++) {
            int g = __gcd(abs(x), __gcd(abs(y), abs(z)));
            if(g) muls[x/g+offset][y/g+offset][z/g+offset]++;
        }
        // caculate positive (x, y, z) and negative (-x, -y, -z) at same time
        for(int x=0;x<=N;x++) for(int y=-N;y<=N;y++) for(int z=-N;z<=N;z++) {
            if((x==0&&y<0) || (x==0 && y==0 && z<0)) continue;
            int g = __gcd(abs(x), __gcd(abs(y), abs(z)));
            if(!g) continue;
            if(g == 1) {
            int S_pos, S_neg, C_pos, C_neg;
            ask(S_pos, S_neg, a, b, c, x, y, z);
            ask(C_pos, C_neg, d, e, f, x, y, z);

            int m_pos = muls[x+offset][y+offset][z+offset];
            int m_neg = muls[-x+offset][-y+offset][-z+offset];
            if(S_pos != -1 && C_pos != -1) (S_pos < C_pos? cSergey+=m_pos: cChen+=m_pos);
            else if(S_pos != -1) cSergey+=m_pos;
            else if(C_pos != -1) cChen+=m_pos;

            if(S_neg != -1 && C_neg != -1) (S_neg < C_neg? cSergey+=m_neg: cChen+=m_neg);
                else if(S_neg != -1) cSergey+=m_neg;
                else if(C_neg != -1) cChen+=m_neg;
            }
        }
        printf("%d %d\n", cSergey, cChen);
    }
    return 0;
}
