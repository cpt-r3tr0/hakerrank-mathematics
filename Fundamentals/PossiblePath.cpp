#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <limits.h>
#include <cstring>
#include <string>

using namespace std;

#define PII pair<int ,int>
#define m_p make_pair
#define LL long long

int n,m,k;
string str,a,b,c,d;
int la,lb,lc,ld;
char ch,ch1;

LL GCD (LL a ,LL b)
{
    if(b==0) return a;
    return GCD(b,a%b);
}

int main()
{
    int test;
    LL a,b,x,y;
    cin>>test;

    while(test--){
        cin>>a>>b>>x>>y;

        if(GCD(a,b)==GCD(x,y))
            cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
