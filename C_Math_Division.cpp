#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MOD = 1e9 + 7;

// Function to compute a^b % mod using exponentiation by squaring
ll pm(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// Function to compute the modular inverse of x modulo mod
ll inv(ll x, ll mod) {
    return pm(x, mod - 2, mod);
}

// Function to compute the expected number of operations
ll solve(int n, string s) {
    if (n == 1) return 0; // Base case: x is already 1

    // Convert binary string to integer x
    ll x = 0;
    for (char c : s) {
        x = (x * 2 + (c - '0')) % MOD;
    }

    // Compute k = x - 2^(n-1), where 2^(n-1) is the smallest n-bit number
    // k represents the offset of x from the smallest n-bit number
    ll k = (x - pm(2LL, n-1, MOD) + MOD) % MOD;

    // Compute the expected number of operations:
    // E(x) = (n-1) + (k / 2^(n-1)) mod MOD
    // Here:
    // - (n-1) is the minimum number of steps to reduce x to 1 (since x has n bits)
    // - (k / 2^(n-1)) accounts for the additional steps due to the offset k
    ll res = (n-1 + k * inv(pm(2LL, n-1, MOD), MOD) % MOD) % MOD;

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; // Number of test cases
    cin >> t;
    while (t--) {
        int n; // Length of the binary string
        cin >> n;
        string s; // Binary string representing x
        cin >> s;

        // Compute and print the expected number of operations
        cout << solve(n, s) << "\n";
    }

    return 0;
}