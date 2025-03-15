#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);
const int NX = 30000 + 10;

struct Line {
    int x, ymin, ymax, op;
    Line() {}
    Line(int _x, int _ym, int _ymx, int _op) {
        x = _x;
        ymin = _ym;
        ymax = _ymx;
        op = _op;
    }
    bool operator<(const Line& e) const {
        return x < e.x;
    }
};

Line inp[(NX << 5) + 1];
long long sum[(NX << 5) + 1], h[(NX << 5) + 1], lazy[(NX << 5) + 1];

int n, m, l;

void compress() {
    int k = 1;
    for (int i = 2; i <= m; i++) {
        if (h[k] != h[i]) {
            h[++k] = h[i];
        }
    }
    m = k;
}

void update(int node, int l, int r, int x, int y, int op) {
    int lchild = node * 2;
    int rchild = lchild + 1;
    int mid = (l + r) / 2;

    if (h[r] < x || h[l] > y) return; // Out of boundary
    if (h[l] >= x && h[r] <= y) {
        lazy[node] += (op ? 1 : -1);
        if (lazy[node])
            sum[node] = h[r] - h[l];
        else
            sum[node] = sum[lchild] + sum[rchild];
        return;
    }
    if (l + 1 >= r) return; // No need to process further

    update(lchild, l, mid, x, y, op);
    update(rchild, mid, r, x, y, op);

    if (lazy[node])
        sum[node] = h[r] - h[l];
    else
        sum[node] = sum[lchild] + sum[rchild];
}

int main() {
    // Input processing using standard I/O
    int t=1;
    // scanf("%d", &t);
    for (int cs = 1; cs <= t; cs++) {
        scanf("%d", &n);
        l = 0;
        m = 0;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            inp[l++] = Line(x1, y1, y2, 1);
            inp[l++] = Line(x2, y1, y2, 0);
            h[++m] = y1;
            h[++m] = y2;
        }

        sort(inp, inp + l);
        sort(h + 1, h + 1 + m);

        compress();
        int lim = (NX << 3);
        for (int i = 0; i <= lim; i++) {
            lazy[i] = sum[i] = 0;
        }

        update(1, 1, m, inp[0].ymin, inp[0].ymax, inp[0].op);

        long long ans = 0;
        for (int i = 1; i < l; i++) {
            ans += sum[1] * (long long)(inp[i].x - inp[i - 1].x);
            update(1, 1, m, inp[i].ymin, inp[i].ymax, inp[i].op);
        }
        printf("Case %d: %lld\n", cs, ans);
    }
    return 0;
}
