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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 3e5 + 10;
const ll M = 1e9 + 7;
ll FM[N];
int is_initialized = 0;
ll factorialMod(ll n, ll x)
{
    if (!is_initialized)
    {
        FM[0] = 1 % x;
        for (int i = 1; i < N; i++)
            FM[i] = (FM[i - 1] * i) % x;
        is_initialized = 1;
    }
    return FM[n];
}

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

ll nCrMod(ll n, ll r, ll x)
{
    if (r == 0)
        return 1;
    if (r > n)
        return 0;
    ll res = factorialMod(n, x);
    ll fr = factorialMod(r, x);
    ll zr = factorialMod(n - r, x);
    res = (res * inverseMod((fr * zr) % x, x)) % x;
    return res;
}
ll n, k;
ll dp[N][4];
ll twn;
ll sumn;
ll func(ll i, ll f)
{
    if (i == k)
    {
        return 1;
    }
    if (dp[i][f] != -1)
        return dp[i][f];
    ll ret = 0;
    if (f)
        ret = (ret + (twn * func(i + 1, 1)) % M) % M; // 1 0
    else
    {
        if (n % 2 == 0)
        {
            ret = (ret + func(i + 1, 1)) % M;              // 0 - 1 (xor value - and value)
            ret = (ret + (sumn * func(i + 1, f)) % M) % M; // 0 - 0
        }
        else
        {
            ret = (ret + func(i + 1, f)) % M;              // 1 - 1
            ret = (ret + (sumn * func(i + 1, f)) % M) % M; // 0 - 0
        }
    }

    return dp[i][f] = ret % M;
}
int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    cin >> t;

    while (t--)
    {
        cin >> n >> k;
        for (ll i = 0; i <= k + 2; i++)
        {
            mem(dp[i], -1);
        }
        sumn = 0;
        for (ll i = 0; i < n; i += 2)
        {
            sumn = (sumn + nCrMod(n, i, M)) % M;
        }
        twn = powerMod(2LL, n, M);

        // deb2(n,k);
        ll ans = func(0, 0);
        cout << ans << nn;
    }

    return 0;
}
