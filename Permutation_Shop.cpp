#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const int MAXN = 200005;

long long fact[MAXN];

void precompute_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    vector<bool> used(n + 1, false);
    int neg_one_count = 0;

    for (int i = 0; i < n; i++) {
        cin >> p[i];
        if (p[i] != -1) {
            used[p[i]] = true;
        } else {
            neg_one_count++;
        }
    }

    if (neg_one_count == n) {
        long long total_f_sum = 0;
        for (long long m = 2; m < n; ++m) {
            long long T_m = m * (m + 1) / 2;
            if (T_m > n) {
                break;
            }
            long long ways = (m * (m - 1)) % MOD;
            ways = (ways * fact[n - 2]) % MOD;
            total_f_sum = (total_f_sum + ways) % MOD;
        }
        cout << total_f_sum << endl;
        return;
    }

    vector<int> unused_nums;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            unused_nums.push_back(i);
        }
    }

    long long total_f_sum = 0;

    for (long long m = 1; m < n; ++m) {
        long long T_m = m * (m + 1) / 2;
        if (T_m > n || T_m < 2) {
            continue;
        }

        int unused_s = 0;
        for (int x : unused_nums) {
            if (x <= m) {
                unused_s++;
            }
        }
        
        long long current_m_ways = 0;

        if (p[0] != -1 && p[n - 1] != -1) {
            if (p[0] <= m && p[n - 1] <= m) {
                current_m_ways = fact[neg_one_count];
            }
        }
        else if (p[0] != -1 && p[n - 1] == -1) {
            if (p[0] <= m) {
                if(neg_one_count > 0)
                   current_m_ways = (1LL * unused_s * fact[neg_one_count - 1]) % MOD;
            }
        }
        else if (p[0] == -1 && p[n - 1] != -1) {
            if (p[n - 1] <= m) {
                if(neg_one_count > 0)
                    current_m_ways = (1LL * unused_s * fact[neg_one_count - 1]) % MOD;
            }
        }
        else if (p[0] == -1 && p[n - 1] == -1) {
             if (neg_one_count >= 2) {
                 long long term = (1LL * unused_s * (unused_s - 1)) % MOD;
                 if (term < 0) term += MOD;
                 current_m_ways = (term * fact[neg_one_count - 2]) % MOD;
             }
        }

        total_f_sum = (total_f_sum + current_m_ways) % MOD;
    }

    cout << total_f_sum << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute_factorials();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}