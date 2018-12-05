#include<iostream>
#include<set>
#include<map>
#include<string>
#include<stdio.h>
#include<sstream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<string.h>
using namespace std ;
#define INF (int)1e9
#define MAXN 50002
#define MOD 1000000007
int n,a[MAXN] ;


int dp[MAXN] ;
int solve(){
    sort(a,a + n) ;
    dp[n] = 1 ;
    for(int i = n - 1;i >= 0;i--){
        int low = -1,high = n ;
        while(low + 1 < high){
            int mid = low + (high - low) / 2 ;
            if(a[mid] <= i) low = mid ;
            else high = mid ;
        }
    int ct = low + 1 ;
    if(ct <= i) dp[i] = 0 ;
    else dp[i] = 1LL * (ct - i) * dp[i + 1] % MOD ;
    }
    return dp[0] ;
}


int main(){
    int tests ;
    scanf("%d",&tests) ;
    while(tests--){
        scanf("%d",&n) ;
        for(int i = 0;i < n;i++) scanf("%d",&a[i]) ;
        for(int i = 0;i < n;i++) if(a[i] < 0 || a[i] > n) while(1) ;
        int ret = solve() ;
        printf("%d\n",ret) ;
    }
    return 0 ;
}
