#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

string nu;
bool ans;

int num(int a,int b,int c) {
	int cv=(nu[a]-'0')*100+(nu[b]-'0')*10+nu[c]-'0';
	return cv;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		ans=false;
		cin >> nu;
		if(nu.length()>2) {
			for(int i=0;i<nu.size();++i) {
				if(!ans) for(int j=i+1;j<nu.size();++j) {
						if(!ans) for(int k=j+1;k<nu.size();++k) {
								if(num(i,j,k)%8==0) ans=true;
								if(num(j,i,k)%8==0) ans=true;
								if(num(i,k,j)%8==0) ans=true;
								if(num(j,k,i)%8==0) ans=true;
								if(num(k,i,j)%8==0) ans=true;
								if(num(k,j,i)%8==0) ans=true;
							}
					}
			}
		} else {
			int alp;
			istringstream(nu) >> alp;
			if(alp%8==0) ans=true;
			int bet=alp%10;
			bet*=10;
			bet+=(alp/10);
			if(bet%8==0) ans=true;
		}
		if(ans) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
