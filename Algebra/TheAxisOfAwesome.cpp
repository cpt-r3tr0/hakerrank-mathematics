#include <bits/stdc++.h>

using namespace std;

#define int int64_t
#define double long double

const double eps = 1e-9;

signed main(){

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
        for(int i = 0; i < n; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            a += y * y + z * z;
            b += x * x + z * z;
            c += x * x + y * y;
            d += - x * y;
            e += - x * z;
            f += - y * z;
        }
        int A = -1,
            B = a + b + c,
            C = d * d + e * e + f * f - a * b - a * c - b * c,
            D = a * b * c - a * f * f - b * e * e - c * d * d + 2 * d * e * f;
        int dA = 3 * A, dB = 2 * B, dC = C;
        int dD = dB * dB - 4 * dA * dC;
        if(dD == 0)
        {
            cout << 0 << "\n";
            continue;
        }
        double x = (- dB + sqrt(dD)) / (2 * dA);
        double F = A * x * x * x + B * x * x + C * x + D;
        if(abs(F) < eps)
            cout << 1 << "\n";
        else
            cout << 2 << "\n";
    }
}
