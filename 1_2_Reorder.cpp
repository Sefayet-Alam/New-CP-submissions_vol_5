#include <bits/stdc++.h>
#define int long long int
using namespace std;

const int mod = 998244353;
template <class T>
class BIT
{
public:
    int n;
    vector<T> f;
    BIT(int n) : n(n)
    {
        f.resize(n + 1, (T)0);
    }
    BIT(const vector<T> &a)
    { // O(n)
        n = a.size(xw);
        f.assign(n + 1, (T)0);
        for (int i = 1; i <= n; i++)
        {
            f[i] += a[i - 1];
            if (i + (i & -i) <= n)
            {
                f[i + (i & -i)] += f[i];
            }
        }
    }
    void update(int p, T v)
    {
        while (p <= n)
            f[p] = (f[p] % mod + v % mod) % mod, p += p & -p;
    }
    T pref(int p)
    {
        T ret = 0;
        while (p)
            ret = (ret % mod + f[p] % mod) % mod, p -= p & -p;
        return ret;
    }
    T range(int l, int r)
    {
        return (pref(r) - pref(l - 1) + mod) % mod;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> dp(n + 2, 0);
    dp[n + 1] = 1;
    BIT<int> bt(n + 3);
    for (int i = n; i >= 1; i--)
    {
        if (a[i] == 2)
        {
            dp[i] = dp[i + 1];
            bt.update(i, dp[i]);
        }
        else
        {
            dp[i] = dp[i + 1] + bt.range(i + 2, n);
            dp[i] %= mod;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << dp[i] << " ";
    cout << "\n";
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    for (int cs = 1; cs <= t; cs++)
    {
        // cout << "Case " << cs << ": ";
        solve();
    }
    return 0;
}