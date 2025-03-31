#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define nn '\n'
ll power(ll a, ll n){
    ll res = 1;
    while(n){if(n%2){res*=a;n--;}else{a*=a;n/=2;}}
    return res;
}

int main()
{
    ll t;
    t = 1;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        ll ans=(n*(n+2)*(2*n+1))/8;
        cout<<ans<<nn;
    }
    return 0;
}
