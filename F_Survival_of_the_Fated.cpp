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

// Printings & debugging
#define nn '\n'

#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 3e5 + 10;
const ll M = 998244353;


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
        ll n;
        cin >> n;
        vector<ll> vec(n);
        for (ll i = 0; i < n; i++)
            cin >> vec[i];
        sort(vec.rbegin(), vec.rend());
        ll sum = 0;
        vector<ll> suff(n, 0);
        suff[n - 1] = vec[n - 1];
        for (ll i = n - 2; i >= 0; i--)
        {
            suff[i] += suff[i + 1];
            suff[i] %= M;
            suff[i] += vec[i];
            suff[i] %= M;
        }
        for (ll i = 0; i < n-1; i++)
        {
            ll rem = (n - (i + 1))%M;
            ll pls = (rem * vec[i])%M;
            ll tomin = (suff[i + 1]);
            ll now = (pls - tomin + M) % M;
            sum = (sum + now) % M;
        }
        ll mult =(n-1);
        for (ll i = 1; i <= n - 1; i++)
        {
            mult = (mult * i) % M;
        }
        mult = (mult * 2) % M;
        ll totmatch = n - 1;
        for (ll i = 1; i <= n; i++)
        {
            totmatch = (totmatch * i) % M;
        }
        mult = (mult * inverseMod(totmatch, M)) % M;
        ll ans = (sum * mult) % M;
        cout << ans << nn;
    }

    return 0;
}
