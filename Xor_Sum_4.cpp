#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    
    long long result = 0;
    for (int k = 0; k < 60; ++k) {
        long long mask = 1LL << k;
        long long cnt = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i] & mask) {
                cnt++;
            }
        }
        long long contribution = (cnt * (N - cnt)) % MOD;
        contribution = (contribution * ((1LL << k) % MOD)) % MOD;
        result = (result + contribution) % MOD;
    }
    
    cout << result << endl;
    return 0;
}

