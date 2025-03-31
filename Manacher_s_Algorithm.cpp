#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// VVI
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll long long
#define SZ(a) (int)a.size()
#define UNIQUE(a) (a).erase(unique(all(a)), (a).end())
#define mp make_pair
#define all(x) x.begin(), x.end()

//Printings & debugging
#define nn '\n'


// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;

#define MAXLEN 1000010
constexpr uint64_t mod = (1ULL << 61) - 1;

const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (mod / 3) + (mod / 3);

uint64_t base_pow[MAXLEN];

int64_t modmul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}

void init() {
    base_pow[0] = 1;
    for (int i = 1; i < MAXLEN; i++) {
        base_pow[i] = modmul(base_pow[i - 1], base);
    }
}

struct PolyHash {
    vector<int64_t> pref;

    PolyHash() {}

    template <typename T>
    PolyHash(const vector<T>& ar) {
        if (!base_pow[0]) init();
        int n = ar.size();
        assert(n < MAXLEN);
        pref.resize(n + 3, 0);

        for (int i = 1; i <= n; i++) {
            pref[i] = modmul(pref[i - 1], base) + ar[i - 1] + 997;
            if (pref[i] >= mod) pref[i] -= mod;
        }
    }

    PolyHash(const string& str) : PolyHash(vector<char>(str.begin(), str.end())) {}

    uint64_t get_hash(int l, int len) {
        int r = l + len - 1;
        int64_t h = pref[r + 1] - modmul(base_pow[len], pref[l]);
        return h < 0 ? h + mod : h;
    }
};

int main() {
    // Input handling
    fast;
    string a;
    cin >> a;

    // Initialize polynomial hashes
    PolyHash hash_a(a);
    reverse(a.begin(), a.end());
    PolyHash hash_b(a);

    // Get length of string
    const int n = (int)a.size();
    uint64_t answ = 0;

    for (int i = 0, j = n - 1; i < n; ++i, --j) {
        // Odd length palindromes
        int low = 0, high = min(n - i, n - j) + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (hash_a.get_hash(i, mid) == hash_b.get_hash(j, mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        answ += low;

        // Even length palindromes
        low = 0, high = min(n - i - 1, n - j) + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (hash_a.get_hash(i + 1, mid) == hash_b.get_hash(j, mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        answ += low;
    }

    // Output result
    cout << answ << "\n";
    return 0;
}
