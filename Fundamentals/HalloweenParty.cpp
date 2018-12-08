#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long int test , *k, *os;
    k = (long int*)malloc(test*sizeof(long int));
    os = (long int*)malloc(test*sizeof(long int));
    cin >> test;
    for (int i=0; i<test; i++){
        cin >> k[i];
        if(k[i]%2==0)
            os[i]= (k[i]*k[i])/4;
        else
            os[i]=(k[i]/2)*((k[i]/2)+1);

        cout << os[i] << endl;
    }
    return 0;
}
