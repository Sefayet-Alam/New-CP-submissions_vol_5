#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6+10;

int n, k;                   // Number of PolandBalls and forgetful Balls
int p[MAX_N], mark[MAX_N];  // p[i] stores the permutation, mark[i] for DFS traversal
vector<int> vec;            // Stores the sizes of cycles
bitset<MAX_N> dp;           // DP bitset for subset sum
int cnt[MAX_N], mn;         // cnt[i] stores count of cycles of length i

// DFS function to determine the length of a cycle
int dfs(int v) {
    mark[v] = 1;  // Mark current node as visited
    if (mark[p[v]]) // If we reach a visited node, cycle is complete
        return 1;
    return dfs(p[v]) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Input reading
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;  // Convert to 0-based index
    }

    // Step 1: Find all cycles in the permutation
    for (int i = 0; i < n; i++) {
        if (!mark[i]) {
            vec.push_back(dfs(i));  // Store cycle size
        }
    }

    // Step 2: Count occurrences of cycle lengths
    for (int x : vec) {
        cnt[x]++;
    }

    // Step 3: DP to find the minimum number of gifts not received
    dp[0] = 1; // Base case: we can always achieve sum 0
    for (int i = 0; i < n; i++) {
        int t = 1;
        while (cnt[i]) {
            t = min(t, cnt[i]);  // Process cycles in powers of 2 (binary optimization)
            dp |= dp << (i * t); // Bitset shift to track subset sums
            cnt[i] -= t;
            t *= 2;  // Increase `t` exponentially (binary representation)
        }
    }

    // Step 4: Determine the minimum number of unreceived gifts
    cout << (dp[k] ? k : min(k + 1, n)) << ' ';

    // Step 5: Determine the maximum number of unreceived gifts
    mn = n;
    for (int x : vec) {
        int t = min(x / 2, k);  // Remove as many pairs as possible
        mn -= 2 * t;
        k -= t;
    }
    for (int x : vec) {
        int t = min(x & 1, k);  // Handle remaining odd cycle parts
        mn -= t;
        k -= t;
    }

    // Output the maximum number of unreceived gifts
    cout << n - mn << '\n';
}
