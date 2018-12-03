#include <bits/stdc++.h>
using namespace std;
typedef long long ls;
const ls ln=2e5+5,d=1e9+7;
ls q,n,k,b[ln],c[ln];
ls exp(ls a,ls b){
    ls s=1;
    while(b){
        if(b&1){
            s=s*a%d;
        }    a=a*a%d,b>>=1;
    }    return s;
}
void mob_ncr(){
    ls p[ln];
    memset(p,0,sizeof(p));
    fill(b,b+ln,1),c[0]=c[1]=1;
    for(ls i=2;i<ln;i++){
        if(p[i]==0){
            for(ls j=i;j<ln;j+=i){
                b[j]*=(j%(i*i)==0 ? 0 : -1),p[j]=1;
            }
        }    c[i]=c[i-1]*i%d;
    }
}
ls cal(){
    ls ans=0;
    for(ls i=1;i<=n;i++){
        ans=(ans+b[i]*c[n/i+k-1]%d*exp(c[k]*c[n/i-1]%d,d-2)%d)%d;
    }    return (ans+d)%d;
}

int main(){
    mob_ncr();
    cin>>q;
    while(q--){
        cin>>n>>k;
        cout<<cal()<<endl;
    }
}
