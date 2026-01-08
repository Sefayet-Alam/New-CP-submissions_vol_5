/**
 * Problem: Move m bishops from initial to target configuration on an n x n board.
 * Constraints: n is odd, corners are black. m <= n. Max moves 4m.
 * Solution Strategy:
 * 1. "Parking": Move all bishops from their Initial positions to distinct positions on the Main Diagonal (1,1) to (n,n).
 * 2. "Unparking": Move bishops from the Main Diagonal to the Target positions (reverse of Parking).
 * 3. Combine the moves.
 * 
 * Parking Algorithm:
 * - Each bishop at (r, c) has a "projection" k = (r+c)/2 on the main diagonal.
 * - Bishops with the same k are on the same anti-diagonal.
 * - We group bishops by k and sort them by distance to the diagonal (Inner to Outer).
 * - We assign distinct target spots t on the diagonal to each bishop.
 * - To avoid collisions:
 *   - Bishops moving "Left" (target < k) must be processed in increasing order of target, with Inner bishops taking smallest targets.
 *   - Bishops moving "Right" (target > k) must be processed in decreasing order of target, with Inner bishops taking largest targets.
 * - The moves are generated in two passes: Left Movers first, then Right/Stay Movers.
 * 
 * Move Count:
 * - Each bishop moves at most 2 times to park: (r, c) -> (k, k) -> (t, t).
 * - Same for unparking.
 * - Total moves <= 2m + 2m = 4m.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

// Structure to represent a bishop's state
struct B {
    int r, c;
    int k; // Projection index (r+c)/2
    int d; // Distance |r-c| (Inner < Outer)
    int t; // Assigned target on diagonal
};

// Structure to represent a move
struct M {
    int r1, c1, r2, c2;
};

// Comparator for sorting bishops by projection k, then by distance d
bool cmpK(const B& a, const B& b) {
    if (a.k != b.k) return a.k < b.k;
    return a.d < b.d;
}

// Comparator for sorting by assigned target t
bool cmpT(const B& a, const B& b) {
    return a.t < b.t;
}

/**
 * Solves the subproblem of moving bishops from configuration `b` to the main diagonal targets specified in `b[i].t`.
 * Returns the list of moves.
 */
vector<M> solve_moves(int n, int m, vector<B>& b) {
    vector<M> res;
    
    // Separate into Left Movers (target < k) and Right/Stay Movers (target >= k)
    // Note: The assignment of targets and sorting guarantees collision-free paths if processed in correct order.
    
    // Sort by target to process in order along the diagonal
    sort(b.begin(), b.end(), cmpT);

    // Pass 1: Left Movers (target < k)
    // Process in increasing order of target t
    for (int x = 0; x < m; ++x) {
        if (b[x].t < b[x].k) {
            // Move 1: To diagonal (k, k) if not already there
            if (b[x].r != b[x].k || b[x].c != b[x].k)
                res.push_back({b[x].r, b[x].c, b[x].k, b[x].k});
            // Move 2: To target (t, t) if different from k
            if (b[x].k != b[x].t)
                res.push_back({b[x].k, b[x].k, b[x].t, b[x].t});
        }
    }

    // Pass 2: Right/Stay Movers (target >= k)
    // Process in decreasing order of target t to avoid blocking
    for (int x = m - 1; x >= 0; --x) {
        if (b[x].t >= b[x].k) {
            // Move 1: To diagonal (k, k)
            if (b[x].r != b[x].k || b[x].c != b[x].k)
                res.push_back({b[x].r, b[x].c, b[x].k, b[x].k});
            // Move 2: To target (t, t)
            if (b[x].k != b[x].t)
                res.push_back({b[x].k, b[x].k, b[x].t, b[x].t});
        }
    }
    return res;
}

void run(int tc) {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<B> s(m), t(m);
    for (int i = 0; i < m; ++i) {
        cin >> s[i].r >> s[i].c;
        s[i].k = (s[i].r + s[i].c) / 2;
        s[i].d = abs(s[i].r - s[i].c);
    }
    for (int i = 0; i < m; ++i) {
        cin >> t[i].r >> t[i].c;
        t[i].k = (t[i].r + t[i].c) / 2;
        t[i].d = abs(t[i].r - t[i].c);
    }

    // Sort both configurations by k, then d.
    // This effectively matches the i-th bishop in S to the i-th bishop in T via the i-th target spot.
    sort(s.begin(), s.end(), cmpK);
    sort(t.begin(), t.end(), cmpK);

    // Generate distinct target spots P on the main diagonal.
    // We try to keep P[i] close to S[i].k to minimize movement, but distinctness is key.
    vector<int> P(m);
    for(int i=0; i<m; ++i) P[i] = s[i].k;
    
    // Enforce strictly increasing targets
    for(int i=1; i<m; ++i) {
        if(P[i] <= P[i-1]) P[i] = P[i-1] + 1;
    }
    // Shift back if we exceeded board size n
    if(P[m-1] > n) {
        int diff = P[m-1] - n;
        for(int i=0; i<m; ++i) P[i] -= diff;
    }

    // Assign targets
    for(int i=0; i<m; ++i) {
        s[i].t = P[i];
        t[i].t = P[i]; // T unparks from the SAME P
    }

    // Solve both halves
    vector<M> movesS = solve_moves(n, m, s);
    vector<M> movesT = solve_moves(n, m, t);

    // Output
    cout << "Case " << tc << ": " << (movesS.size() + movesT.size()) << "\n";
    // S -> P moves
    for (auto& x : movesS) 
        cout << x.r1 << " " << x.c1 << " " << x.r2 << " " << x.c2 << "\n";
    // P -> T moves (reverse of T -> P)
    for (int i = movesT.size() - 1; i >= 0; --i)
        cout << movesT[i].r2 << " " << movesT[i].c2 << " " << movesT[i].r1 << " " << movesT[i].c1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) run(i);
    }
    return 0;
}