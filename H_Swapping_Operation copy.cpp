#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define nl '\n'
#define tsolve int t;cin >> t; while(t--) solve
constexpr ll mod = 1e9 + 7;
struct SparseTable {
    vector<vector<int>> st;

    int better(int lidx, int ridx) {
        return lidx & ridx;
    }

    void init(vector<int> &vec) {
        int n = ssize(vec);
        st.assign(__lg(n) + 1, vector<int>(n));
        st[0] = vec;
        for (int j = 0; (2 << j) <= n; j++) {
            for (int i = 0; i + (2 << j) <= n; i++) {
                st[j + 1][i] = better(st[j][i] , st[j][i + (1 << j)]);
            }}}

    int query(int l, int r) {
        assert(l <= r);
        if (r == l) return -1;
        int j = __lg(r - l); //31 - builtin_clz(r - l);
        return better(st[j][l] , st[j][r - (1 << j)]);
    }
};

bool check(vector<int> &a, SparseTable &sparse, array<vector<int>, 30> &pos0, int mask) {
    int n = ssize(a);
    for (int i = 0; i < n; i++) {
        if ((a[i] & mask) == mask) return true;
    }
    for (int i = 0; i < 30; i++) {
        if (!(mask >> i & 1) || empty(pos0[i])) continue;
        int swap_left = pos0[i][0];
        if (swap_left > 0 && ((sparse.query(0, swap_left) | sparse.query(swap_left, n)) & mask) == mask) return true;
        for (int j = 0; j < 30; j++) {
            int k;
            if (i == j) {
                if (ssize(pos0[i]) == 1) continue;
                k = pos0[i][1];
            } else {
                if (!(mask >> j & 1) || empty(pos0[j])) continue;
                k = pos0[j][0];
                if (k <= swap_left) continue;
            }
            {
                int left_contrib = sparse.query(0, swap_left) & sparse.query(swap_left + 1, k) & mask;
                int right_contrib = mask ^ left_contrib;
                if ((a[swap_left] & right_contrib) != right_contrib) continue;
                int viol1 = -1, viol2 = -1;
                for (int l = 0; l < 30; l++) {
                    if (!(right_contrib >> l & 1)) continue;
                    for (int x: pos0[l] | views::reverse | views::take(2)) {
                        if (x > viol1) viol2 = viol1, viol1 = x;
                        else if (x < viol1 && x > viol2) viol2 = x;
                    }
                }
                if (viol1 < k) {
                    // swap with arbitrary element
                    // TODO: is there an element x in [k,n) s.t. a[x] & left_contrib == left_contrib
                    // swap with a[k-1] instead! but what if k == swap_left+1??? then we could just split at swap_left and it works!
                    // but what if k == 1??? -> special case above
                    if (k != swap_left+1) return true;
                } else if (viol2 < k) {
                    if ((a[viol1] & left_contrib) == left_contrib) return true;
                }
            }
            {
                for (int l = 0; l < 30; l++) {
                    if (ssize(pos0[l]) != 1) continue;
                    int x = pos0[l][0];
                    if (x < k) continue;
                    if ((((sparse.query(0, swap_left) & a[x] & sparse.query(swap_left+1, k)) | (sparse.query(k, x) & a[swap_left] & sparse.query(x+1, n))) & mask) == mask) return true;
                }
            }
        }
    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x: a) cin >> x;
    vector<int> arev;
    {
        auto r = a | views::reverse;
        arev.assign(begin(r), end(r));
    }
    int ans = 0;
    SparseTable sparse;
    sparse.init(a);
    SparseTable rsparse;
    rsparse.init(arev);

    array<vector<int>, 30> pos0, pos0r;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < n; j++) if (!(a[j] >> i & 1)) pos0[i].push_back(j);
        for (int j = 0; j < n; j++) if (!(arev[j] >> i & 1)) pos0r[i].push_back(j);
    }

    for (int bit = 1 << 29; bit; bit >>= 1) {
        if (sparse.query(0, n) & bit) continue;
        if (check(a, sparse, pos0, ans | bit) || check(arev, rsparse, pos0r, ans | bit)) ans |= bit;
    }

    cout << ans + 2*sparse.query(0, n) << "\n";
}


int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    cout.tie(nullptr);

    tsolve();
}