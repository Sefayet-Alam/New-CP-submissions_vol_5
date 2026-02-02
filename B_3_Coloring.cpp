#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// VVI
#define fast ios_base::sync_with_stdio(false); cin.tie(nullptr);

#define ll long long
#define SZ(a) (int)(a).size()
#define mp make_pair
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) (x).begin(), (x).end()

// Printings & debugging
#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl

/// INLINE FUNCTIONS
inline ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a * b / GCD(a, b); }
inline double logb(ll base, ll num) { return (double)log(num) / (double)log(base); }

/// Data structures
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vvl;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

namespace io {
template <typename First, typename Second>
ostream &operator<<(ostream &os, const pair<First, Second> &p) { return os << p.first << " " << p.second; }

template <typename First>
ostream &operator<<(ostream &os, const vector<First> &v) {
    bool space = false;
    for (First x : v) {
        if (space) os << " ";
        space = true;
        os << x;
    }
    return os;
}

template <typename First, typename Second>
istream &operator>>(istream &is, pair<First, Second> &p) { return is >> p.first >> p.second; }

template <typename First>
istream &operator>>(istream &is, vector<First> &v) {
    for (First &x : v) is >> x;
    return is;
}
} // namespace io
using namespace io;

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;

static inline void tel(int b, int i, int j) {
    cout << b << " " << i << " " << j << endl; // endl flushes
}
static inline int ask() {
    int x;
    cin >> x;
    return x;
}

int main() {
    fast;

    int n;
    cin >> n;

    vector<pair<int,int>> cells[2];
    cells[0].reserve(n * n);
    cells[1].reserve(n * n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cells[(i + j) & 1].push_back({i, j});
        }
    }

    int p0 = 0, p1 = 0;
    for (int turn = 0; turn < n * n; turn++) {
        int a = ask();
        if (a == 1) {
            if (p1 < SZ(cells[1])) {
                auto [i, j] = cells[1][p1++];
                tel(2, i, j);
            } else {
                auto [i, j] = cells[0][p0++];
                tel(3, i, j);
            }
        } 
        else if (a == 2) {
            if (p0 < SZ(cells[0])) {
                auto [i, j] = cells[0][p0++];
                tel(1, i, j);
            } else {
                auto [i, j] = cells[1][p1++];
                tel(3, i, j);
            }
        } else { // a == 3
            if (p0 < SZ(cells[0])) {
                auto [i, j] = cells[0][p0++];
                tel(1, i, j);
            } else {
                auto [i, j] = cells[1][p1++];
                tel(2, i, j);
            }
        }
    }

    return 0;
}
