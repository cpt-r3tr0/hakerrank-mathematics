#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<int> a;
    int n, q, x, y, t;
    cin>>n;

    for( int i = 0; i < n; i++ ){
        cin>>t;
        a.push_back(t);
    }

    cin>>q;

    for( int i = 0; i < q; i++ ){
        cin>>x>>y;

        if( x > y || a[x-1] % 2 || ( x < y && a[x] == 0 ) ) cout<<"Odd";
        else    cout<<"Even";

        cout<<endl;
    }

    return 0;
}
