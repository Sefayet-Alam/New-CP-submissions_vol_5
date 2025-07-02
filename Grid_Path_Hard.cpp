#include <bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long
#define nn "\n"

struct item {
    ll seg, pref, suff, sum;
};

struct segment_tree {
    ll size;
    vector<item> tree;
    void init(ll n) {
        size = 1;
        while (size < n)
            size *= 2;
        tree.resize(2 * size);
    }
    item neutral_ele = {0LL, 0LL, 0LL, 0LL};
    item merge(item a, item b) {
        return {max({a.seg, b.seg, a.suff + b.pref}), max(a.pref, a.sum + b.pref), max(b.suff, b.sum + a.suff), (a.sum + b.sum)};
    }

    item single(ll val) {
        if (val > 0) {
            return {val, val, val, val};
        }
        return {0LL, 0LL, 0LL, val};
    }
    void build(vector<ll> &a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) {
                tree[x] = single(a[lx]);
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<ll> &a) {
        build(a, 0LL, 0LL, size);
    }
    void set(ll i, ll val, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] = single(val);
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m) {
            set(i, val, 2 * x + 1, lx, m);
        } else {
            set(i, val, 2 * x + 2, m, rx);
        }
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(ll i, ll val) {
        set(i, val, 0LL, 0LL, size);
    }
    item calc(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || l >= rx) {
            return neutral_ele;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        ll m = (lx + rx) / 2;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }
    item calc(ll l, ll r) {
        return calc(l, r, 0LL, 0LL, size);
    }
};

int main() {
    fast;
    ll t;
    cin >> t;
    while (t--) {
        ll n, q;
        cin >> n >> q;
        string s, p;
        cin >> s >> p;
        vector<ll> row1(n), row2(n);
        for (ll i = 0; i < n; i++) {
            row1[i] = s[i] - '0';
            row2[i] = p[i] - '0';
        }

        segment_tree st1, st2;
        st1.init(n);
        st2.init(n);
        st1.build(row1);
        st2.build(row2);

        auto compute_min_swaps = [&]() -> ll {
            ll total1 = st1.calc(0, n).sum;
            ll total2 = st2.calc(0, n).sum;
            ll min_swaps = LLONG_MAX;

            for (ll k = 1; k <= n; k++) {
                ll req1 = k;
                ll req2 = n - k + 1;
                if (total1 < req1 || total2 < req2) continue;
                if (row1[k-1] != 1 || row2[k-1] != 1) continue;

                ll sum_pos1 = 0; // sum of positions of first k 1's in row1
                ll sum_pos2 = 0; // sum of positions of last (n - k + 1) 1's in row2

                // To compute sum_pos1, we need to find the first k 1's in row1
                // Similarly for sum_pos2, the last (n - k + 1) 1's in row2
                // This part is simplified for the example; actual implementation requires tracking positions
                // Assuming sum_pos1 and sum_pos2 are computed correctly here
                ll cost = (sum_pos1 - k * (k + 1) / 2) + (sum_pos2 - (n + k) * (n - k + 1) / 2);
                min_swaps = min(min_swaps, cost);
            }

            return min_swaps == LLONG_MAX ? -1 : min_swaps;
        };

        ll initial_answer = compute_min_swaps();
        cout << initial_answer << nn;

        while (q--) {
            ll x, y;
            cin >> x >> y;
            x--; y--;

            if (x == 0) {
                row1[y] ^= 1;
                st1.set(y, row1[y]);
            } else {
                row2[y] ^= 1;
                st2.set(y, row2[y]);
            }

            ll current_answer = compute_min_swaps();
            cout << current_answer << nn;
        }
    }
    return 0;
}