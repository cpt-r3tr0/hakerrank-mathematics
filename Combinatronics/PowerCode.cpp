#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define fo(i,a,b) dfo(int,i,a,b)
#define fr(i,n) dfr(int,i,n)
#define fe(i,a,b) dfe(int,i,a,b)
#define fq(i,n) dfq(int,i,n)
#define nfo(i,a,b) dfo(,i,a,b)
#define nfr(i,n) dfr(,i,n)
#define nfe(i,a,b) dfe(,i,a,b)
#define nfq(i,n) dfq(,i,n)
#define dfo(d,i,a,b) for (d i = (a); i < (b); i++)
#define dfr(d,i,n) dfo(d,i,0,n)
#define dfe(d,i,a,b) for (d i = (a); i <= (b); i++)
#define dfq(d,i,n) dfe(d,i,1,n)
#define ffo(i,a,b) dffo(int,i,a,b)
#define ffr(i,n) dffr(int,i,n)
#define ffe(i,a,b) dffe(int,i,a,b)
#define ffq(i,n) dffq(int,i,n)
#define nffo(i,a,b) dffo(,i,a,b)
#define nffr(i,n) dffr(,i,n)
#define nffe(i,a,b) dffe(,i,a,b)
#define nffq(i,n) dffq(,i,n)
#define dffo(d,i,a,b) for (d i = (b)-1; i >= (a); i--)
#define dffr(d,i,n) dffo(d,i,0,n)
#define dffe(d,i,a,b) for (d i = (b); i >= (a); i--)
#define dffq(d,i,n) dffe(d,i,1,n)
#define ll long long
#define alok(n,t) ((t*)malloc((n)*sizeof(t)))
#define pf printf
#define sf scanf
#define pln pf("\n")

#define lim 1111111
#include<algorithm>
using namespace std;

char line[lim];
char word[lim];
char **C;
int *Cl;
int **gd;
int *bd;
ll *a;

int *onQ;
int *Q;
int *P;
ll *S;

ll frob(int n) {
    onQ = alok(a[0], int);
    Q = alok(31111111, int);
    P = alok(a[0], int);
    fr(i,a[0]) onQ[i] = 0;
    onQ[0] = 1;
    Q[0] = 0;
    P[0] = n-1;
    S = alok(a[0], ll);
    S[0] = 0;
    fo(i,1,a[0]) S[i] = a[0]*a[n-1];
    int ql = 1;
    fr(qi,ql) {
        int v = Q[qi];
        onQ[v] = 0;
        fq(j,P[v]) {
            int u = (v + a[j]) % a[0];
            ll w = S[v] + a[j];
            if (w < S[u]) {
                S[u] = w;
                P[u] = j;
                if (!onQ[u]) {
                    onQ[u] = 1;
                    Q[ql++] = u;
                }
            }
        }
    }
    ll mx = S[0];
    fo(i,1,a[0]) if (mx < S[i]) mx = S[i];
    return mx - a[0];
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
int *machine[1111];
int main() {
    fr(i,1111) machine[i] = alok(128, int);
    //a = alok(111, ll);
    //a[0] = 3; a[1] = 5; pf("%lld\n", frob(2));
    //a[0] = 3; a[1] = 5; a[2] = 7; pf("%lld\n", frob(3));
    //a[0] = 3*5; a[1] = 3*7; a[2] = 5*7; pf("%lld\n", frob(3));

    fgets(line, lim, stdin);
    int n;
    sscanf(line, "%d", &n);
    Cl = alok(n, int);
    C = alok(n, char*);
    gd = alok(n, int*);
    bd = alok(lim, int);
    fr(i,n) {
        C[i] = alok(lim, char);
        fgets(C[i], lim, stdin);
        Cl[i] = strlen(C[i])-1;//
        C[i][Cl[i]] = 0;
        gd[i] = alok(Cl[i], int);
        fr(j,Cl[i]) gd[i][j] = 1;
    }
    int k;
    fgets(line, lim, stdin);
    sscanf(line, "%d", &k);
    fr(xi,k) {
        fgets(line, lim, stdin);
        sscanf(line, "%s", word);
        int lw = strlen(word);
        // make machine word
        fr(i,128) machine[0][i] = 0;
        int i, j;
        for (i = 0, j = -1; i < lw; i++) {
            if (j >= 0) {
                for (int k = 0; k < 128; k++) {
                    machine[i][k] = machine[j][k];
                }
            }
            char d = word[i];
            machine[i][d] = i + 1;
            j = j < 0 ? 0 : machine[j][d];
        }
        fr(jj,n) {
            // feed to machine
            fr(l,Cl[jj]) bd[l] = 0;
            int cst = 0;
            fr(l,Cl[jj]) {
                cst = machine[cst][C[jj][l]];
                if (cst == lw) {
                    bd[l - lw + 1] = 1;
                    cst = j;
                }
            }
            int mxbd = -1;
            fr(l,Cl[jj]) {
                if (bd[l]) mxbd = l;
                if (mxbd >= 0 && l - lw < mxbd) gd[jj][l] = 0;
            }
        }
    }
    a = alok(n, ll);
    ll g = 0;
    fr(i,n) {
        a[i] = 0;
        fr(j,Cl[i]) {
            if (gd[i][j]) a[i]++;
        }
        g = gcd(g, a[i]);
    }
    if (g == 1) {
        sort(a, a + n);
        while (!a[0]) a++ ,n--;
        ll f = frob(n);
        pf("%lld\n", f);
    } else {
        pf("-1\n");
    }
}
