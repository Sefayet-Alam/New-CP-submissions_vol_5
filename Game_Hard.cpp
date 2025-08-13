#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll long long
#define SZ(a) (int)a.size()
#define UNIQUE(a) (a).erase(unique(all(a)), (a).end())
#define mp make_pair
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()

#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")

typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vvl;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll sum_arithmetic(ll l, ll r) {
    if (l > r) return 0;
    return (r * (r + 1)) / 2 - (l - 1) * l / 2;
}

void solve() {
    ll n;
    cin >> n;
    vl A(n);
    for (ll i = 0; i < n; ++i) cin >> A[i];
    
    sort(all(A), greater<ll>());
    vl prefix(n + 1, 0);
    for (ll i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + A[i];
    }
    
    vl ans(2 * n + 1, 0);
    for (ll k = 1; k <= 2 * n; ++k) {
        ll low = (k + 1) / 2;
        ll high = min(k, n);
        ll max_sum = 0;
        
        ll left = low, right = high;
        while (left <= right) {
            ll mid1 = left + (right - left) / 3;
            ll mid2 = right - (right - left) / 3;
            
            ll sum1 = prefix[mid1] + sum_arithmetic(mid1 - (k - mid1), mid1 - 1);
            ll sum2 = prefix[mid2] + sum_arithmetic(mid2 - (k - mid2), mid2 - 1);
            
            if (sum1 < sum2) {
                max_sum = max(max_sum, sum2);
                left = mid1 + 1;
            } else {
                max_sum = max(max_sum, sum1);
                right = mid2 - 1;
            }
        }
        ans[k] = max_sum;
    }
    
    for (ll k = 1; k <= 2 * n; ++k) {
        cout << ans[k] << " ";
    }
    cout << nn;
}

int main() {
    fast;
    ll t;
    t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}