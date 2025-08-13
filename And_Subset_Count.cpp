#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define md 1000000007
const ll MLOG = 20;
const ll MAXN = (1LL << MLOG);
ll dp[MAXN];

void forward2(ll dp[]) {
    for (ll bit = 0; bit < MLOG; bit++) {
        for (ll i = MAXN - 1; i >= 0; i--) {
            if (i & (1 << bit)) {
                dp[i ^ (1 << bit)] = (dp[i ^ (1 << bit)] + dp[i]) % md;
            }
        }
    }
}

void backward2(ll dp[]) {
    for (ll bit = 0; bit < MLOG; bit++) {
        for (ll i = 0; i < MAXN; i++) {
            if (i & (1 << bit)) {
                dp[i ^ (1 << bit)] = (dp[i ^ (1 << bit)] - dp[i] + md) % md;
            }
        }
    }
}

ll power(ll a, ll b, ll mod) {
    ll res = 1;
    a = a % mod;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        dp[x]++;
    }

    forward2(dp);
    for (ll i = 0; i < MAXN; i++) {
        dp[i] = (power(2, dp[i], md) - 1 + md) % md;
    }
    backward2(dp);
    for(ll k=0;k<=n;k++){
        cout<<dp[k]<<" ";
    }
    cout<<endl;

    return 0;
}


