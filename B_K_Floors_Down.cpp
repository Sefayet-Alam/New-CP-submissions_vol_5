#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// VVI
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

//Printings & debugging
#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")


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
using PQ = priority_queue<T>;
template <typename T>
using QP = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> 
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using ordered_multimap = tree<T, R, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
namespace io{
    template<typename First, typename Second> ostream& operator << ( ostream &os, const pair<First, Second> &p ) { return os << p.first << " " << p.second; }
    template<typename First, typename Second> ostream& operator << ( ostream &os, const map<First, Second> &mp ) { for( auto it : mp ) { os << it << endl;  } return os; }
    template<typename First> ostream& operator << ( ostream &os, const vector<First> &v ) { bool space = false; for( First x : v ) { if( space ) os << " "; space = true; os << x; } return os; }
    template<typename First> ostream& operator << ( ostream &os, const set<First> &st ) { bool space = false; for( First x : st ) { if( space ) os << " "; space = true; os << x; } return os; }
    template<typename First> ostream& operator << ( ostream &os, const multiset<First> &st ) { bool space = false; for( First x : st ) { if( space ) os << " "; space = true; os << x; } return os; }
    template<typename First, typename Second> istream& operator >> ( istream &is, pair<First, Second> &p ) { return is >> p.first >> p.second; }
    template<typename First> istream& operator >> ( istream &is, vector<First> &v ) { for( First &x : v ) { is >> x; } return is; }
    
    long long fastread(){ char c; long long d = 1, x = 0; do c = getchar(); while( c == ' ' || c == '\n' ); if( c == '-' ) c = getchar(), d = -1; while( isdigit( c ) ){ x = x * 10 + c - '0'; c = getchar(); } return d * x; }
    static bool sep = false;
    using std::to_string;
    string to_string( bool x ){ return ( x ? "true" : "false" ); }
    string to_string( const string & s ){ return "\"" + s + "\""; }
    string to_string( const char * s ){ return "\"" + string( s ) + "\""; }
    string to_string ( const char & c ) { string s; s += c; return "\'" + s + "\'"; }
    template<typename Type> string to_string( vector<Type> );
    template<typename First, typename Second> string to_string( pair<First, Second> );
    template<typename Collection> string to_string( Collection );
    template<typename First, typename Second> string to_string( pair<First, Second> p ){ return "{" + to_string( p.first ) + ", " + to_string( p.second ) + "}"; }
    template<typename Type> string to_string( vector<Type> v ) { bool sep = false; string s = "["; for( Type x: v ){ if( sep ) s += ", "; sep = true; s += to_string( x ); } s += "]"; return s; }
    template<typename Collection> string to_string( Collection collection ) { bool sep = false; string s = "{"; for( auto x: collection ){ if( sep ) s += ", "; sep = true; s += to_string( x ); } s += "}"; return s; }
    void print() { cerr << endl; sep = false; }
    template <typename First, typename... Other> void print( First first, Other... other ) { if( sep ) cerr << " | "; sep = true; cerr << to_string( first ); print( other... ); }
} using namespace io;

/* Points tO CONSIDER
    # RTE? -> check array bounds and constraints
    -> check if u are dividing smth by 0
    #TLE? -> thinks about binary search/ dp / optimization techniques
    # WA? 
    -> overflow,reset global variables
    -> Check corner cases
    -> use Setpre for precision problems

    #Can't Get an idea?
    -> think from different/simpler approaches
    -> Think in reverse?
    -> Read the problem statement again
    -> Check the constraints again
    -> Ignore unnecessary information, and use it to draw the problem in new ways.
    -> Characterize the problem: Suppose I did find such a solution, what would it look like? what characteristics it would have? Can we toy around with such a solution so that it remains optimal?
    -> Randomly guessing: Guess and try to prove false
    -> Finding invariants: Check which properties don't change
    -> Solving subtasks of the original problem and then trying to extend/generalize your solution.
    -> bruteforce to find pattern
    -> Making obvious lower and upper bounds, and proving they are constructible.
    -> Fixing a parameter and then trying to maximise the result with respect to that fixed parameter.
    -> Maybe take a deep breath and take a break 
    -> STRESS TESTING !!!!!!
*/
const ll M = 998244353;
const ll N = 1e6 + 10;

ll powerMod(ll x, ll y, ll p){
    ll res = 1 % p;
    x = x % p;
    while (y > 0){
        if (y & 1) res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

ll inverseMod(ll a, ll x){
    return powerMod(a, x - 2, x);
}

ll factorial[N], inv_factorial[N];

void precompute_factorials() {
    factorial[0] = 1;
    for (ll i = 1; i < N; i++) {
        factorial[i] = (factorial[i-1] * i) % M;
    }
    inv_factorial[N-1] = powerMod(factorial[N-1], M-2, M);
    for (ll i = N-2; i >= 0; i--) {
        inv_factorial[i] = (inv_factorial[i+1] * (i+1)) % M;
    }
}

ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return ((factorial[n] * inv_factorial[r]) % M * inv_factorial[n-r]) % M;
}

int main()
{
    fast;
    precompute_factorials();
    
    ll t;
    cin >> t;
    
    while (t--) {
        ll n, k;
        cin >> n >> k;
        
        vector<ll> vec(n);
        vector<ll> cnt(n + 1, 0);
        for (ll i = 0; i < n; i++) {
            cin >> vec[i];
            cnt[vec[i]]++;
        }
        
        // Special case: k = 1
        if (k == 1) {
            ll sum = 0;
            for (ll i = 0; i < n; i++) {
                sum = (sum + vec[i]) % M;
            }
            cout << sum << nn;
            continue;
        }
        
        // Get unique values > 1
        vector<ll> unique_vals;
        for (ll i = 2; i <= n; i++) {
            if (cnt[i] > 0) {
                unique_vals.push_back(i);
            }
        }
        vector<vector<ll>> dp(22, vector<ll>(n + 1, 0));
        for (ll i = 2; i <= n; i++) {
            dp[1][i] = cnt[i];
        }
        for (ll j = 1; j <= 20; j++) {
            for (ll i = 2; i <= n; i++) {
                if (dp[j][i] == 0) continue;
                for (auto val : unique_vals) {
                    if (i * 1LL * val > n) break;
                    dp[j + 1][i * val] = (dp[j + 1][i * val] + dp[j][i] * cnt[val]) % M;
                }
            }
        }
        ll ones_power[22] = {0};
        ll ones = cnt[1];
        for (ll j = 1; j <= 21; j++) {
            if (k - 1 >= j) {
                ones_power[j] = powerMod(ones, k - 1 - j, M);
            }
        }
        ll K = k - 1;
        ll nCr_val[22] = {0};
        if (K >= 0) {
            ll now = 1;
            for (ll j = 1; j <= min(21LL, K); j++) {
                if (j > K) break;
                if (j > 1) {
                    now = (now * (K - j + 1)) % M;
                    now = (now * inverseMod(j, M)) % M;
                } else {
                    now = K % M;
                }
                nCr_val[j] = now;
            }
            nCr_val[0] = 1;
        }
        
        // Calculate w[i] - ways to get i as final value
        vector<ll> w(n + 1, 0);
        
        // w[1] is special
        w[1] = powerMod(ones, K, M);
        
        for (ll i = 2; i <= n; i++) {
            for (ll j = 1; j <= min(21LL, K); j++) {
                if (dp[j][i] == 0) continue;
                if (K == j) {
                    w[i] = (w[i] + dp[j][i]) % M;
                } else {
                    ll ways = (dp[j][i] * ones_power[j]) % M;
                    ways = (ways * nCr_val[j]) % M;
                    w[i] = (w[i] + ways) % M;
                }
            }
        }
        
        // Prefix sum for counting numbers in range
        vector<ll> pre(n + 1, 0);
        for (ll i = 1; i <= n; i++) {
            pre[i] = (pre[i-1] + cnt[i]) % M;
        }
        
        // Calculate final answer
        ll ans = 0;
        for (ll i = 1; i <= n; i++) {
            if (w[i] == 0) continue;
            for (ll j = i; j <= n; j += i) {
                ll r = min(n, j + i - 1);
                ll count_in_range = (pre[r] - pre[j-1] + M) % M;
                ans = (ans + (w[i] * count_in_range % M * (j / i) % M)) % M;
            }
        }
        
        cout << ans << nn;
    }
    
    return 0;
}