#include <bits/stdc++.h>

#define ll long long
#define m 1000000007

using namespace std;

int main (){
    ll test,n;
    cin>>test;
    while (test--){
    	cin>>n;
    	ll ans=((n%m)*(n%m))%m;
    	cout<<ans<<endl;
    }
    return 0;
}
