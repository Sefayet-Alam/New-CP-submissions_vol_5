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
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()

// Printings & debugging
#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")

/// INLINE FUNCTIONS
inline ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a * b / GCD(a, b); }
inline double logb(ll base, ll num) { return (double)log(num) / (double)log(base); }

/// Data structures
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vvl;
template <typename T>
using PQ = priority_queue<T>;
template <typename T>
using QP = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using ordered_multimap = tree<T, R, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;


const ll N = 2e5 + 10;

vl get_distances(ll start, ll n, const vvl& g) {
    vl dist(n, -1);
    queue<ll> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    fast;
    ll t;
    if (!(cin >> t)) return 0;

    while (t--) {
        ll n, a, b, da, db;
        cin >> n >> a >> b >> da >> db;
        a--; b--; 

        vvl g(n);
        for (ll i = 0; i < n - 1; i++) {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vl distA = get_distances(a, n, g);
        ll dist_ab = distA[b];
        vl dist0 = get_distances(0, n, g);
        ll u_diam = 0;
        for (ll i = 0; i < n; i++) {
            if (dist0[i] > dist0[u_diam]) u_diam = i;
        }
        vl dist_diam = get_distances(u_diam, n, g);
        ll diameter = 0;
        for (ll i = 0; i < n; i++) {
            diameter = max(diameter, dist_diam[i]);
        }

        if (dist_ab <= da || db <= 2 * da || diameter <= 2 * da) {
            cout << "Alice" << nn;
        } else {
            cout << "Bob" << nn;
        }
    }

    return 0;
}