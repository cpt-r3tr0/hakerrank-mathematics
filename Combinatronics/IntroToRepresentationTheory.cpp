#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cout.precision(7);

    double x ;

    vector<double> real ;
    vector<double> imag ;

    double PI = 3.14159265358979 ;

    int k, n ;

    cin >> n >> k  ;

    double a,b ;

    for(int i = 0 ; i < k ; i++){
        cin >> a >> b ;
        real.push_back(a) ;
        imag.push_back(b) ;
    }

    for(int i = 0 ; i < k ; i++){
        double sumreal = 0 ;

        for(int j = 0 ; j < k ; j++){
            int modded = (i*j) % k ; //
            sumreal = sumreal + real[j]*cos(2*modded*PI/k) - imag[j]*sin(2*modded*PI/k) ;
        }

        sumreal = sumreal/k + 0.5 ;

        int howmany ;

        howmany = sumreal ;

        double x = cos(2*i*PI/k) ;
        double y = -sin(2*i*PI/k) ;

        for(int l = 0 ; l < howmany ; l++){
            cout << fixed << x << " " << y << endl ;
        }

    }
    return 0;
}
