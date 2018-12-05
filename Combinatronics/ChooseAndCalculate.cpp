#include <iostream>
#include <cmath>
#include <cstdlib>
#define ull unsigned long long
#define MODNUM 1000000007
using namespace std;

int cmp(const void* a,const void* b)
{
    return *(int*)a - *(int*)b;
}
ull powMod(ull a,int power)
{
    if(power==0)
        return 1L;
    ull temp=powMod(a,power/2);
    if(power%2==1)
        return ((((temp%MODNUM)*a)%MODNUM)*temp)%MODNUM;
    return (temp*temp)%MODNUM;
}

void findCombinations(ull comb[],int sizeC,int K)
{
    comb[0]=1;
    for(int i=1;i<sizeC;i++){
        comb[i]=((ull)((comb[i-1]*(K+i-1))%MODNUM)*powMod(i,MODNUM-2))%MODNUM;
    }
}

int main(){
    int N,K;
    cin>>N>>K;
    int A[N];
    for(int i=0;i<N;i++){
        cin>>A[i];
    }
    ull comb[N-K+1];
    findCombinations(comb,N-K+1,K);
    qsort(A,N,sizeof(int),cmp);
    ull res=0;
    for(int i=K-1;i<N;i++){
        res=(res+(A[i]*comb[i-K+1])%MODNUM)%MODNUM;
    }
    for(int i=0;i<N-K+1;i++){
        res=(MODNUM+ res- (A[i]*comb[N-K-i])%MODNUM)%MODNUM;
    }
    cout<<res<<endl;
}
