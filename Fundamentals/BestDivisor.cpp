#include <bits/stdc++.h>

using namespace std;


int sum(int n){
    int res=0;
    while(n!=0){
        res+=n%10;
        n/=10;
    }
    return res;
}
int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int max = sum(n);
    int res = n;

    for (int i = n/2; i >0; i--){
        if(n%i == 0){
            int temp = sum(i);
            if (temp == max){
                res = i;
            }
            else if(temp>max){
                max = temp;
                res = i;
            }

        }
    }

    cout<<res;
    return 0;
}
