#include <iostream>
#include <stdio.h>
using namespace std;

int hcf(int a,int b)
{
	if(b==0)
	return a;
	else
	return hcf(b,a%b);
}

int main()
{
	int t,a,b,c;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d %d",&a,&b,&c);
		int ast=hcf(a,b);
		int number=a>b?a:b;
		if(c%ast==0 && c<=number)
		cout<<"YES"<<endl;
		else
		cout<<"NO"<<endl;
	}
	return 0;
}
