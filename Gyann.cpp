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
#define nn '\n'
#define all(x) x.begin(), x.end()

struct SegTree
{
    int n;
    vector<ll> mn, mx;
    void init(int sz)
    {
        n = 1;
        while (n < sz)
            n <<= 1;
        mn.assign(2 * n, LLONG_MAX);
        mx.assign(2 * n, LLONG_MIN);
    }
    void build(vector<ll> &pref)
    {
        for (int i = 0; i < (int)pref.size(); i++)
            mn[i + n] = mx[i + n] = pref[i];
        for (int i = n - 1; i >= 1; i--)
        {
            mn[i] = min(mn[2 * i], mn[2 * i + 1]);
            mx[i] = max(mx[2 * i], mx[2 * i + 1]);
        }
    }
    ll getMin(int l, int r)
    {
        ll res = LLONG_MAX;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = min(res, mn[l++]);
            if (r & 1)
                res = min(res, mn[--r]);
        }
        return res;
    }
    ll getMax(int l, int r)
    {
        ll res = LLONG_MIN;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = max(res, mx[l++]);
            if (r & 1)
                res = max(res, mx[--r]);
        }
        return res;
    }
    // find farthest right index where min(pref[L..x]) >= lim
    int maxRightSafe(int L, ll lim)
    {
        int lo = L, hi = n; // pref size ≤ n
        while (lo < hi)
        {
            int mid = (lo + hi + 1) / 2;
            if (getMin(L, mid + 1) >= lim)
                lo = mid;
            else
                hi = mid - 1;
        }
        return lo;
    }
    // symmetric for left side: farthest left where min(pref[x..R]) >= lim
    int maxLeftSafe(int R, ll lim)
    {
        int lo = 0, hi = R;
        while (lo < hi)
        {
            int mid = (lo + hi) / 2;
            if (getMin(mid, R + 1) >= lim)
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo;
    }
};

int main()
{
    fast;
    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        vector<ll> pref(n + 2, 0);
        for (int i = 1; i <= n; i++)
            pref[i] = pref[i - 1] + a[i];
        SegTree st;
        st.init(n + 2);
        st.build(pref);

        while (q--)
        {
            int k;
            cin >> k;
            ll S = a[k];
            if (S < 0)
            {
                cout << "NO" << nn;
                continue;
            }

            int L = k, R = k;
            bool ok = 0;
            while (1)
            {
                if (L == 1 || R == n)
                {
                    ok = 1;
                    break;
                }
                bool moved = 0;
                // try right
                int rmax = st.maxRightSafe(R, pref[R] - S);
                if (rmax > R)
                {
                    ll gain = st.getMax(R, rmax + 1) - pref[R];
                    if (gain > 0)
                    {
                        S += gain;
                        R = rmax;
                        moved = 1;
                        continue;
                    }
                }
                // try left
                int lmin = st.maxLeftSafe(L - 1, pref[L - 1] - S);
                if (lmin < L - 1)
                {
                    ll gain = st.getMax(lmin, L) - pref[L - 1];
                    if (gain > 0)
                    {
                        S += gain;
                        L = lmin + 1;
                        moved = 1;
                        continue;
                    }
                }
                if (!moved)
                    break;
            }
            cout << (ok ? "YES" : "NO") << nn;
        }
    }
    return 0;
}
