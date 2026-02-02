#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

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

#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")

inline ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a * b / GCD(a, b); }
inline double logb(ll base, ll num) { return (double)log(num) / (double)log(base); }

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
using orderedset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using orderedmultiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using orderedmap = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using orderedmultimap = tree<T, R, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 200005;

vl g[N];
ll pr[N], sz[N], dp[N], ht[N], gv[N], cd[N], sd[N];

void getinf(ll u)
{
    sz[u] = 1;
    ht[u] = 0;
    for (auto v : g[u])
    {
        dp[v] = dp[u] + 1;
        getinf(v);
        sz[u] += sz[v];
        ht[u] = max(ht[u], ht[v] + 1);
    }
}

vl solve(ll u)
{
    ll hvy = -1;
    for (auto v : g[u])
    {
        if (hvy == -1 || ht[v] > ht[hvy])
            hvy = v;
    }
    if (hvy == -1)
    {
        gv[u] = 1;
        return {1};
    }
    vl res = solve(hvy);
    gv[u] = gv[hvy];
    res.push_back(1);
    gv[u] += 1;
    for (auto v : g[u])
    {
        if (v == hvy)
            continue;
        vl tmp = solve(v);
        ll tsz = SZ(tmp);
        ll rsz = SZ(res);
        for (ll i = 0; i < tsz; ++i)
        {
            ll idx1 = tsz - 1 - i;
            ll idx2 = rsz - 1 - (i + 1);
            ll vold = res[idx2];
            ll vnew = vold + tmp[idx1];
            res[idx2] = vnew;
            gv[u] += vnew * vnew - vold * vold;
        }
    }
    return res;
}

void clean(ll n)
{
    for (ll i = 1; i <= n; i++)
    {
        g[i].clear();
        pr[i] = (i < n ? i + 1 : 0);
        sz[i] = 0;
        dp[i] = 0;
        ht[i] = 0;
        gv[i] = 0;
    }
}

int main()
{
    fast;
    ll t;
    if (!(cin >> t)) return 0;
    while (t--)
    {
        ll n, m;
        cin >> n >> m;
        clean(n);
        for (int i = 0; i < m; i++)
        {
            ll u, v;
            cin >> u >> v;
            if (u < n) pr[u] = max(pr[u], v);
        }
        for (ll i = 1; i < n; i++)
        {
            g[pr[i]].push_back(i);
        }
        dp[n] = 0;
        getinf(n);
        ll mx = 0;
        for (ll i = 1; i <= n; i++)
            mx = max(mx, dp[i]);
        for (ll i = 0; i <= mx; i++)
            cd[i] = 0;
        for (ll i = 1; i <= n; i++)
            cd[dp[i]]++;
        for (ll i = 0; i <= mx + 1; i++)
            sd[i] = 0;
        for (ll i = mx; i >= 0; i--)
            sd[i] = sd[i + 1] + cd[i];
        ll ans1 = 0;
        for (ll i = 1; i <= n; i++)
        {
            ans1 += dp[i] * sd[dp[i]];
        }
        solve(n);
        ll ans2 = 0;
        for (ll i = 1; i < n; i++)
        {
            ans2 += sz[i] * sz[i] + gv[i];
        }
        cout << ans1 - ans2 / 2 << nn;
    }
    return 0;
}