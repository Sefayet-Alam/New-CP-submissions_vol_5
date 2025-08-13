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

// CONSTANTS
const ll N = 2e5 + 10;
const ll M = 998244353; 


ll FM[N];
vl fib;
int is_initialized = 0;

ll powerMod(ll x, ll y, ll p)
{
    ll res = 1 % p;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

ll inverseMod(ll a, ll x)
{
    return powerMod(a, x - 2, x);
}

void storefib(ll n, ll x)
{
    if (!is_initialized)
    {
        FM[0] = 1 % x;
        for (int i = 1; i < n + 3; i++)
            FM[i] = (FM[i - 1] * i) % x;

        fib.assign(n + 3, 0);
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i <= n + 2; ++i)
        {
            fib[i] = (fib[i - 1] + fib[i - 2]) % x;
        }
        is_initialized = 1;
    }
}

ll factorialMod(ll n, ll x)
{
    return FM[n];
}

ll nCrMod(ll n, ll r, ll x)
{
    if (r < 0 || r > n)
        return 0;
    ll res = factorialMod(n, x);
    ll fr = factorialMod(r, x);
    ll zr = factorialMod(n - r, x);
    res = (res * inverseMod((fr * zr) % x, x)) % x;
    return res;
}

struct Matrix
{
    ll a[2][2];
    Matrix()
    {
        mem(a, 0);
    }
};

int main()
{
    fast;
    ll n, q;
    cin >> n >> q;

    storefib(n, M);

    map<ll, ll> constrnts;

    for (int i = 0; i < q; ++i)
    {
        ll x, y;
        cin >> x >> y;
        if (y == -1)
        {
            constrnts.erase(x);
        }
        else
        {
            constrnts[x] = y;
        }

        map<ll, ll> curconstrnts = constrnts;
        curconstrnts[0] = 0;

        pll dp = {1, 0};

        ll lastpos = 0;
        ll lastval = 0;
        bool f = true;

        for (auto &[pos, val] : curconstrnts)
        {
            if (pos == 0)
                continue;

            ll len = pos - lastpos;
            ll k = val - lastval;

            if (k < 0)
            {
                f = false;
                break;
            }

            Matrix T;
            T.a[0][0] = nCrMod(len - k, k, M);
            T.a[0][1] = nCrMod(len - k, k - 1, M);
            T.a[1][0] = nCrMod(len - k - 1, k, M);
            T.a[1][1] = nCrMod(len - k - 1, k - 1, M);

            pll ndp;
            ndp.first = (dp.first * T.a[0][0] + dp.second * T.a[1][0]) % M;
            ndp.second = (dp.first * T.a[0][1] + dp.second * T.a[1][1]) % M;

            dp = ndp;

            lastpos = pos;
            lastval = val;
        }

        if (!f)
        {
            cout << 0 << nn;
            continue;
        }

        ll flen = n - lastpos;

        ll totans = (dp.first * fib[flen + 2] + dp.second * fib[flen + 1]) % M;

        cout << (totans + M) % M << nn;
    }
    return 0;
}