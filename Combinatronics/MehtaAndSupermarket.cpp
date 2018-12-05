#include <iostream>
using namespace std;

//				   123456789123456789
#define THRESHOLD 1000000000000000000
#define INFI 	  2000000000000000000

inline int getbit(int n, int bit){
	return (n>>bit)%2;
}


//assume L < R, L>=0
inline long long getInRange(long long L, long long R, long long i){
	return (R/i) - ((L-1)/i);
}

long long gcd(long long a, long long b){
	if(a<b) return gcd(b,a);
	return ((b==0)? a : gcd(b, a%b));
}


//returns INFI on overflow
long long lcm(long long a, long long b){


	if(a>THRESHOLD || b>THRESHOLD) return INFI;
	long long g = gcd(a,b);
	a /= g;
	if(b > (THRESHOLD + a-1)/a)
		return INFI;
	return a*b;
}



int main(){

	int N;
	cin>>N;
	int A[20];
	for(int i=0; i<N; i++)
		cin>>A[i];


	int D;
	long long L[102];
	long long R[102];
	long long totalAns[102];
	cin>>D;
	for(int i=0;i<D;i++){
		cin>>L[i]>>R[i];
		totalAns[i] = 0;
	}

	int maxVal = (1<<N);
	for(int i=1;i<maxVal; i++){
		long long currLcm = 1;
 		int count = 0;
		for(int bit=0;bit<N;bit++){
			if(getbit(i, bit) == 1){
				currLcm = lcm(currLcm, A[bit]);
				count++;
			}
		}
		for(int i=0;i<D;i++){
			totalAns[i] += getInRange(L[i], R[i], currLcm) * (2*(count & 1) - 1);
		}
	}

	for(int i=0;i<D;i++)
		cout<<totalAns[i]<<endl;

	return 0;
}
