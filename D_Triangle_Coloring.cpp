#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 200005; // Assuming n ≤ 200000

vector<int> fact(MAXN), invFact(MAXN);

// Fast modular exponentiation (a^b % mod)
int modPow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void precomputeFactorials(int n, int mod) {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    invFact[n] = modPow(fact[n], mod - 2, mod);
    for (int i = n - 1; i > 0; i--) {
        invFact[i] = invFact[i + 1] * (i + 1) % mod;
    }
}

// Compute nCr % MOD using precomputed factorials
int binomialCoefficient(int n, int r, int mod) {
    if (r > n || r < 0) return 0;
    return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
}

// Solve the problem
void solve() {
    int n;
    cin >> n;
    vector<int> weights(n);

    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    int num_triples = n / 3;
    vector<int> contrib(num_triples);

    for (int i = 0; i < num_triples; i++) {
        int w1 = weights[3 * i], w2 = weights[3 * i + 1], w3 = weights[3 * i + 2];

        if (w1 == w2 && w2 == w3) {
            contrib[i] = 3;  // All edges are the same
        } else if (w1 != w2 && w2 != w3 && w1 != w3) {
            contrib[i] = 1;  // All edges are different
        } else {
            int max_w = max({w1, w2, w3});
            int count_max = (w1 == max_w) + (w2 == max_w) + (w3 == max_w);

            if (count_max == 2) {
                contrib[i] = 1;
            } else {
                contrib[i] = 2;
            }
        }
    }

    // Compute binomial coefficient C(n/3, n/6) % MOD
    int result = binomialCoefficient(num_triples, num_triples / 2, MOD);

    // Multiply by contribution values
    for (int c : contrib) {
        result = result * c % MOD;
    }

    cout << result << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    precomputeFactorials(MAXN - 1, MOD);  // Precompute factorials up to MAXN

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
