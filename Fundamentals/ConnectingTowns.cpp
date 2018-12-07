#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int test ;
    cin >> test;
    while(test--){
        int towns,
            *routes,
            ans =1 ;
        cin>> towns;
        routes = new int[towns-1];
        for(int i =0; i < towns-1; i++){
            cin >> routes[i];
            ans *= routes[i];
            ans = ans % 1234567;
        }
        cout << ans << endl;
    }

    return 0;
}
