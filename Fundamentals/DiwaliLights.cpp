#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int c=100000;
long long power2(int n)
{
    if(n==0)
        return 1;
    else if(n==1)
        return 2;
    long long temp=power2(n/2);
    if(n%2==0)
    {
        temp=temp*temp;
        if(temp>=c)
            temp%=c;
    }
    else
    {
        temp=temp*temp*2;
        if(temp>=c)
            temp%=c;
    }
    return temp;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        long long val;
        val=power2(n);
        val-=1;
        printf("%lld\n",val);
    }
    return 0;
}
