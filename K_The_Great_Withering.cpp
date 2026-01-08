/**
 * Problem: K. The Great Withering
 * Solution:
 * 1. The problem asks for the sum of valid weight assignments for m from 1 to k.
 * 2. A weight assignment is valid iff all weights are distinct and there exists a root r such that
 *    edge weights strictly increase along any path away from r.
 * 3. This structure allows us to count valid permutations of weights 1 to n-1. Let this count be A_n.
 * 4. The answer is A_n * Binomial(k+1, n).
 * 5. A_n is computed by summing contributions of each edge acting as the "minimum weight edge".
 *    Using re-rooting DP, we compute the necessary heap probabilities for each node.
 *    The formula derived is: A_n = n * (n-2)! * Sum_{(u,v)} (sz[v] * P(T, u)),
 *    where P(T, u) is the probability that a random permutation on the tree rooted at u forms a valid heap structure.
 */

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;
const int MAXN = 1000005;

long long fact[MAXN], invFact[MAXN];
long long inv[MAXN];
vector<int> adj[MAXN];
int sz[MAXN];
long long ans_An;
int n;

// Precompute factorials and modular inverses
void precompute() {
    fact[0] = 1;
    invFact[0] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAXN; i++)
        inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = (invFact[i - 1] * inv[i]) % MOD;
    }
}

// First DFS to compute subtree sizes relative to root 1
void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

// Second DFS (Re-rooting) to compute sum of terms
// P_u corresponds to Product(1/size) for the tree rooted at u
void dfs_reroot(int u, int p, long long P_u) {
    for (int v : adj[u]) {
        if (v != p) {
            // Edge (u, v) is considered. v is child of u in current rooting.
            // Contribution: sz[v] * P(T, u)
            // Note: The global multiplier (n-2)! * n is applied at the end.
            long long term = (sz[v] * P_u) % MOD;
            ans_An = (ans_An + term) % MOD;
            
            // Compute P_v for the child node to move root there
            // When moving root from u to v, u becomes a child of v with size n - sz[v]
            // P(T, v) = P(T, u) * sz[v] / (n - sz[v])
            long long P_v = P_u * sz[v] % MOD;
            P_v = P_v * inv[n - sz[v]] % MOD;
            
            dfs_reroot(v, u, P_v);
        }
    }
}

void solve() {
    int k_in;
    if (!(cin >> n >> k_in)) return;
    
    for (int i = 1; i <= n; i++) adj[i].clear();
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Base case or invalid k
    if (n > k_in + 1) {
        // Binomial(k+1, n) will be 0, handled correctly below
    }

    dfs_sz(1, 0);
    
    // Compute P(T, 1)
    long long current_P = 1;
    for (int i = 1; i <= n; i++) {
        current_P = (current_P * inv[sz[i]]) % MOD;
    }
    
    ans_An = 0;
    dfs_reroot(1, 0, current_P);
    
    // Multiply by n * (n-2)!
    // Handle n < 2 case (though problem says n >= 2)
    if (n >= 2) {
        long long factor = (fact[n - 2] * n) % MOD;
        ans_An = (ans_An * factor) % MOD;
    } else {
        ans_An = 0; // Should not happen based on constraints
    }
    
    // Calculate Binomial(k + 1, n)
    if (k_in + 1 < n) {
        cout << 0 << "\n";
        return;
    }
    
    long long binom = invFact[n];
    long long num = 1;
    // Compute (k+1) * (k) * ... * (k - n + 2)
    for (int i = 0; i < n; i++) {
        long long val = (k_in + 1 - i) % MOD;
        num = (num * val) % MOD;
    }
    binom = (binom * num) % MOD;
    
    cout << (ans_An * binom) % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
}

