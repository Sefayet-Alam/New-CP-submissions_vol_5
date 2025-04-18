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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;

const ll N=1010;
typedef pair<ll, ll> pll;

int n, m, a, b;
int h[N][N]; 
ll temp[N][N], temp2[N][N];
deque<pll> dq, dq2;

void add(deque<pll> &dq, int val, int idx, bool isMax) {
    while (!dq.empty() && ((isMax && dq.back().first <= val) || (!isMax && dq.back().first >= val))) {
        dq.pop_back();
    }
    dq.push_back({val, idx});
}

void del(deque<pll> &dq, int idx) {
    if (!dq.empty() && dq.front().second == idx) dq.pop_front();
}

void init(deque<pll> &dq) {
    dq.clear();
}

ll solve() {
    ll q;
    cin >> n >> m >> a >> q;
    b = a; // Submatrix size a*b
    
    // Initialize h with -1
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            h[i][j] = -1;
        }
    }
    
    // Input values
    while (q--) {
        ll x, y, z;
        cin >> x >> y >> z;
        h[x][y] = z;
    }

    ll ans = 1e18;

    // Step 1: Compute row-wise max (temp) and row-wise min (temp2)
    for (int i = 1; i <= n; i++) {
        init(dq);
        init(dq2);
        
        for (int j = 1; j <= b; j++) {
            add(dq, h[i][j], j, true);  // Find maximum
            add(dq2, h[i][j], j, false); // Find minimum
        }
        
        temp[i][1] = dq.front().first;
        temp2[i][1] = dq2.front().first;
        
        for (int j = b + 1; j <= m; j++) {
            del(dq, j - b);
            del(dq2, j - b);
            add(dq, h[i][j], j, true);
            add(dq2, h[i][j], j, false);
            temp[i][j - b + 1] = dq.front().first;
            temp2[i][j - b + 1] = dq2.front().first;
        }
    }

    // Step 2: Compute column-wise sliding window min/max
    for (int j = 1; j <= (m - b + 1); j++) {
        init(dq);
        init(dq2);

        for (int i = 1; i <= a; i++) {
            add(dq, temp[i][j], i, true);
            add(dq2, temp2[i][j], i, false);
        }

        ll now1 = dq.front().first;
        ll now2 = dq2.front().first;
 
        if (now2 > -1) ans = min(ans, now1);

        for (int i = a + 1; i <= n; i++) {
            del(dq, i - a);
            del(dq2, i - a);
            add(dq, temp[i][j], i, true);
            add(dq2, temp2[i][j], i, false);
            
            now1 = dq.front().first;
            now2 = dq2.front().first;

            if (now2 > -1) ans = min(ans, now1);
        }
    }

    return ans;
}


int main()
{
    
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    ll ret=solve();
    if(ret>1e17) cout<<-1<<nn;
    else cout<<ret<<nn;

    return 0;
}



