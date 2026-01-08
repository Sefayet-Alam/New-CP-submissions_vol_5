#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);

const ll N = 2000005;
const ll M = 998244353;

ll iv[N], f[N], g[N];

int main() {
    fast;
    
    iv[1] = 1;
    for (int i = 2; i < N; i++) 
        iv[i] = M - (M / i) * iv[M % i] % M;

    f[1] = 1; 
    g[1] = 1;
    
    ll sg = 1, sjg = 1, sjjg = 1;
    ll sf = 1, sjf = 1;
    ll i2 = iv[2];

    for (ll i = 2; i < N; i++) {
        ll k = iv[i - 1] * iv[i + 2] % M * 2 % M;
        
        ll ng = ((i + 1) * sg % M - sjg + M) % M;
        g[i] = (1 + ng * k) % M;

        ll tf = ((i + 1) * sf % M - sjf + M) % M;
        ll tg = ((i * i % M + i) % M * sg % M - (2 * i + 1) % M * sjg % M + sjjg + 2 * M) % M;
        tg = tg * i2 % M;

        ll tot = (tf + tg) % M;
        ll base = (i + 1) * i2 % M;
        f[i] = (base + tot * k) % M;

        sg = (sg + g[i]) % M;
        sjg = (sjg + i * g[i]) % M;
        sjjg = (sjjg + i * i % M * g[i]) % M;
        sf = (sf + f[i]) % M;
        sjf = (sjf + i * f[i]) % M;
    }

    ll t;
    if (cin >> t) {
        while (t--) {
            ll l, r;
            cin >> l >> r;
            ll n = r - l + 1;
            ll ans = (f[n] + (l - 1) * g[n]) % M;
            cout << ans << "\n";
        }
    }

    return 0;
}