#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long num[1003];

long divisors(long n)
{
    long gog = 0;
    for(long i = 1 ; i <= sqrt(n) ; i++){
        if(i == sqrt(n) && sqrt(n) == n/sqrt(n)){
            gog++;
        }
        else if(n%i == 0){
            gog++;
            gog++;
        }
    }
    return gog;
}

long gcd(long a , long b){
    if(b == 0){
        return a;
    }
    else{
        return gcd(b,a%b);
    }
}

int main() {
    long t;
    cin >> t;
    for(long i = 2 ; i <= 1000 ; i=i+2){
        num[i/2-1] = i*i;
    }
    while(t--){
        long long n;
        cin >> n;
        long answer = divisors(n);
        long counter = 0;
        for(long i = 0 ; ; i++){
            if(num[i] >= n){
                break;
            }
            if(n%num[i] == 0){
                counter++;
            }
        }
        if(counter == 0){
            cout << "0\n";
        }
        else{
            long common = gcd(counter,answer-1);
            cout << counter/common << "/" << (answer-1)/common << "\n";
        }
    }
    return 0;
}
