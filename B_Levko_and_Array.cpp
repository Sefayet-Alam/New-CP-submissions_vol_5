#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

const ll M = 1e9 + 7;
ll n, k;
vector<ll> a;
bool func(ll x)
{
    vector<ll> L(n), R(n);
    for (ll i = 0; i < n; i++)
    {
        L[i] = a[i] - i * x;
        R[i] = a[i] + i * x;
    }

    // Coordinate compress R
    vector<ll> comp = R;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    auto getR = [&](ll v)
    {
        return (int)(lower_bound(comp.begin(), comp.end(), v) - comp.begin()) + 1;
    };

    // Sort indices by L descending, R ascending
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j)
         {
        if (L[i] != L[j]) return L[i] > L[j];
        return R[i] < R[j]; });

    // Fenwick Tree (BIT) for prefix maximum over compressed R
    int m = comp.size();
    vector<ll> bit(m + 2, 0);
    auto update = [&](int i, ll v)
    {
        for (; i <= m; i += i & -i)
            bit[i] = max(bit[i], v);
    };
    auto query = [&](int i)
    {
        ll ans = 0;
        for (; i > 0; i -= i & -i)
            ans = max(ans, bit[i]);
        return ans;
    };

    vector<ll> dp(n, 0);
    ll bestAll = 0;

    for (int id : idx)
    {
        int rpos = getR(R[id]);
        ll best = query(rpos);
        dp[id] = best + 1;
        update(rpos, dp[id]); // We are building it over the sorted coordinate space of R[i] values
        bestAll = max(bestAll, dp[id]);
    }

    return n - bestAll <= k;
}
int main()
{
    fast;
    cin >> n >> k;
    a.resize(n);
    for (ll i = 0; i < n; i++)
        cin >> a[i];

    ll lo = -1, hi = 2 * M;
    while (hi - lo > 1)
    {
        ll mid = (lo + hi) / 2;
        if (func(mid))
            hi = mid;
        else
            lo = mid;
    }
    cout << hi << '\n';
    return 0;
}
