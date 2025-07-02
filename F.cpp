#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5e5 + 5;

int N, D, R;
int H[MAXN];
vector<pair<int, int>> scaffolds;
int dp[MAXN];
int seg[1 << 20];

void update(int pos, int val, int size) {
    pos += size;
    seg[pos] = val;
    for (pos >>= 1; pos >= 1; pos >>= 1) {
        seg[pos] = max(seg[2*pos], seg[2*pos+1]);
    }
}

int query(int l, int r, int size) {
    l += size;
    r += size;
    int res = 0;
    while (l <= r) {
        if (l % 2 == 1) res = max(res, seg[l++]);
        if (r % 2 == 0) res = max(res, seg[r--]);
        l >>= 1;
        r >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> D >> R;
    for (int i = 1; i <= N; ++i) {
        cin >> H[i];
        scaffolds.emplace_back(H[i], i);
    }

    sort(scaffolds.begin(), scaffolds.end());

    int size = 1;
    while (size < N) size <<= 1;

    int ans = 0;
    for (auto& [h, pos] : scaffolds) {
        int max_h_val = h - D;
        int current_max = 0;
        if (max_h_val >= 1) {
            int L1 = max(1, pos - R);
            int R1 = pos - 1;
            if (L1 <= R1) {
                current_max = max(current_max, query(L1 - 1, R1 - 1, size));
            }
            int L2 = pos + 1;
            int R2 = min(N, pos + R);
            if (L2 <= R2) {
                current_max = max(current_max, query(L2 - 1, R2 - 1, size));
            }
            dp[pos] = current_max + 1;
        } else {
            dp[pos] = 0;
        }
        update(pos - 1, dp[pos], size);
        ans = max(ans, dp[pos]);
    }

    cout << ans << '\n';

    return 0;
}