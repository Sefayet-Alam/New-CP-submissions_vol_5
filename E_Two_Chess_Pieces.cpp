#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 10;

vector<int> g[N];
bool reqA[N], reqB[N];
bool hasA[N], hasB[N];
int path[N]; 
int n, d;

void dfs_mark(int u, int p, int depth) {
    path[depth] = u;
    
    if (reqA[u]) {
        int anc_idx = max(0, depth - d);
        reqB[path[anc_idx]] = true;
    }
    if (reqB[u]) {
        int anc_idx = max(0, depth - d);
        reqA[path[anc_idx]] = true;
    }

    for (int v : g[u]) {
        if (v == p) continue;
        dfs_mark(v, u, depth + 1);
    }
}

void dfs_fill(int u, int p) {
    hasA[u] = reqA[u];
    hasB[u] = reqB[u];
    
    for (int v : g[u]) {
        if (v == p) continue;
        dfs_fill(v, u);
        hasA[u] |= hasA[v];
        hasB[u] |= hasB[v];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> d;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int m1, m2, x;
    cin >> m1;
    for (int i = 0; i < m1; i++) {
        cin >> x;
        reqA[x] = true;
    }
    cin >> m2;
    for (int i = 0; i < m2; i++) {
        cin >> x;
        reqB[x] = true;
    }

    reqA[1] = reqB[1] = true;

    dfs_mark(1, 0, 0);

    dfs_fill(1, 0);

    ll ans = 0;
    for (ll i = 2; i <= n; i++) {
        if (hasA[i]) ans += 2;
        if (hasB[i]) ans += 2;
    }

    cout << ans << endl;

    return 0;
}