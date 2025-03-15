
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <cmath>

using namespace std;

// VVI
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll int
#define SZ(a) (int)a.size()
#define UNIQUE(a) (a).erase(unique(all(a)), (a).end())
#define mp make_pair
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()

//Printings & debugging
#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 1e6+ 10;
const ll M = 1e9 + 7;



vector<int> Primes(N,1);
vector<ll>primenos;
void SieveOfEratosthenes(ll n)
{
    Primes[1]=0;
    for (ll i=2;i*i<=n;i++) {
    if(Primes[i]==1){     
    for(ll j=i*i;j<=n;j+=i)
        Primes[j]=0;
        }
    }
    for(ll i=1;i<n;i++){
        if(Primes[i]){
            primenos.push_back(i);
        }
    }
}


map<pair<string,int>,int>mpp;
int main()
{
    fast;
    SieveOfEratosthenes(N);
    string K;
    ll L;
    // cout<<primenos.size()<<nn;
    while (cin>>K>>L)
    {
        if(K=="0" && L==0) break;
        if(mpp.find(mp(K,L))!=mpp.end()){
            if(mpp[mp(K,L)]==-1) cout<<"GOOD"<<nn;
            else cout<<"BAD"<<" "<<mpp[mp(K,L)]<<nn;
            continue;
        }
        // cout<<K<<" "<<L<<nn;
        bool f=1;
        ll ans=-1;
        for(ll i=0;i<primenos.size() && primenos[i]<L;i++){
            int it=primenos[i];
            ll kseg=0;
            for (ll j = 0; j < K.size(); j++) {
                kseg *= 10;
                kseg += K[j] - '0';
                kseg %= it;
            }
            if (kseg == 0) {
                ans = it;
                f=0;
                break;
            }
        }
        mpp[mp(K,L)]=ans;
        if(f==0) cout<<"BAD"<<" "<<ans<<nn;
        else cout<<"GOOD"<<nn;
    }
    
    return 0;
}



