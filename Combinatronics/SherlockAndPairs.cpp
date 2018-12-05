#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll a[1000005],ans;
int T,i,j,n,x;



int main(){
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    scanf("%d",&T);
    while(T--){
    scanf("%d",&n);
    ans=0;
    for(i=1;i<=n;i++){
        scanf("%d",&x);
        a[x]++;
    }
    for(i=1;i<=1000000;i++)
        ans+=(a[i]*(a[i]-1)),a[i]=0;
    cout<<ans<<endl;
    }
    return 0;
}
