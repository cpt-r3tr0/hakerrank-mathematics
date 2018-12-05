#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define ll long long
ll fac[100001];

ll powmod(ll a, ll k, ll n){
    long long int b=1;
    while (k) {
        if (k%2==0) {
            k /= 2;
	        a = (a*a)%n;
        }
        else {
            k--;
            b = (b*a)%n;
        }
    }
    return b;
}

void init(){
    fac[0]=fac[1]=1;
    for(int i=2;i<=100000;i++)
        fac[i]=(fac[i-1]*i)%MOD;
}


int main(){
    string s;
    cin>>s;
    init();
    int c[26]={0};
    for(int i=0;s[i]!='\0';i++)
        c[s[i]-'a']++;
    ll ans=fac[s.size()/2];
    ll ans1=1;
    for(int i=0;i<26;i++){
        ans1*=fac[c[i]/2];
	    ans1%=MOD;
    }
    cout<<((ans*powmod(ans1,MOD-2,MOD))%MOD);
    return 0;
}
