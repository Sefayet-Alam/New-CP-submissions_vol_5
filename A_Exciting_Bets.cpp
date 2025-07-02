#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        if (a == b) {
            cout << "0 0" << endl;
        } else {
            long long d = abs(a - b);
            long long g = d;
            // Calculate k_increase: minimal k to make (a + k) % g == 0
            long long k_increase = (g - (a % g)) % g;
            // Calculate k_decrease: minimal k to make (a - k) % g == 0
            long long k_decrease = a % g;
            // Check if decrease is possible (both a and b >= k_decrease)
            long long k;
            if (a >= k_decrease && b >= k_decrease) {
                k = min(k_increase, k_decrease);
            } else {
                k = k_increase;
            }
            cout << g << " " << k << endl;
        }
    }
}

int main() {
    solve();
    return 0;
}