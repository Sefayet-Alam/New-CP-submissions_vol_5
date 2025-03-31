#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fast ios::sync_with_stdio(false); cin.tie(0);
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
    vector<int64_t> pref, suff;

    PolyHash() {}

    template <typename T>
    PolyHash(const vector<T>& ar) {
        if (!base_pow[0]) init();

        int n = ar.size();
        assert(n < MAXLEN);
        pref.resize(n + 3, 0), suff.resize(n + 3, 0);

        for (int i = 1; i <= n; i++) {
            pref[i] = modmul(pref[i - 1], base) + ar[i - 1] + 997;
            if (pref[i] >= mod) pref[i] -= mod;
        }

        for (int i = n; i >= 1; i--) {
            suff[i] = modmul(suff[i + 1], base) + ar[i - 1] + 997;
            if (suff[i] >= mod) suff[i] -= mod;
        }
    }

    PolyHash(const char* str) : PolyHash(vector<char>(str, str + strlen(str))) {}
    PolyHash(string str) : PolyHash(vector<char>(str.begin(), str.end())) {}

    uint64_t get_hash(int l, int r) {
        int64_t h = pref[r + 1] - modmul(base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + mod : h;
    }

    uint64_t rev_hash(int l, int r) {
        int64_t h = suff[l + 1] - modmul(base_pow[r - l + 1], suff[r + 2]);
        return h < 0 ? h + mod : h;
    }
};

set<string> words;
ll dp[101][101];
string s;

ll func(ll l, ll r, PolyHash& hs) {
    if (l > r)
        return 0;
    if (dp[l][r] != -1) return dp[l][r]; // Use memoization

    ll ret = 0;
    set<ll> mex;
    
    for (ll i = l; i <= r; i++) {
        for (ll j = i; j <= r; j++) {
            string sub = s.substr(i, j - i + 1);
            
            if (words.find(sub) != words.end()) {
                mex.insert(func(l, i - 1, hs) ^ func(j + 1, r, hs));
            }
        }
    }

    for (auto it : mex) {
        if (it == ret) ret++;
        else break;
    }
    
    return dp[l][r] = ret;  // Store result in dp table
}

int main() {
    fast;
    ll t;
    cin >> t;

    while (t--) {
        cin >> s;
        PolyHash hs(s);
        ll n = s.size();
        ll k;
        cin >> k;
        words.clear();  // Clear previous test case words

        for (ll i = 0; i < k; i++) {
            string p;
            cin >> p;
            words.insert(p);
        }

        memset(dp, -1, sizeof(dp)); // Reset DP array for new test case

        ll ans = func(0, n - 1, hs);
        if(ans) cout<<"Teddy"<<endl;
        else cout<<"Tracy"<<endl;
    }

    return 0;
}
