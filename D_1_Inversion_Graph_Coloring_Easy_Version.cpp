#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // dp[x][y]: number of good subsequences whose canonical partition
    // has the first increasing subsequence ending in x and the second ending in y.
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    
    // Base case: the empty subsequence.
    // Partition: ([], []), ends: (0, 0).
    dp[0][0] = 1;

    for (int v : a) {
        // next_dp stores counts of subsequences newly formed by *adding* v.
        vector<vector<long long>> next_dp(n + 1, vector<long long>(n + 1, 0));
        for (int x = 0; x <= n; ++x) {
            for (int y = 0; y <= n; ++y) {
                if (dp[x][y] == 0) continue;

                // For each existing subsequence, form a new one by appending v.
                // Apply the greedy rule to find the new canonical partition.
                
                // Rule: Try to place v in the first partition.
                if (v > x) {
                    next_dp[v][y] = (next_dp[v][y] + dp[x][y]) % MOD;
                } 
                // Rule: If not possible, try to place v in the second partition.
                else if (v > y) {
                    next_dp[x][v] = (next_dp[x][v] + dp[x][y]) % MOD;
                }
            }
        }

        // Add the counts of newly formed subsequences to the main dp table.
        // The original dp values represent subsequences *not* containing v.
        for (int x = 0; x <= n; ++x) {
            for (int y = 0; y <= n; ++y) {
                dp[x][y] = (dp[x][y] + next_dp[x][y]) % MOD;
            }
        }
    }

    long long total_good_subsequences = 0;
    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y <= n; ++y) {
            total_good_subsequences = (total_good_subsequences + dp[x][y]) % MOD;
        }
    }

    cout << total_good_subsequences << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}