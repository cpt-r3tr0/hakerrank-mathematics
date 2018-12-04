#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

void matrixmultiplication(long long arr[2][2],long long arr2[2][2],int mod){
    long long calc;
    int n=2;
    long long arr3[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            arr3[i][j]=0;
            for(int k = 0; k < n; k++){
                arr3[i][j] += arr[i][k]*arr2[k][j];
                arr3[i][j]%=mod;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            arr[i][j]=arr3[i][j];
        }
    }
}
void matrixpower(long long arr[2][2],long long b,int mod){
    long long ans[2][2];
    int n=2;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ans[i][j]=0;
        }
        ans[i][i]=1;
    }
    while(b>0){
        if(b&1){
            matrixmultiplication(ans,arr,mod);
        }
        matrixmultiplication(arr,arr,mod);
        b /= 2;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            arr[i][j]=ans[i][j];
        }
    }
}
ll gcd(ll a, ll b){
	if(b==0) return a;
	else return gcd(b,a%b);
}
const int mod = 1e9+7;
long long arr[2][2];
long long arr2[2][2];
int main() {
    arr2[0][0]=1;
    arr2[0][1]=1;
    ll n,ai,g=0;
	cin >> n;
	while(n--){
		cin >> ai;
		g = gcd(ai,g);
    }
    arr[0][0]=1;
    arr[0][1]=1;
    arr[1][0]=1;
    arr[1][1]=0;
    matrixpower(arr,g-2,mod);
    matrixmultiplication(arr2,arr,mod);
    cout << arr2[0][0] << "\n";
    return 0;
}
