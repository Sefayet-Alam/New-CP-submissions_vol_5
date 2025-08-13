#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

pair<int, int> getrange(int k) {
    int upper = (1 << min(k, 31));
    return {k + 1, upper};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> facs;
        for (int d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                facs.push_back(d);
                if (d != n / d) {
                    facs.push_back(n / d);
                }
            }
        }
        
        int ans = -1;
        for (int L = 1; L < 66; L++) {
            int even = L / 2;
            int odd = (L - 1) / 2;
            
            auto [l1, r1] = getrange(even);
            auto [l2, r2] = getrange(odd);
            
            for (int d1 : facs) {
                if (l1 <= d1 && d1 <= r1) {
                    int d2 = n / d1;
                    if (l2 <= d2 && d2 <= r2) {
                        ans = L;
                        break;
                    }
                }
            }
            if (ans != -1) break;
        }
        cout << ans << '\n';
    }
    return 0;
}