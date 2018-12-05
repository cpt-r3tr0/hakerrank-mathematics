#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
ll fact[30]={0};
ll compute(ll x,ll y){
    return (x>=y) ? fact[x]/(fact[x-y]*fact[y]) : 0;
   }
void findKthPermutation(ll k,ll n,ll m){
    ll partition;
    if(n==1&&m==0){
        cout<<"H";
        return;
    }
    if(n==0&&m==1){
        cout<<"V";
        return;
    }
    partition=compute(n+m-1,m);
    if(k<=partition){
        cout<<"H";
        findKthPermutation(k,n-1,m);
     }else{
        cout<<"V";
        findKthPermutation(k-partition,n,m-1);
     }
}

int main(){
    ll t,n,m,k;
    cin>>t;
    fact[0]=1;
    for(ll i=1;i<30;i++){
        fact[i]=fact[i-1]*i;
    }
    while(t--){
        cin>>n>>m>>k;
        k++;
        findKthPermutation(k,n,m);
        cout<<endl;
    }
    return 0;
 }
