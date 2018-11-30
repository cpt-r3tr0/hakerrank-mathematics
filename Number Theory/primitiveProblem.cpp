#include <bits/stdc++.h>
using namespace std;
map<int,int>us;
long long zpower(long long x,long long y,long long int MOD){
   long long int temp;
    if( y == 0)
        return 1;
    temp = zpower(x, y/2,MOD);
    temp=(temp%MOD*temp%MOD)%MOD;
    if (y%2 == 0)
        return temp;
    else
        return (x%MOD*temp)%MOD;
}
void euler_phi_function(int n){
  while(n%2==0){
       n=n/2; us[2]++;
  }
  for(int i=3;i<=sqrt(n);i+=2){
      while(n%i==0){
          n=n/i; us[i]++;
      }
  }
    if(n>2)us[n]++;
}

int main(){
  long long n;
  cin>>n;
  euler_phi_function(n-1);
    for(int i=2;i<n;i++){
      bool flag=true;
      for(auto x:us){
            int y=(n-1)/x.first;
           if(zpower(i,y,n)==1){
            flag=false; break;
           }
        }
       if(flag){ cout<<i<<" "; break;}
    }
    n--;
    for(auto x:us){
        n=(n/x.first)*(x.first-1);
    }
    cout<<n;

}
