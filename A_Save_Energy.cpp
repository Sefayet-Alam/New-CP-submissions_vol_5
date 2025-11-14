#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fast ios::sync_with_stdio(0); cin.tie(0);
#define Setpre(x) cout << fixed << setprecision(x)
#define nn "\n"

int main() {
    fast;
    ll k, d, t;
    cin >> k >> d >> t;

    ll rem = (d - k % d) % d;
    double cyctim = k + rem;
    double cycenergy = k + rem * 0.5;

    double cycs = floor((t * 1.0) / cycenergy);
    double tot = cycs * cyctim;
    double cooked = cycs * cycenergy;

    double remtim = t - cooked;

    if (remtim <= k)
        tot += remtim; 
    else
        tot += k + (remtim - k) * 2; 

    Setpre(10) << tot << nn;
    return 0;
}
