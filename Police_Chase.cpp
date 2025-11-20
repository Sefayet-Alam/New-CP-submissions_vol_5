#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll,ll>
const ll M = 1e9 + 7;
const ll inf = M;

const ll maxnodes = 5005; // careful with memory
ll nodes = maxnodes, src, dest;
ll dist[maxnodes], q[maxnodes], work[maxnodes];

struct Edge {
    ll to, rev;
    ll f, cap;
};

vector<Edge> g[maxnodes];

void addEdge(ll s, ll t, ll cap) {
    Edge a = {t, (ll)g[t].size(), 0, cap};
    Edge b = {s, (ll)g[s].size(), 0, 0};
    g[s].push_back(a);
    g[t].push_back(b);
}

bool dinic_bfs() {
    fill(dist, dist + nodes, -1);
    dist[src] = 0;
    ll index = 0;
    q[index++] = src;

    for (ll i = 0; i < index; i++) {
        ll u = q[i];
        for (Edge &e : g[u]) {
            if (dist[e.to] < 0 && e.f < e.cap) {
                dist[e.to] = dist[u] + 1;
                q[index++] = e.to;
            }
        }
    }
    return dist[dest] >= 0;
}

ll dinic_dfs(ll u, ll f) {
    if (u == dest) return f;

    for (ll &i = work[u]; i < (ll) g[u].size(); i++) {
        Edge &e = g[u][i];
        if (e.f < e.cap && dist[e.to] == dist[u] + 1) {
            ll flow = dinic_dfs(e.to, min(f, e.cap - e.f));
            if (flow > 0) {
                e.f += flow;
                g[e.to][e.rev].f -= flow;
                return flow;
            }
        }
    }
    return 0;
}

ll maxFlow(ll _src, ll _dest) {
    src = _src; dest = _dest;
    ll result = 0;
    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (ll delta = dinic_dfs(src, inf))
            result += delta;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    nodes = n + 1;
    src = 1; dest = n;

    map<pll,bool> oadj; // store original edges

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        addEdge(u, v, 1);
        addEdge(v, u, 1);
        oadj[{u,v}] = oadj[{v,u}] = true;
    }

    maxFlow(src, dest);

    // BFS to find reachable nodes in residual graph
    vector<bool> reachable(n + 1, false);
    queue<ll> q;
    q.push(src);
    reachable[src] = true;
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (Edge &e : g[u]) {
            if (e.cap - e.f > 0 && !reachable[e.to]) {
                reachable[e.to] = true;
                q.push(e.to);
            }
        }
    }

    // Find min-cut edges: u reachable, v not reachable
    vector<pll> ans;
    for (auto it : oadj) {
        ll u = it.first.first;
        ll v = it.first.second;
        if (reachable[u] && !reachable[v]) ans.push_back({u,v});
    }

    cout << ans.size() << "\n";
    for (auto it : ans) cout << it.first << " " << it.second << "\n";

    return 0;
}
