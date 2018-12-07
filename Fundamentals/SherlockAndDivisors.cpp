#include<bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	scanf("%d",&t);
	while( t-- ) {
		long long n,i,j,k,l;
		scanf("%lld",&n);
		long long ans =0;
		for(i=1;i*i<=n;i++){
			if(n%i==0){
			if(n/i!=i){
				k = n/i;
				if(!(k&1))
				ans++;
			}
			if(!(i&1))
				ans++;

				}
			}
			printf("%lld\n",ans);
	}
	return 0;
}
