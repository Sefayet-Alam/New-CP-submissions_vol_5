#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define SZ(a) (int)a.size()
#define all(x) x.begin(), x.end()
#define pb push_back
#define mem(a, b) memset(a, b, sizeof(a))

const int N = 100005;

struct info {
    int c, l, r, bl, br;
};

vector<int> g[N];
vector<info> anc[N];
int val[N], sub[N];
bool blk[N];
int n, q;

// Segment Tree per centroid
vector<int> tr[N];
vector<bool> lz[N];
int csz[N];

void push(int id, int v, int tl, int trr) {
    if (lz[id][v]) {
        int tm = (tl + trr) / 2;
        lz[id][2 * v] = !lz[id][2 * v];
        tr[id][2 * v] = (tm - tl + 1) - tr[id][2 * v];
        lz[id][2 * v + 1] = !lz[id][2 * v + 1];
        tr[id][2 * v + 1] = (trr - tm) - tr[id][2 * v + 1];
        lz[id][v] = 0;
    }
}

void upd(int id, int v, int tl, int trr, int l, int r) {
    if (l > r) return;
    if (l == tl && r == trr) {
        tr[id][v] = (trr - tl + 1) - tr[id][v];
        lz[id][v] = !lz[id][v];
    } else {
        push(id, v, tl, trr);
        int tm = (tl + trr) / 2;
        upd(id, 2 * v, tl, tm, l, min(r, tm));
        upd(id, 2 * v + 1, tm + 1, trr, max(l, tm + 1), r);
        tr[id][v] = tr[id][2 * v] + tr[id][2 * v + 1];
    }
}

int qry(int id, int v, int tl, int trr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == trr) return tr[id][v];
    push(id, v, tl, trr);
    int tm = (tl + trr) / 2;
    return qry(id, 2 * v, tl, tm, l, min(r, tm)) +
           qry(id, 2 * v + 1, tm + 1, trr, max(l, tm + 1), r);
}

int qrypt(int id, int v, int tl, int trr, int p) {
    if (tl == trr) return tr[id][v];
    push(id, v, tl, trr);
    int tm = (tl + trr) / 2;
    if (p <= tm) return qrypt(id, 2 * v, tl, tm, p);
    return qrypt(id, 2 * v + 1, tm + 1, trr, p);
}

// Decomposition
int timer;
int tin[N], tout[N];
vector<int> tvals;

void getsz(int u, int p) {
    sub[u] = 1;
    for (int v : g[u]) {
        if (v != p && !blk[v]) {
            getsz(v, u);
            sub[u] += sub[v];
        }
    }
}

int findcen(int u, int p, int tot) {
    for (int v : g[u]) {
        if (v != p && !blk[v] && sub[v] > tot / 2)
            return findcen(v, u, tot);
    }
    return u;
}

void dfscen(int u, int p, int cxor) {
    tin[u] = ++timer;
    int cur = cxor ^ val[u];
    tvals.pb(cur);
    for (int v : g[u]) {
        if (v != p && !blk[v]) dfscen(v, u, cur);
    }
    tout[u] = timer;
}

void build(int id, int v, int tl, int trr) {
    if (tl == trr) tr[id][v] = tvals[tl - 1];
    else {
        int tm = (tl + trr) / 2;
        build(id, 2 * v, tl, tm);
        build(id, 2 * v + 1, tm + 1, trr);
        tr[id][v] = tr[id][2 * v] + tr[id][2 * v + 1];
    }
}

void decompose(int u) {
    getsz(u, -1);
    int tot = sub[u];
    int cen = findcen(u, -1, tot);

    timer = 0;
    tvals.clear();
    tin[cen] = ++timer;
    tvals.pb(val[cen]);

    for (int v : g[cen]) {
        if (!blk[v]) dfscen(v, cen, val[cen]);
    }
    tout[cen] = timer;

    csz[cen] = tot;
    tr[cen].assign(4 * tot + 1, 0);
    lz[cen].assign(4 * tot + 1, 0);
    build(cen, 1, 1, tot);

    anc[cen].pb({cen, tin[cen], tout[cen], -1, -1});

    for (int v : g[cen]) {
        if (!blk[v]) {
            int bl = tin[v], br = tout[v];
            auto tag = [&](auto&& self, int curr, int p) -> void {
                anc[curr].pb({cen, tin[curr], tout[curr], bl, br});
                for (int nxt : g[curr]) {
                    if (nxt != p && !blk[nxt]) self(self, nxt, curr);
                }
            };
            tag(tag, v, cen);
        }
    }

    blk[cen] = 1;
    for (int v : g[cen]) {
        if (!blk[v]) decompose(v);
    }
}

void solve(int tno) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        anc[i].clear();
        tr[i].clear(); lz[i].clear();
        blk[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].pb(v); g[v].pb(u);
    }

    decompose(1);

    cout << "Case " << tno << ":" << "\n";
    int root = 1;

    while (q--) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            val[x] ^= 1;
            for (auto& i : anc[x]) {
                upd(i.c, 1, 1, csz[i.c], i.l, i.r);
            }
        } else {
            root = x;
        }

        int ans = 0;
        for (auto& i : anc[root]) {
            int c = i.c;
            int px = qrypt(c, 1, 1, csz[c], i.l);
            int tar = 1 ^ px ^ val[c];
            int tot1 = tr[c][1];
            int cnt = (tar == 1) ? tot1 : (csz[c] - tot1);

            if (i.bl != -1) {
                int bon = qry(c, 1, 1, csz[c], i.bl, i.br);
                int bsz = i.br - i.bl + 1;
                int bcnt = (tar == 1) ? bon : (bsz - bon);
                cnt -= bcnt;
            }
            ans += cnt;
        }
        cout << ans << "\n";
    }
}

int main() {
    fast;
    int t; cin >> t;
    for (int i = 1; i <= t; i++) solve(i);
    return 0;
}