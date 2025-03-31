#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>

using namespace std;

typedef unsigned long long ull;

// Generate random base in (before, after) open interval
int gen_base(const int before, const int after) {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt_rand(seed);
    int base = uniform_int_distribution<int>(before + 1, after)(mt_rand);
    return base % 2 == 0 ? base - 1 : base;
}

struct PolyHash {
    static const int mod = (int)1e9 + 123; // prime mod of polynomial hashing
    static vector<int> pow1;                // powers of base modulo mod
    static vector<ull> pow2;                // powers of base modulo 2^64
    static int base;                         // base (point of hashing)

    // Diff between `a` and `b` modulo mod (0 <= a < mod, 0 <= b < mod)
    static inline int diff(int a, int b) {
        return (a -= b) < 0 ? a + mod : a;
    }

    // Variables of class
    vector<int> pref1;  // Hash on prefix modulo mod
    vector<ull> pref2;  // Hash on prefix modulo 2^64

    // Constructor from string
    PolyHash(const string& s)
        : pref1(s.size() + 1, 0), pref2(s.size() + 1, 0) {
        const int n = s.size(); // Firstly calculate the needed power of base
        while ((int)pow1.size() <= n) {
            pow1.push_back(1LL * pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < n; ++i) {
            pref1[i + 1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
            pref2[i + 1] = pref2[i] + s[i] * pow2[i];
        }
    }

    // Polynomial hash of subsequence [pos, pos + len)
    inline pair<int, ull> operator()(const int pos, const int len, const int mxPow = 0) const {
        int hash1 = pref1[pos + len] - pref1[pos];
        ull hash2 = pref2[pos + len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mxPow != 0) {
            hash1 = 1LL * hash1 * pow1[mxPow - (pos + len - 1)] % mod;
            hash2 *= pow2[mxPow - (pos + len - 1)];
        }
        return make_pair(hash1, hash2);
    }
};

// Init static variables of PolyHash class
int PolyHash::base = (int)1e9 + 7;
vector<int> PolyHash::pow1{1};
vector<ull> PolyHash::pow2{1};

// Functions for calculating this sum: 1 + a + a^2 + ... + a^(k-1) by modulo mod and 2^64 in O(log(k))
int sum_int(int a, int k) {
    if (k == 1) {
        return 1;
    } else if (k % 2 == 0) {
        return (1LL + a) * sum_int(1LL * a * a % PolyHash::mod, k / 2) % PolyHash::mod;
    } else {
        return 1 + (a + 1LL) * a % PolyHash::mod * sum_int(1LL * a * a % PolyHash::mod, k / 2) % PolyHash::mod;
    }
}

ull sum_ull(ull a, int k) {
    if (k == 1) {
        return 1;
    } else if (k % 2 == 0) {
        return (1 + a) * sum_ull(a * a, k / 2);
    } else {
        return 1 + a * sum_ull(a, k - 1);
    }
}

int main() {
    string a;
    cin >> a;

    reverse(a.begin(), a.end()); // reverse the string

    // Generate random point of hashing
    PolyHash::base = gen_base(256, PolyHash::mod);

    // Construct hashes on prefixes of substring a
    PolyHash hash(a);

    // Length of string
    const int n = (int)a.size();

    int answ = 0;
    for (int len = 1; len <= n; ++len) {
        // Get polynomial hash
        auto hash1 = hash(0, len); // on prefix a[0...len)
        auto hash2 = hash(0, n);   // on prefix a[0...n)

        // Multiply on sum of geometry progression hash modulo mod
        hash1.first = 1LL * hash1.first * sum_int(PolyHash::pow1[len], n) % PolyHash::mod;
        hash2.first = 1LL * hash2.first * sum_int(PolyHash::pow1[n], len) % PolyHash::mod;

        // Multiply on sum of geometry progression hash modulo 2^64
        hash1.second *= sum_ull(PolyHash::pow2[len], n);
        hash2.second *= sum_ull(PolyHash::pow2[n], len);

        // Compare hashes
        answ += (hash1 == hash2);
    }

    cout << answ << endl;

    return 0;
}
