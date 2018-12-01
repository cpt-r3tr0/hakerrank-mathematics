#include<iostream>
using namespace std;

long long ans(long long x)
{
	x*=6;
	long long low = 1,high = 1000000,mid,f1,f2;
	while(low<high)
	{
		mid = (low+high)/2;
		f1 = mid*(mid+1)*(2*mid+1);
		f2 = (mid+1)*(mid+2)*(2*mid+3);
		if(f1 == x)
			return mid;
		if(f2 == x)
			return mid+1;
		if(f1<x&&f2<x)
			low = mid+1;
		if(f1>x && f2>x)
			high = mid-1;
		else if(f1<x && f2>x)
			return mid;
	}
	return low;
}

int main()
{
	long long t,x;
	cin>>t;
	while(t--)
	{
		cin>>x;
		cout<<ans(x)<<'\n';
	}
	return 0;
}
