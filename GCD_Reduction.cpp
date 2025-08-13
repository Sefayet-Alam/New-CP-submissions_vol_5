#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <list>

using ll = long long;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

ll get_score(ll n, const std::vector<ll>& a) {
    if (n < 3) {
        return a[0];
    }

    std::list<ll> l(a.begin(), a.end());
    for (int i = 0; i < n - 2; ++i) {
        auto it1 = l.begin();
        auto it2 = std::next(it1);
        auto it3 = std::next(it2);
        ll val1 = *it1;
        ll val2 = *it2;
        ll val3 = *it3;

        if (gcd(val1, val3) <= gcd(val2, val3)) {
            l.erase(it1);
        } else {
            l.erase(it2);
        }
    }
    return l.front();
}

void solve() {
    ll n, x, y;
    std::cin >> n >> x >> y;

    std::vector<ll> unused;
    for (int i = 1; i <= n; ++i) {
        if (i != x && i != y) {
            unused.push_back(i);
        }
    }

    // Attempt 1: Unused numbers in ascending order
    std::vector<ll> a1 = unused;
    a1.push_back(y);
    a1.push_back(x);
    if (get_score(n, a1) != y) {
        for (size_t i = 0; i < a1.size(); ++i) {
            std::cout << a1[i] << (i == a1.size() - 1 ? "" : " ");
        }
        std::cout << "\n";
        return;
    }

    // Attempt 2: Unused numbers in descending order
    if (unused.size() > 1) {
        std::sort(unused.rbegin(), unused.rend());
        std::vector<ll> a2 = unused;
        a2.push_back(y);
        a2.push_back(x);
        if (get_score(n, a2) != y) {
            for (size_t i = 0; i < a2.size(); ++i) {
                std::cout << a2[i] << (i == a2.size() - 1 ? "" : " ");
            }
            std::cout << "\n";
            return;
        }
    }

    std::cout << -1 << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}