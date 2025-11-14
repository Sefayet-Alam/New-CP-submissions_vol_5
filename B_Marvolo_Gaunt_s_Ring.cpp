#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()
#define nn '\n'

const ll N = 1e5 + 10;
const ll M = 5e18 + 7;

vector<ll> vec(N);
ll n, p, q, r;
ll dp[N][4];

ll func(ll n)
{
    dp[0][0] = p * vec[0];
    for (int i = 1; i < n; i++)
        dp[i][0] = max(dp[i - 1][0], p * vec[i]);

    dp[0][1] = dp[0][0] + q * vec[0];
    for (int i = 1; i < n; i++)
        dp[i][1] = max(dp[i - 1][1], dp[i][0] + q * vec[i]);

    dp[0][2] = dp[0][1] + r * vec[0];
    for (int i = 1; i < n; i++)
        dp[i][2] = max(dp[i - 1][2], dp[i][1] + r * vec[i]);

    return dp[n - 1][2];
}

int main()
{
    fast;
    cin >> n >> p >> q >> r;
    vec.resize(n);
    for (int i = 0; i < n; i++) cin >> vec[i];
    ll ans = func(n);
    cout << ans << nn;
    return 0;
}
