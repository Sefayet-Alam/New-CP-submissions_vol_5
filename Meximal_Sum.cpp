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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll M = 1e9 + 7;

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

const ll INF = 1LL << 60;
 
struct Interval {
    int st, en, val;
};
 
pair<vector<ll>, vector<ll>> build_suffix(const vector<ll>& P, int R_bound) {
    vector<ll> suf_min(R_bound + 2), suf_max(R_bound + 2);
    suf_min[R_bound] = P[R_bound];
    suf_max[R_bound] = P[R_bound];
    for (int i = R_bound - 1; i >= 1; i--) {
        suf_min[i] = min(P[i], suf_min[i + 1]);
        suf_max[i] = max(P[i], suf_max[i + 1]);
    }
    return {suf_min, suf_max};
}
 
pair<ll, ll> solve_case(int N, const vector<int>& A) {
    vector<ll> P(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        P[i] = P[i - 1] + A[i - 1];
    }
    ll T = P[N];
    unordered_set<int> s;
    for (int x : A) s.insert(x);
    int g = 0;
    while (s.count(g)) g++;
    if (g == 0) {
        auto suf = build_suffix(P, N - 1);
        vector<ll> suf_min = suf.first, suf_max = suf.second;
        ll ans_min = INF, ans_max = -INF;
        for (int L = 1; L <= N - 2; L++) {
            ll rmin = suf_min[L + 1], rmax = suf_max[L + 1];
            ll candidate_max = 2 * P[L] + T - 2 * rmin;
            ll candidate_min = 2 * P[L] + T - 2 * rmax;
            ans_max = max(ans_max, candidate_max);
            ans_min = min(ans_min, candidate_min);
        }
        return {ans_min, ans_max};
    }
    vector<vector<int>> pos(g);
    for (int i = 1; i <= N; i++) {
        if (A[i - 1] < g) pos[A[i - 1]].push_back(i);
    }
    int L_low = 0, R_up = INT_MAX;
    for (int x = 0; x < g; x++) {
        L_low = max(L_low, pos[x][0]);
        R_up = min(R_up, pos[x].back() - 1);
    }
    if (L_low > R_up) return {-1, -1};
    auto suf = build_suffix(P, R_up);
    vector<ll> suf_min = suf.first, suf_max = suf.second;
    vector<Interval> intervals;
    for (int x = 0; x < g; x++) {
        vector<int>& arr = pos[x];
        if (arr[0] > L_low) {
            int st = L_low, en = min(R_up, arr[0] - 1);
            if (st <= en) intervals.push_back({st, en, arr[0]});
        }
        for (size_t j = 0; j + 1 < arr.size(); j++) {
            int st = max(L_low, arr[j]), en = min(R_up, arr[j + 1] - 1);
            if (st <= en) intervals.push_back({st, en, arr[j + 1]});
        }
    }
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
        return a.st < b.st;
    });
    priority_queue<pair<int, int>> pq;
    ll ans_min = INF, ans_max = -INF;
    int ptr = 0;
    bool candidate_found = false;
    for (int L = L_low; L <= R_up; L++) {
        while (ptr < intervals.size() && intervals[ptr].st == L) {
            pq.push({intervals[ptr].val, intervals[ptr].en});
            ptr++;
        }
        while (!pq.empty() && pq.top().second < L) {
            pq.pop();
        }
        if (pq.empty()) continue;
        int F_L = pq.top().first;
        int R_low_bound = max(F_L, L + 1);
        if (R_low_bound > R_up) continue;
        ll candidate_max = 2 * P[L] + T - 2 * suf_min[R_low_bound];
        ll candidate_min = 2 * P[L] + T - 2 * suf_max[R_low_bound];
        ans_max = max(ans_max, candidate_max);
        ans_min = min(ans_min, candidate_min);
        candidate_found = true;
    }
    if (!candidate_found) return {-1, -1};
    return {ans_min, ans_max};
}
int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    cin >> t;

    while (t--)
    {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        auto res = solve_case(N, A);
        cout << res.first << " " << res.second << "\n";
    }

    return 0;
}


