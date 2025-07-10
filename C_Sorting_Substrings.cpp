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



typedef pair<ll, ll> pll;
typedef vector<ll> vl;


string s;
vl c, p, lcp;
void countSort(vector<ll> &p, vector<ll> &c)
{
    ll n = p.size();
    vector<ll> cnt(n);
    for (auto it : c)
        cnt[it]++;
    vector<ll> p_new(n), pos(n);
    pos[0] = 0;
    for (ll i = 1; i < n; i++)
        pos[i] = pos[i - 1] + cnt[i - 1];
    for (auto it : p)
    {
        ll i = c[it];
        p_new[pos[i]] = it;
        pos[i]++;
    }
    p = p_new;
}
void SuffixArray_LCP(string &s)
{
    s += " ";
    ll n = s.size();
    vector<pair<char, ll>> suf(n);
    for (ll i = 0; i < n; i++)
        suf[i] = {s[i], i};
    sort(suf.begin(), suf.end());
    // vector<ll> p(n), c(n);
    p.resize(n),c.resize(n);
    for (ll i = 0; i < n; i++)
        p[i] = suf[i].second;
    c[p[0]] = 0;
    for (ll i = 1; i < n; i++)
    {
        if (suf[i].first == suf[i - 1].first)
            c[p[i]] = c[p[i - 1]];
        else
            c[p[i]] = c[p[i - 1]] + 1;
    }
    ll k = 0;
    while ((1 << k) < n)
    {
        for (ll i = 0; i < n; i++)
            p[i] = (p[i] - (1 << k) + n) % n;
        countSort(p, c);
        vector<ll> c_new(n);
        c_new[p[0]] = 0;
        for (ll i = 1; i < n; i++)
        {
            pair<ll, ll> last = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair<ll, ll> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            if (cur == last)
                c_new[p[i]] = c_new[p[i - 1]];
            else
                c_new[p[i]] = c_new[p[i - 1]] + 1;
        }
        c = c_new;
        k++;
    }

    lcp.resize(n);
    k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        ll pi = c[i], j = p[pi - 1];
        while (s[i + k] == s[j + k])
            k++;
        lcp[pi] = k;
        k = max(k - 1, 0LL);
    }
    // return {c, p, lcp};
}

struct segment_tree
{
    ll size;
    vector<ll> tree;
    // INITIALIZATION
    void init(ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        tree.assign(2 * size, 0LL);
    }
    ll merge(ll a, ll b)
    {
        return min(a,b);
    }

    void build(vector<ll> &a, ll x, ll lx, ll rx)
    {
        // linear time
        if (rx - lx == 1)
        {
            if (lx < a.size())
            {
                tree[x] = a[lx];
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<ll> &a)
    {
        // linear time
        build(a, 0, 0, size);
    }
    // SET AND GET
    void set(ll i, ll val, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            // leaf
            tree[x] = val;
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, val, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, val, 2 * x + 2, m, rx);
        }
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(ll i, ll val)
    {
        // assigns val at index i
        set(i, val, 0, 0, size);
    }


    /// RANGE SUM
    ll sum(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (lx >= r || l >= rx)
        {
            return INT_MAX;
        }
        if (lx >= l && rx <= r)
        {
            return tree[x];
        }
        ll m = (lx + rx) / 2;
        ll s1 = sum(l, r, 2 * x + 1, lx, m);
        ll s2 = sum(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }
    ll sum(ll l, ll r)
    {
        // returns sum from l to r-1
        return sum(l, r, 0, 0, size);
    }
} sg;



bool cmp(pll a, pll b)
{
    if (a.first == b.first)
        return a.second < b.second;
    ll suf1 = c[a.first], suf2 = c[b.first];
    ll len1 = a.second - a.first + 1, len2 = b.second - b.first + 1;
    ll cp = sg.sum(min(suf1, suf2)+1, max(suf1, suf2)+1); // common part
    if (len1 <= cp && len2 <= cp)
    {
        if (len1 == len2)
            return a.first < b.first;
        else
            return len1 < len2;
    }
    else if (len1 <= cp)
        return 1;
    else if (len2 <= cp)
        return 0;
    else if(suf1>suf2) return 0;
    return 1;
}

int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    cin >> s;
    ll m = s.size();
    sg.init(2*m + 100);
    SuffixArray_LCP(s);
    for (ll i = 0; i < lcp.size(); i++)
        sg.set(i, lcp[i]);

    // for(ll i=0;i<lcp.size();i++) deb(sg.sum(i,i+1));
    vector<pll> pars;
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        ll x, y;
        cin >> x >> y;
        x--, y--;
        pars.push_back({x, y});
    }
    sort(all(pars), cmp);
    for (auto it : pars)
    {
        cout << it.first + 1 << " " << it.second + 1 << nn;
    }

    return 0;
}

