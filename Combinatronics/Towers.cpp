#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

#define REP(i,n) for (int i = 1; i <= n; i++)
typedef long long ll;
typedef vector<vector<ll> > matrix;
const ll MOD = 1000000007;
const int K = 15;

// computes A * B
matrix mul(matrix A, matrix B)
{
    matrix C(K+1, vector<ll>(K+1));
    REP(i, K) REP(j, K) REP(k, K)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

// computes A ^ p
matrix pow(matrix A, ll p)
{
    if (p == 1)
        return A;
    if (p % 2)
        return mul(A, pow(A, p-1));
    matrix X = pow(A, p/2);
    return mul(X, X);
}
// Complete the solve function below.
int solve(long n, vector<int> heights) {
    matrix T(K+1, vector<ll>(K+1));
    REP(i, K - 1)
        T[i][i + 1] = 1;
    for (auto h : heights)
        T[K][K - h + 1]++;

    vector<ll> F1(K+1);
    F1[0] = 1;
    REP(i, K)
        for (auto h : heights){
            if (i >= h)
                F1[i] += T[K][K - h + 1] * F1[i - h];
        }

    if (n == 1)
        return (2 * F1[1]) % MOD;

    T = pow(T, n - 1);

    ll res = 0;
    REP(i, K)
        res = (res + T[1][i] * F1[i]) % MOD;
    return (2 * res) % MOD;

}

int main(){
    ofstream fout(getenv("OUTPUT_PATH"));

    long n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int heights_count;
    cin >> heights_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string heights_temp_temp;
    getline(cin, heights_temp_temp);

    vector<string> heights_temp = split_string(heights_temp_temp);

    vector<int> heights(heights_count);

    for (int i = 0; i < heights_count; i++) {
        int heights_item = stoi(heights_temp[i]);

        heights[i] = heights_item;
    }

    int result = solve(n, heights);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
