#include <bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define ull unsigned long long
#define nn '\n'
#define all(x) x.begin(), x.end()

typedef pair<int, ull> pll;
const int INF = 2e9 + 7;

inline int popcount(ull x) { return __builtin_popcountll(x); }
inline int poplow(ull x) { return __builtin_ctzll(x); }
inline int pophigh(ull x) { return 63 - __builtin_clzll(x); }

void solve(int tc) {
    cout << "Case " << tc << ": ";
    int n;
    cin >> n;
    vector<ull> a(n);
    for(int i=0; i<n; ++i) cin >> a[i];

    vector<pll> cur;
    cur.reserve(2000);
    cur.push_back({0, 0});//total cost,last value

    bool possible = true;
    ll allon=(1ULL << 60) - 1;
    for (int i = 0; i < n; i++) {
        ull u = a[i];
        int base = popcount(u);
        int mnm = INF; 
        vector<pll> nxt;
        nxt.reserve(cur.size() * 4);

        for (const auto& p : cur) {
            int c = p.first;
            ull v = p.second;

            if (c >= mnm) break;

            if (u > v) {
                nxt.push_back({c, u});
                mnm = c;
            } else {
                // ~v =1 -> where v is 0
                // u & ~v =1 -> where prev is 0 and a[i] is one

                ull diff = u & ~v;
                int start = 0;
                if (diff) start = pophigh(diff);

                ull avail = ~v;
                if (start) avail &= (1ULL << start);
                // avail &= ((1ULL << 60) - 1);

                ll minaddpar = INF;

                while (avail) {
                    ll bit = poplow(avail);
                    avail &= ~(1ULL << bit);

                    ull nv = (v & (1LL << (bit + 1))) | (1ULL << bit) | (u & ((1ULL << bit) - 1));
                    int add = popcount(nv) - base;

                    if (c + add >= mnm) continue;

                    if (add < minaddpar) {
                        nxt.push_back({c + add, nv});
                        minaddpar = add;
                    }
                }
            }
        }

        if (nxt.empty()) {
            possible = false;
            break;
        }

        sort(all(nxt));
        cur.clear();
        ull min_val = ~0ULL;
        for (const auto& p : nxt) {
            if (p.second < min_val) {
                cur.push_back(p);
                min_val = p.second;
            }
        }
    }

    if (!possible) cout << -1 << nn;
    else cout << cur[0].first << nn;
}

int main() {
    fast;
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) solve(i);
    return 0;
}