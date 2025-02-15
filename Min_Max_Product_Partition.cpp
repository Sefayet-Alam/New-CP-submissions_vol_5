#include <bits/stdc++.h>
using namespace std;

#define int long long
 
const int MOD = 998244353;
 
vector<int> power2;
 
int modExp(int base, int exp, int mod) {
    int res = 1;
    base %= mod;
    while(exp) {
        if(exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}
 
struct Node {
    int len;
    int f, sumRight, sumLeft, first, last;
};
 
Node makeNode(int v, int c) {
    Node node;
    node.len = c;
    if(c == 0) {
        node.f = node.sumRight = node.sumLeft = node.first = node.last = 0;
    } else {
        node.sumRight = ( v % MOD * ((power2[c] - 1 + MOD) % MOD) ) % MOD;
        node.sumLeft  = node.sumRight;
        node.f        = ((v % MOD * v % MOD) % MOD * ((power2[c] - 2 + MOD) % MOD)) % MOD;
        node.first    = v;
        node.last     = v;
    }
    return node;
}
 
Node combine(const Node &L, const Node &R) {
    if(L.len == 0) return R;
    if(R.len == 0) return L;
    Node res;
    res.len = L.len + R.len;
    res.first = L.first;
    res.last  = R.last;
    res.sumRight = ( L.sumRight + (power2[L.len] * R.sumRight) % MOD ) % MOD;
    res.sumLeft  = ( (power2[R.len] * L.sumLeft) % MOD + R.sumLeft ) % MOD;
    int cross = ( (L.sumLeft * R.sumRight) % MOD + (L.last % MOD * R.first % MOD) % MOD ) % MOD;
    res.f = ( L.f + R.f + cross ) % MOD;
    return res;
}
 
struct SegTree {
    int n;
    vector<Node> tree;
    SegTree(int n) : n(n) { tree.resize(4 * n); }
    void build(vector<int>& freq, vector<int>& vals, int idx, int l, int r) {
        if(l == r) {
            tree[idx] = makeNode(vals[l], freq[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(freq, vals, idx * 2, l, mid);
        build(freq, vals, idx * 2 + 1, mid + 1, r);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }
    void update(int idx, int l, int r, int pos, int newFreq, int val) {
        if(l == r) {
            tree[idx] = makeNode(val, newFreq);
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid)
            update(idx * 2, l, mid, pos, newFreq, val);
        else
            update(idx * 2 + 1, mid + 1, r, pos, newFreq, val);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }
};
 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int N, Q;
        cin >> N >> Q;
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        vector<pair<int,int>> updates(Q);
        vector<int> allValues;
        for (int i = 0; i < N; i++) allValues.push_back(A[i]);
        for (int i = 0; i < Q; i++){
            int x, v;
            cin >> x >> v;
            updates[i] = {x - 1, v};
            allValues.push_back(v);
        }
        sort(allValues.begin(), allValues.end());
        allValues.erase(unique(allValues.begin(), allValues.end()), allValues.end());
        int m = allValues.size();
        unordered_map<int,int> comp;
        for (int i = 0; i < m; i++) comp[allValues[i]] = i;
        vector<int> freq(m, 0);
        vector<int> vals(m, 0);
        for (int i = 0; i < m; i++) vals[i] = allValues[i];
        for (int i = 0; i < N; i++){
            int idx = comp[A[i]];
            freq[idx]++;
        }
        power2.resize(N + 5);
        power2[0] = 1;
        for (int i = 1; i < N + 5; i++){
            power2[i] = (power2[i - 1] * 2) % MOD;
        }
        SegTree seg(m);
        seg.build(freq, vals, 1, 0, m - 1);
        cout << seg.tree[1].f % MOD << "\n";
        for (int i = 0; i < Q; i++){
            int pos = updates[i].first;
            int newVal = updates[i].second;
            int oldVal = A[pos];
            A[pos] = newVal;
            int oldIdx = comp[oldVal], newIdx = comp[newVal];
            freq[oldIdx]--;
            freq[newIdx]++;
            seg.update(1, 0, m - 1, oldIdx, freq[oldIdx], vals[oldIdx]);
            seg.update(1, 0, m - 1, newIdx, freq[newIdx], vals[newIdx]);
            cout << seg.tree[1].f % MOD << "\n";
        }
    }
    return 0;
}