#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

unsigned long long prime = 1000000007ULL;
unsigned long long bin[1001][1001];
unsigned long long binsum[1001][1001];
int cs[1001][1001];

unsigned long long power(unsigned long long abase, unsigned long long aexp) {
    unsigned long long base = abase;
    unsigned long long exp = aexp;
    unsigned long long res=1;
    while(exp>0ULL) {
       if(exp%2ULL==1ULL) res=(res*base)%prime;
       base=(base*base)%prime;
       exp/=2ULL;
    }
    return res%prime;
}

unsigned long long fast_chi(int n, int m, int c){
    if(c == n){
        if((m+1) % 2 == 0) return 1ULL;
        else return (prime - 1ULL);
    }
    else{
        int lower_limit;
        int upper_limit;
        if((c <= m) && (c <= (n-m+1))){
            lower_limit = 1;
            upper_limit = c;
        }
        else if((c > m) && (c <= (n-m+1))){
            lower_limit = 1;
            upper_limit = m;
        }
        else if((c <= m) && (c > (n-m+1))){
            lower_limit = c - (n - m);
            upper_limit = c;
        }
        else{
            lower_limit = c - (n-m);
            upper_limit = m;
        }
        unsigned long long lower_sum = 0ULL;
        unsigned long long upper_sum = 0ULL;
        unsigned long long answer;
        for(int x = lower_limit; x < (upper_limit + 1); x += 2) lower_sum = (lower_sum + bin[n-c][m-x]) % prime;
        if(lower_limit < upper_limit) for(int x = lower_limit+1; x < (upper_limit + 1); x += 2) upper_sum = (upper_sum + bin[n-c][m-x]) % prime;
        if((lower_limit + 1) % 2 == 0) answer = (lower_sum + ((upper_sum * (prime-1)) % prime)) % prime;
        else answer = (upper_sum + ((lower_sum * (prime-1)) % prime)) % prime;
        unsigned long long banswer = binsum[n-c][m - lower_limit];
        if(upper_limit < m) banswer += (((prime - 1) * binsum[n-c][m - upper_limit - 1]) % prime);
        if(m % 2 == 0)  banswer = (banswer * (prime - 1)) % prime;
        return banswer;
    }

}
unsigned long long chi(int n, int m, int c){
    if(2*m < (n+1)){
        if(c == 1) return bin[n-1][m-1];
        else if(c <= m){
            unsigned long long total = 0ULL;
            for(int i = 0; i < c; i++){
                int x = i+1;
                if((x+1) % 2 == 0) total = (total + bin[n-c][m-x]) % prime;
                else{
                    unsigned long long add = (bin[n-c][m-x] * (prime - 1ULL)) % prime;
                    total = (total + add) % prime;
                }
            }
            return total;
        }
        else if((c > m) && (c <= (n-m+1))){
            unsigned long long total = 0ULL;
            for(int i = 0; i < m; i++){
                int x = i+1;
                if((x+1) % 2 == 0) total = (total + bin[n-c][m-x]) % prime;
                else{
                    unsigned long long add = (bin[n-c][m-x] * (prime - 1ULL)) % prime;
                    total = (total + add) % prime;
                }
            }
            return total;
        }
        else if((c > (n-m+1)) && (c < n)){
            unsigned long long total = 0ULL;
            for(int x = c - (n-m); x < (m+1); x++){
                if((x+1) % 2 == 0) total = (total + bin[n-c][m-x]) % prime;
                else{
                    unsigned long long add = (bin[n-c][m-x] * (prime - 1ULL)) % prime;
                    total = (total + add) % prime;
                }
            }
            return total;
        }
        else{
            if((m+1) % 2 == 0) return 1ULL;
            else return (prime - 1ULL);
        }
    }
    else{
        if(c == 1) return bin[n-1][m-1];
        else if(c <= (n-m+1)){
            unsigned long long total = 0ULL;
            for(int i = 0; i < c; i++){
                int x = i+1;
                if((x+1) % 2 == 0) total = (total + bin[n-c][m-x]) % prime;
                else{
                    unsigned long long add = (bin[n-c][m-x] * (prime - 1ULL)) % prime;
                    total = (total + add) % prime;
                }
            }
            return total;
        }
        else if((c > (n-m+1)) && (c <= m)){
            unsigned long long total = 0ULL;
            for(int x = c - (n-m); x < (c+1); x++){
                if((x+1) % 2 == 0) total = (total + bin[n-c][m-x]) % prime;
                else{
                    unsigned long long add = (bin[n-c][m-x] * (prime - 1ULL)) % prime;
                    total = (total + add) % prime;
                }
            }
            return total;
        }
        else if((c > m) && (c < n)){
            unsigned long long total = 0ULL;
            for(int x = c - (n-m); x < (m+1); x++){
                if((x+1) % 2 == 0) total = (total + bin[n-c][m-x]) % prime;
                else{
                    unsigned long long add = (bin[n-c][m-x] * (prime - 1ULL)) % prime;
                    total = (total + add) % prime;
                }
            }
            return total;
        }
        else{
            if((m+1) % 2 == 0) return 1ULL;
            else return (prime - 1ULL);
        }
    }
}
unsigned long long get_trace(int n, int m, int trial){
    unsigned long long total = 1;
    unsigned long long len_c = 0ULL;
    for(int i = 0; i < 1001; i++){
        int exponent = cs[trial][i];
        if(exponent > 0){
            unsigned long long base = fast_chi(n, m, i);
            unsigned long long ull_exp = (unsigned long long) exponent;
            len_c += ull_exp;
            unsigned long long multiplier = power(base, ull_exp);
            total = (total * multiplier) % prime;
        }
    }
    unsigned long long dimension = fast_chi(n, m, 1);
    total = (total * dimension) % prime;
    total = (total * chi(n, m, n)) % prime;
    unsigned long long divisor = power(dimension, len_c);
    total = (total * power(divisor, prime-2)) % prime;
    return total;
}

unsigned long long get_conjugacy_class_size(int n, int c){
    if(c == 1) return 1ULL;
    else{
        unsigned long long total = bin[n][c];
        for(int i = 1; i < c; i++){
            unsigned long long multiplier = (unsigned long long) i;
            total = (total * multiplier) % prime;
        }
        return total;
    }
}

unsigned long long get_multiplier(int n, int trial){
    unsigned long long long_n = (unsigned long long) n;
    unsigned long long answer = power(long_n, prime - 2ULL);
    for(int i = 0; i < 1001; i++){
        int exponent = cs[trial][i];
        if(exponent > 0){
            unsigned long long long_exp = (unsigned long long) exponent;
            unsigned long long base = get_conjugacy_class_size(n, i);
            answer = (answer * power(base, long_exp)) % prime;
        }
    }
    return answer;
}

unsigned long long get_enumeration(int n, int trial){
    unsigned long long total = 0ULL;
    for(int i = 1; i < (n+1); i++) total = (total + get_trace(n, i, trial)) % prime;
    unsigned long long mult = get_multiplier(n, trial); total = (total * mult) % prime;
    return total;
}

int main() {
    int T; cin>>T;
    for(int i = 0; i < T; i++) for(int j = 0; j < T; j++) cs[i][j] = 0;
    int ns[T]; int ms[T];
    for(int i = 0; i < T; i++){
        int m; cin>>ns[i]>>m;ms[i] = m;
        for(int j = 0; j < m; j++){
            int k;
            cin>>k;
            cs[i][k] += 1;
        }
    }
    int max_n = 0;
    for(int i = 0; i < T; i++) if(ns[i] > max_n) max_n = ns[i];
    for(int i = 0; i < (max_n + 1); i++){
        for(int j = 0; j < (i+1); j++){
            if(j ==0) bin[i][j] = 1ULL;
            else if(j == i) bin[i][j] = 1ULL;
            else bin[i][j] = (bin[i-1][j] + bin[i-1][j-1]) % prime;
        }
    }
    for(int i = 0; i < (max_n + 1); i++){
        for(int j = 0; j < (i+1); j++){
            if(j ==0) binsum[i][j] = 1ULL;
            else {
                unsigned long long adder;
                if(j % 2 == 0) adder = bin[i][j];
                else adder = (bin[i][j] * (prime - 1)) % prime;
                binsum[i][j] = (binsum[i][j-1] + adder) % prime;
            }
        }
    }
    for(int i = 0; i < T; i++){
        unsigned long long answer = get_enumeration(ns[i], i);
        cout<< answer<<endl;;
    }
    return 0;
}
