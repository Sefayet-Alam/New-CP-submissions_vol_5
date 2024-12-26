#include <bits/stdc++.h>

#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define INF(t) (is_same<t, int32_t>::value ? (int)1e9 : (long long)2e18)
#define int long long
#define uint unsigned int
#define endl "\n"

using namespace std;

const int MAXN = 5e5;
vector<vector<int>> pf(MAXN + 1);

void sieve() {
    for(int i = 2; i <= MAXN; i++) {
        if(pf[i].empty()) {
            for(int j = i; j <= MAXN; j += i) {
                pf[j].push_back(i);
            }
        }
    }
}

const int MOD = 998244353;

inline int gcdex(int a, int b, int* p, int* q) {
    if(a == 0) {
        *p = 0;
        *q = 1;
        return b;
    }
    int c, d;
    int g = gcdex(b % a, a, &c, &d);
    *p = d - (b / a) * c;
    *q = c;
    return g;
}

inline int mdsum(int a, int b) {
    return ((a + b) % MOD + MOD) % MOD;
}

inline int mdpro(int a, int b) {
    return (((a % MOD) * (b % MOD)) % MOD + MOD) % MOD;
}

inline int mdexp(int a, int n) {
    if(n == 0) {
        return 1;
    }
    int b= mdexp(a, n / 2);
    b = mdpro(b, b);
    if(n & 1) {
        b = mdpro(a, b);
    }
    return (b % MOD + MOD) % MOD;
}

inline int mdinv(int a) {
    int b, c;
    int g = gcdex(a, MOD, &b, &c);
    if(g != 1) {
        cerr << "ERROR: GCD DOESN'T EXIST!!! VERIFY CODE!!!" << endl;
        return 0;
    }
    return (b % MOD + MOD) % MOD;
}
/// BIT MANIPULATION

#define Set(x, k) (x |= (1LL << k))
#define Unset(x, k) (x &= ~(1LL << k))
#define Check(x, k) (x & (1LL << k))
#define Toggle(x, k) (x ^ (1LL << k))

int popcount(uint x) { return __builtin_popcountll(x); };
int poplow(uint x) { return __builtin_ctzll(x); };
int pophigh(uint x) { return 63 - __builtin_clzll(x); };
void zero() {
    int n, m;
    cin >> n >> m;
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        int k = m / i;
        for(int j = 1; j <= k; j++) {
            int v = 0;
            int z = pf[j].size();
            int smask = (1ll << z);
            for(int mask = 0; mask < smask; mask++) {
                int p = 1;
                for(int b = 0; b < z; b++) {
                    if((mask >> b) & 1) {
                        p *= pf[j][b];    
                    }
                }
                v += ((popcount((uint)mask) & 1) ? -1 : 1) * (k / p);
            }
            ans = mdsum(ans, mdexp(v, n));
        }
    }
    cout << ans << endl;
}

signed main() {
    Precizne

    
    sieve();
    int progress = 1;
    cin >> progress;
    for(int p = 1; p <= progress; p++) {
       
        zero();
    }

   

    return 0;
}