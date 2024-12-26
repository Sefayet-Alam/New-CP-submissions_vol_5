#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to find the cycle lengths in the permutation
vector<int> find_cycle_lengths(vector<int>& P, int N) {
    vector<int> visited(N + 1, 0);
    vector<int> cycle_lengths;

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            int length = 0;
            int current = i;

            while (!visited[current]) {
                visited[current] = 1;
                current = P[current - 1];
                length++;
            }

            cycle_lengths.push_back(length);
        }
    }

    return cycle_lengths;
}

int main() {
	// your code goes here
	 int T; // Number of test cases
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> P(N);
        for (int i = 0; i < N; ++i) {
            cin >> P[i];
        }

        // Find cycle lengths in the permutation
        vector<int> cycle_lengths = find_cycle_lengths(P, N);

        // Calculate the minimum cost to merge all cycles
        ll total_cost = 0;

        if (cycle_lengths.size() > 1) {
            priority_queue<int, vector<int>, greater<int>> pq(cycle_lengths.begin(), cycle_lengths.end());

            while (pq.size() > 1) {
                int smallest = pq.top();
                pq.pop();
                int second_smallest = pq.top();
                pq.pop();

                total_cost += smallest + second_smallest;
                pq.push(smallest + second_smallest);
            }
        }

        cout << total_cost << "\n";
    }

    return 0;
}