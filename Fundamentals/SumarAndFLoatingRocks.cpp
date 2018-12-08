#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b){
    if(b>a) return gcd(b,a);
    if(b==0) return a;
    return gcd(b, a%b);
}

int main() {
    int T;
    cin >> T;
    for(int t=0;t<T;t++){
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int dx = abs(x1-x2);
        int dy = abs(y1-y2);

        int g = gcd(dx, dy);
        cout << (g-1) << endl;
    }
    return 0;
}
