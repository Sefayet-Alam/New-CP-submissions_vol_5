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

inline ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a * b / GCD(a, b); }

typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vvl;

const ll N = 2e5 + 10;
const int MV = 1000005;

int cnt[MV + 20];
int P[MV + 20];
bool sk[MV + 20];

int main()
{
    fast;
    int t;
    cin >> t;
    ll tno=1;
    while (t--)
    {
    
        ll n;
        cin >> n;
        ll mx = 0;
        ll sm = 0;
        vl a(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            if (a[i] > mx)
                mx = a[i];
            sm += (ll)a[i] * a[i];
        }

        mem(cnt, 0);
        mem(P, 0);
        mem(sk, 0);

        for (ll x : a)
            cnt[x]++;
        for (ll i = 1; i <= mx + 1; ++i)
            P[i] = P[i - 1] + cnt[i];

        ll mn = -1;
        ll res = 1;

        for (ll g = 2; g <= mx + 1; ++g)
        {
            ll cur = 0;
            for (ll k = 1;; ++k)
            {
                ll L = (k - 1) * g;
                if (L > mx)
                    break;
                ll R = k * g;
                ll lim = min(R, mx + 1);
                ll c = P[lim] - P[L];
                if (c > 0)
                    cur += (ll)c * R * R;
            }
            ll cst = cur - sm;

            if (mn == -1 || cst < mn)
            {
                mn = cst;
                res = g;
            }
            else if (cst == mn)
            {
                res = max(res, g);
            }
        }
        cout << "Case " << tno++ << ": " << mn << " " << res << nn;
    }
    return 0;
}