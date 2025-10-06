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


// CONSTANTS
const ll N = 8e5+10;
#define ll long long int
#define lc ((n) << 1)
#define rc ((n) << 1 | 1)
#define pb push_back

typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update> pds;

ll n;

vector<ll> arr(N);
pds mst[N];

void init(ll pp)
{
    for (ll i = 0; i < 4 * pp; i++)
    {
        mst[i].clear();
    }
}

void build(ll n, ll b, ll e)
{
    if (b == e)
    {
        mst[n].insert({arr[b], b});
        return;
    }
    for (ll i = b; i <= e; i++)
        mst[n].insert({arr[i], i});

    ll mid = (b + e) / 2;
    build(lc, b, mid);
    build(rc, mid + 1, e);
}

ll query(ll n, ll b, ll e, ll i, ll j, ll v, ll idx)
{
    if (b > j or e < i)
        return 0;
    if (b >= i and e <= j)
    {
        ll k = mst[n].order_of_key({v, idx});
        return k;
    }
    ll mid = (b + e) / 2;
    return query(lc, b, mid, i, j, v, idx) + query(rc, mid + 1, e, i, j, v, idx);
}

void update(ll n, ll b, ll e, ll i, ll v, ll nw)
{
    if (i < b or e < i)
        return;
    if (b == i and e == i)
    {
        mst[n].erase(mst[n].find({v, i}));
        mst[n].insert({nw, i});
        return;
    }
    ll mid = (b + e) / 2;
    update(lc, b, mid, i, v, nw);
    update(rc, mid + 1, e, i, v, nw);
    mst[n].erase(mst[n].find({v, i}));
    mst[n].insert({nw, i});
}

bool cmp(pll a, pll b)
{
    if (a.first != b.first)
        return a.first > b.first;
    return a.second < b.second;
}
int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    // cin >> t;

    while (t--)
    {
        cin >> n;
        init(n);
        vector<ll> vec(n);
        for(ll i=0;i<n;i++) cin>>vec[i];
        vector<pll> pars;
        for (ll i = 0; i < n; i++)
        {
            pars.push_back({vec[i], i});
        }
        sort(all(pars), cmp);
        // for (auto it : pars)
        //     deb(it);
        ll m;
        cin >> m;
        

        for (ll i = 1; i <= n; i++)
        {
            arr[i] = pars[i - 1].second;
        }
        build(1,1,n);
        while (m--)
        {
            ll k, x;
            cin >> k >> x;
            // deb2(k,x);
            ll l = 1, r = k;
            ll low = mst[1].find_by_order(0)->first, high = mst[1].find_by_order(n - 1)->first, mid, ans;
            // binary search to find the x-th number

            while (low <= high)
            {
                mid = low + high >> 1;
                ll k = query(1, 1, n, l, r, mid, n+2); 
                if (k >= x)
                {
                    ans = mid;
                    high = mid - 1;
                }
                else
                    low = mid + 1;
            }
            // deb2(ans,vec[ans]);
            cout<<vec[ans]<<nn;
        }
    }

    return 0;
}
