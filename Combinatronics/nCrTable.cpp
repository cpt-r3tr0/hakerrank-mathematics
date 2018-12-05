#include <bits/stdc++.h>
using namespace std;
#define llu unsigned long long
#define MOD 1000000000

llu arr[1001][1001];
void pascalTriangle(int n)
{
  for (int line = 0; line < n; line++)
  {
    for (int i = 0; i <= line; i++)
    {
      if (line == i || i == 0)
           arr[line][i] = 1;
      else
           arr[line][i] = (arr[line-1][i-1] + arr[line-1][i])%MOD;
    }
  }
}
int main()
{
    pascalTriangle(1000);
    llu t, n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0;i<=n;i++)
        {
            cout<<arr[n][i]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
