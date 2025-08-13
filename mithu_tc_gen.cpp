#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define mod 1000000007
#define inf (1LL << 62)
#define all(x) x.begin(), x.end()
#define eb emplace_back
#define ff first
#define ss second
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define dtob(p, n) bitset<p>(n).to_string()
#define btod(bin) stoi(bin, nullptr, 2)
#define ok cout << "Eureka" << nl
#define nl '\n'
#define SH 0
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// return a random number in [l, r] range
ll rand(ll l, ll r)
{
    return uniform_int_distribution<ll>(l, r)(rng);
}

ll random_seed(ll i)
{
    return rand() % i;
}

// generate an array of length n where each element in [l, r] range
void Array(ll n, ll l, ll r)
{
    for (int i = 0; i < n; i++)
    {
        cout << rand(l, r) << (i < n - 1 ? ' ' : '\n');
    }
}

// generate a string of lowercase letters of length n
void String(int n, int k)
{
    for (int i = 0; i < n; i++)
    {
        cout << (char)('a' + rand(0, k - 1));
    }
    cout << '\n';
}

void Permutation(int n)
{
    vl v;
    for (ll i = 0; i < n; i++)
        v.eb(i + 1);
    random_shuffle(v.begin(), v.end(), random_seed);
    for (auto u : v)
        cout << u << " ";
    cout << nl;
}

const ll N = 1e12;

void generate()
{
    // freopen("output.txt", "w", stdout);
    cout << 1 << nl;
    ll a = rand(0, 100);
    ll b = rand(0, 100);
    ll c = rand(1, 100);
    cout << a << " " << b << " " << c << nl;
}

int main(int argc, char *argv[])
{
    fastio;
    generate();
    return SH;
}