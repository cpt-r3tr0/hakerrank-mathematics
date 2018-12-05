#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;

int main()
{
      int t;
      cin>>t;
      while(t--)
      {
            int n,k;
            cin>>n>>k;
            lli arr[k];
            for(int i = 0;i<k;i++)
                  arr[i] = 0;
            lli sum = 0;
            arr[0] = 1;
            for(int i=0;i<n;i++)
            {
                  lli x;
                  cin>>x;
                  sum += x;
                  sum %= k;
                  arr[sum]++;
            }
            lli ans = 0;
            for(int i=0;i<k;i++)
                  ans += (arr[i]*(arr[i]-1)/2);
            cout<<ans<<endl;
      }
	return 0;
}
