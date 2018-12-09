#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<sstream>
#include<set>
#include<fstream>
#include<cfloat>
using namespace std;
#define PI (2.*acos(0.))
#define EPS 1e-9
#define ZERO(x)     (fabs(x) < EPS)
#define EQ(a,b)     (ZERO((a)-(b)))
#define LESSER(a,b) (!EQ(a,b) && (a)<(b))
#define GREATER(a,b)(!EQ(a,b) && (a)>(b))
#define GETBIT(x,i) (x&(1<<i))
#define SETBIT(x,i) (x|(1<<i))
#define FORab(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,n) FORab(i,0,(n)-1)
#define FOR1(i,n) FORab(i,1,n)
#define FORit(it,a) for( typeof((a).begin()) it=(a).begin();it!=(a).end();it++)
#define all(a) (a).begin(),(a).end()
#define ms(a,b) memset((a),(b),sizeof(a))
#define pb push_back
#define sz(a) (int)a.size()
#define in(a,b,c) ((a) <= (b) && (b) <= (c))
#define px first
#define py second
#define MOD 1000000007
typedef long long  LL;
typedef vector<int>   vi;
typedef pair<LL,LL>  pll;

LL mem[2][20][20][165][165],L,R,po[22];
LL mem1[2][20][20][165][165];
int K;
LL solve(int pre, int ind, int k, int sum1, int sum2, string &str){
    if(ind==sz(str)){
        mem1[pre][ind][k][sum1][sum2]=0;
        if(sum1==sum2)return 1;
        return 0;
    }
    if(mem[pre][ind][k][sum1][sum2]!=-1)return mem[pre][ind][k][sum1][sum2];
    LL &ret=mem[pre][ind][k][sum1][sum2];
    LL &ans=mem1[pre][ind][k][sum1][sum2];
    ans=0;
    ret=0;
    if(pre){
        FOR(i,str[ind]-'0'){
            if(k==0&&i==0){
                LL x=solve(0,ind+1,0,sum1,sum2,str);
                ret+=x;
                ret%=MOD;
                ans+=mem1[0][ind+1][0][sum1][ sum2];
                ans%=MOD;
                //ans+=(( (x*i)%MOD )*po[sz(str)-ind-1])%MOD;
                //ans%=MOD;
            }else{
                LL x=solve(0,ind+1,k+1,sum1+(i)*(k<K?1:0),sum2+ i*(((sz(str)-(ind+1))<K)?1:0),str);
                ret+=x;
                ret%=MOD;
                ans+=(( (x*i)%MOD )*po[sz(str)-ind-1])%MOD;
                ans%=MOD;
                ans+=mem1[0][ind+1][k+1][sum1+(i)*(k<K?1:0)][sum2+ i*(((sz(str)-(ind+1))<K)?1:0)];
                ans%=MOD;
            }
        }
        LL x=solve(1,ind+1,k+1,sum1+(str[ind]-'0')*(k<K?1:0),sum2+ (str[ind]-'0')*(((sz(str)-(ind+1))<K)?1:0),str);
        ret+=x;
        ret%=MOD;
        ans+=(( (x*(str[ind]-'0'))%MOD )*po[sz(str)-ind-1])%MOD;
        ans%=MOD;
        ans+=mem1[1][ind+1][k+1][sum1+((str[ind]-'0'))*(k<K?1:0)][sum2+ (str[ind]-'0')*(((sz(str)-(ind+1))<K)?1:0)];
        ans%=MOD;
    }else{
        FOR(i,10){
            if(k==0&&i==0){
                LL x=solve(0,ind+1,0,sum1,sum2,str);
                ret+=x;
                ret%=MOD;
                //ans+=(( (x*i)%MOD )*po[sz(str)-ind-1])%MOD;
                //ans%=MOD;
                ans+=mem1[0][ind+1][0][sum1][ sum2];
                ans%=MOD;
            }else{
                LL x=solve(0,ind+1,k+1,sum1+(i)*(k<K?1:0),sum2+ i*(((sz(str)-(ind+1))<K)?1:0),str);
                ret+=x;
                ret%=MOD;
                ans+=(( (x*i)%MOD )*po[sz(str)-ind-1])%MOD;
                ans%=MOD;
                ans+=mem1[0][ind+1][k+1][sum1+(i)*(k<K?1:0)][sum2+ i*(((sz(str)-(ind+1))<K)?1:0)];
                ans%=MOD;

            }
        }
    }
    return ret;
}
int main()
{
    po[0]=1;
    FOR1(i,18)po[i]=(po[i-1]*10)%MOD;
    cin>>L>>R>>K;
    string str; stringstream ss; ss<<R; ss>>str; ms(mem,-1); //cout<<str<<endl;
    LL ans1=0,ans2=0;
    //cout<<
    solve(1,0,0,0,0,str);//<<endl;
    ans1=mem1[1][0][0][0][0];
    string str1; stringstream ss1; ss1<<(L-1); ss1>>str1; ms(mem,-1);// cout<<str1<<endl;
    //cout<<
    solve(1,0,0,0,0,str1);//<<endl;
    ans2=mem1[1][0][0][0][0];
    //cout<<ans1<<" "<<ans2<<endl;
    cout<<(ans1-ans2+MOD)%MOD<<endl;
    return 0;
}
