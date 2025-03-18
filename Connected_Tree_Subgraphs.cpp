#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ll long long

ll MOD = 1000000007;

ll pow(ll b, ll e)
{
    ll be = b;
    ll res = 1;
    for (ll i = 0; i < 32; i++)
    {
        if (e & (1 << i))
        {
            res = (res*be)%MOD;
        }
        be = (be*be)%MOD;
    }
    return res;
}

ll mdiv(ll a, ll b)
{
    return (a*pow(b, MOD-2))%MOD;
}

ll F[100001];

int fact(int x)
{
    return (F[x] == 0 ? (F[x] = fact(x-1)*x) : F[x]);
}

int N;

vector<pair<ll, ll>> DP[100001];
vector<int> G[100001];
vector<int> NID[100001];
int S[100001];

void dfs(int p, int pp)
{
    S[p] = 1;
    for (int ch : G[p])
    {
        if (ch != pp)
        {
            dfs(ch, p);
            S[p] += S[ch];
        }
    }
}

int s(int from, int p)
{
    if (S[from] > S[p])
        return S[p];
    else
        return N - S[from];
}

pair<ll,ll> dp(int p, int ne)
{
    auto& res = DP[p][ne];
    if (res.second != -1)
        return res;
    //cerr << "Starting calc DP " << p << " " << ne<< endl;
    res.second = 1;
    if (ne == G[p].size())
    {
        res.first = fact(N-1);
    }
    else
    {
        res.first = fact(s(G[p][ne], p)-1);
    }
    for (int i = 0; i < G[p].size(); i++)
    {
        if (i == ne)
            continue;
        res.second *= fact(s(p, G[p][i]));
        res.second %= MOD;
        res.first  *= dp(G[p][i], NID[p][i]).first;
        res.second *= dp(G[p][i], NID[p][i]).second;
        res.first  %= MOD;
        res.second %= MOD;
    }
    //cerr << "DP " << p << " " << ne << " == " << res.first << "/" <<res.second << endl;
    return res;
}

int main()
{
    F[0] = 1;
    ios::sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        DP[i].push_back({-1,-1});
    }
    for(int i = 0; i < N-1; i++)
    {
        int u, v;
        cin >> u >> v;
        NID[u].push_back(G[v].size());
        NID[v].push_back(G[u].size());
        G[u].push_back(v);
        G[v].push_back(u);
        DP[u].push_back({-1, -1});
        DP[v].push_back({-1, -1});
    }
    dfs(1, 0);
    ll res = 0;
    for (int i = 1; i <= N; i++)
    {
        dp(i, G[i].size());
        res += mdiv(DP[i][G[i].size()].first, DP[i][G[i].size()].second);
        res %= MOD;
    }
    cout << res << endl;
}
