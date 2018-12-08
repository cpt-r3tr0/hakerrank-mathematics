#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long n,m;
      long answer=0,t,i;
    long a,b,k,ii,jj,kk;
   cin>>n>>m;
   vector<long> array(n);
   t = m;
   while(t--){
     cin>>a>>b>>k;
     answer = answer + (abs(a-b)+1)*k;
   }
   answer = floor(answer/n);
   cout<<answer<<endl;
   return 0;
 }
