#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static bool IsFib(long T)
{
    double root5 = sqrt(5);
    double phi = (1 + root5) / 2;

    long id = (long)floor( log(T*root5) / log(phi) + 0.5 );
    long u = (long)floor( pow(phi, id)/root5 + 0.5);

    return (u == T);
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long t ,n ;
    cin>> t;
    while (t--){
        cin>> n ;
        if (IsFib(n) == 1)
            cout << "IsFibo" << endl;
        else
            cout << "IsNotFibo" << endl;
    }

    return 0;
}
