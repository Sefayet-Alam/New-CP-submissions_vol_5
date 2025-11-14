#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Function to handle fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

// Function to solve a single test case
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Edge case for small n, though general logic handles it.
    if (n == 2) {
        std::cout << (long long)a[0] + a[1] << "\n";
        return;
    }

    // --- Precomputation ---
    std::vector<int> prefix_and(n);
    prefix_and[0] = a[0];
    for (int i = 1; i < n; ++i) {
        prefix_and[i] = prefix_and[i - 1] & a[i];
    }

    std::vector<int> suffix_and(n);
    suffix_and[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        suffix_and[i] = suffix_and[i + 1] & a[i];
    }

    long long max_f = 0;

    // --- Case 1: No Swap ---
    for (int k = 0; k < n - 1; ++k) {
        max_f = std::max(max_f, (long long)prefix_and[k] + suffix_and[k + 1]);
    }

    // --- Case 2: Isolate a Single Element ---
    for (int i = 0; i < n; ++i) {
        int and_rest = -1; // Represents all bits set to 1 (0xFFFFFFFF)
        if (i > 0) {
            and_rest &= prefix_and[i - 1];
        }
        if (i < n - 1) {
            and_rest &= suffix_and[i + 1];
        }
        max_f = std::max(max_f, (long long)a[i] + and_rest);
    }

    // --- Case 3: Bit-based Partition ---
    for (int b = 0; b < 31; ++b) {
        std::vector<int> s0, s1;
        std::vector<int> indices_s0;
        for (int i = 0; i < n; ++i) {
            if ((a[i] >> b) & 1) {
                s1.push_back(a[i]);
            } else {
                s0.push_back(a[i]);
                indices_s0.push_back(i);
            }
        }

        if (s0.empty() || s1.empty()) {
            continue;
        }

        int k = s0.size();
        int mismatches = 0;
        for (int original_idx : indices_s0) {
            if (original_idx >= k) { // 0-based index check
                mismatches++;
            }
        }

        if (mismatches <= 1) {
            int and_s0 = -1;
            for (int val : s0) {
                and_s0 &= val;
            }
            int and_s1 = -1;
            for (int val : s1) {
                and_s1 &= val;
            }
            max_f = std::max(max_f, (long long)and_s0 + and_s1);
        }
    }

    std::cout << max_f << "\n";
}

int main() {
    fast_io();
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}