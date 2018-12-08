#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define mod 1000000000;
int a[2005][1002];

void calculate(int n,int r){
    if(r==0||r==n){a[n][r]=1;}
    else if(r==1||r==(n-1)){a[n][r]=n%mod;}
    else{
        int p,q;
        if(a[n-1][r]==0)calculate(n-1,r);
        if(a[n-1][r-1]==0)calculate(n-1,r-1);
        p=a[n-1][r];
        q=a[n-1][r-1];
        a[n][r]=(p+q)%mod;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        calculate(k+n-1,n-1);
        cout<<a[k+n-1][n-1]<<endl;
    }
    return 0;
}
