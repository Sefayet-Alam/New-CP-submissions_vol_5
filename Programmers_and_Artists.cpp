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


inline ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a * b / GCD(a, b); }
inline double logb(ll base, ll num) { return (double)log(num) / (double)log(base); }


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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;

struct Applicant {
    ll x;
    ll y;
    ll diff;
    bool is_programmer;
    bool is_artist;
};

bool compareByDiff(const Applicant& a, const Applicant& b) {
    if (a.diff != b.diff) return a.diff > b.diff;
    return a.x > b.x; 
}

void solve() {
    int a, b, n;
    if (!(cin >> a >> b >> n)) return;

    vector<Applicant> applicants(n);
    for (int i = 0; i < n; ++i) {
        cin >> applicants[i].x >> applicants[i].y;
        applicants[i].diff = applicants[i].x - applicants[i].y;
        applicants[i].is_programmer = false;
        applicants[i].is_artist = false;
    }

    // 1. Sort all applicants by the difference (x - y) in descending order.
    sort(all(applicants), compareByDiff);

    // Initial Selection: Top 'a' by diff are the tentative programmers (P)
    for (int i = 0; i < a; ++i) {
        applicants[i].is_programmer = true;
    }

    // 2. Initial Selection of Artists (A) from the remaining set (R = N \ P)
    vector<Applicant*> remaining_r_pointers;
    for (int i = a; i < n; ++i) {
        remaining_r_pointers.push_back(&applicants[i]);
    }

    // Sort the remaining by artistic skill (y) in descending order.
    sort(all(remaining_r_pointers), [](Applicant* pa, Applicant* pb) {
        return pa->y > pb->y;
    });

    // Select the top 'b' from the remaining as artists.
    for (int i = 0; i < min(b, (int)remaining_r_pointers.size()); ++i) {
        remaining_r_pointers[i]->is_artist = true;
    }

    // --- Optimization Step: Check for a beneficial programmer replacement ---
    // The simple greedy (by diff) might miss a programmer with a very large x
    // who was not in the top 'a' of the diff sort. 
    // The only beneficial swap is: programmer k (smallest x in P) -> unhired, 
    // unhired candidate l (largest x in U = R \ A) -> programmer.

    // 3. Find the minimum x in the current programmer set P (x_min_P)
    ll x_min_P = -1;
    Applicant* worst_programmer = nullptr;
    for (int i = 0; i < a; ++i) {
        if (applicants[i].is_programmer) { // Should be true for i < a
            if (applicants[i].x < x_min_P || x_min_P == -1) {
                x_min_P = applicants[i].x;
                worst_programmer = &applicants[i];
            }
        }
    }

    // 4. Find the maximum x in the unhired set U = N \ (P U A) (x_max_U)
    ll x_max_U = -1;
    Applicant* best_unhired_candidate = nullptr;

    for (int i = 0; i < n; ++i) {
        if (!applicants[i].is_programmer && !applicants[i].is_artist) {
            if (applicants[i].x > x_max_U) {
                x_max_U = applicants[i].x;
                best_unhired_candidate = &applicants[i];
            }
        }
    }

    // 5. If swapping is beneficial:
    if (worst_programmer && best_unhired_candidate && x_max_U > x_min_P) {
        // Swap their roles: worst_programmer -> unhired, best_unhired_candidate -> programmer
        worst_programmer->is_programmer = false;
        best_unhired_candidate->is_programmer = true;
    }
    
    // 6. Calculate the final total skill sum
    ll total_skill_sum = 0;
    for (int i = 0; i < n; ++i) {
        if (applicants[i].is_programmer) {
            total_skill_sum += applicants[i].x;
        } else if (applicants[i].is_artist) {
            total_skill_sum += applicants[i].y;
        }
    }

    cout << total_skill_sum << nn;
}

int main()
{
    fast;
    ll t;
    t = 1;

    while (t--)
    {
        solve();
    }

    return 0;
}