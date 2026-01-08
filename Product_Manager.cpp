/**
 * Problem: Product Manager
 * Platform: LightOJ
 * Analysis:
 * The problem asks to minimize the production time for K identical products passing through N stages (PQAs).
 * The processing time at stage i is determined by the specific PQA assigned to that stage.
 * In a flow shop with machine-dependent but job-independent processing times, the makespan (total time)
 * is theoretically derived as: Sum(t_i) + (K-1) * Max(t_i).
 * Since this value relies only on the set of times and not their sequence, the makespan is invariant
 * under permutation. Thus, all N! arrangements yield the same optimal time.
 */

#include <iostream>
#include <vector>

using namespace std;

// Array to store precomputed factorials up to 20.
unsigned long long facts[21];

// Function to precompute factorials
void precompute() {
    facts[0] = 1;
    for (int i = 1; i <= 20; ++i) {
        facts[i] = facts[i - 1] * i;
    }
}

void solve(int t) {
    int N;
    long long K;
    if (!(cin >> N >> K)) return;

    // We must read the N integers representing processing times to consume the input correctly.
    // However, the actual values do not change the count of optimal arrangements (which is always N!).
    long long val;
    for (int i = 0; i < N; ++i) {
        cin >> val;
    }

    // The answer is N!
    cout << "Case " << t << ": " << facts[N] << "\n";
}

int main() {
    // Optimize standard I/O operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            solve(i);
        }
    }
    return 0;
}


