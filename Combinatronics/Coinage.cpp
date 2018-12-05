#include <bits/stdc++.h>

using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        int a,b,c,d,count=0;
        cin >> a >> b >> c >> d;
        for(int one=0;one<=a;one++){
            for(int two=0;two<=b && two <= (N-one)/2;two++){
                for(int five=0;five<=c && five<=(N-one-2*two)/5;five++){
                    if((N-one-2*two-5*five)%10 == 0 && (N-one-2*two-5*five)/10<=d)    count++;
                }
            }
        }
        cout << count << endl;
    }
    return 0;
}
