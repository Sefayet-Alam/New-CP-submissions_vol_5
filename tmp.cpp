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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;


class Solution {
    int i = 0;

    inline long long factor(string &s) {
        if (s[i] == '+' || s[i] == '-') {
            char sign = s[i++];
            long long v = factor(s);
            return sign == '-' ? -v : v;
        }
        if (s[i] == '(') {
            i++;
            long long v = expr(s);
            i++; // ')'
            return v;
        }
        long long num = 0;
        while (i < s.size() && isdigit(s[i]))
            num = num * 10 + (s[i++] - '0');
        return num;
    }

    long long term(string &s) {
        long long v = factor(s);
        while (i < s.size() && (s[i] == '*' || s[i] == '/')) {
            char op = s[i++];
            long long r = factor(s);
            v = (op == '*') ? v * r : v / r;
        }
        return v;
    }

    long long expr(string &s) {
        long long v = term(s);
        while (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            char op = s[i++];
            long long r = term(s);
            v = (op == '+') ? v + r : v - r;
        }
        return v;
    }

public:
    int calculate(string s) {
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        return expr(s);
    }
};


int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    string a;
    cin>>a;
    Solution sln;
    cout<<sln.calculate(a)<<nn;

    return 0;
}


const ll sz = 1009;
vector<ll> g[sz];
ll low[sz], start[sz], TM = 1, root = 1;
bool artPoint[sz], vis[sz];
ordered_map<pll, ll> mpp;
vector<ll> par(sz, -1);
void artdfs(ll u, ll p)
{
    low[u] = start[u] = TM++;
    vis[u] = 1;
    ll child = 0; /// Counter of the children of u in dfs tree
    for (ll i = 0; i < g[u].size(); i++)
    {
        ll v = g[u][i];
        if (v == p)
            continue;

        if (!vis[v])
        {
            par[v] = u;
            artdfs(v, u);
            low[u] = min(low[u], low[v]);

            if (start[u] < low[v])
            {                       /// For articulation bridge: if(start[u] < low[v])
                artPoint[u] = true; /// the edge between u and v is an articulation bridge
                // if(u>v) swap(u,v);
                mpp[{u, v}] = mpp[{v, u}] = 1;
            }
            // if (mpp.find({v, u}) == mpp.end())
            //     mpp[{u, v}] = 1; // add this to find minimum no of edges to keep the graph connected
            child++;
        }
        else if (par[u] != v)
        {
            low[u] = min(low[u], start[v]);
            // if (mpp.find({v, u}) == mpp.end())
            //     mpp[{u, v}] = 1; // add this to find minimum no of edges to keep the graph connected
        }
    }
}

// artdfs(root, -1)
void reset(ll n)
{
    TM = 1, root = 1;
    for (ll i = 0; i <= n + 2; i++)
    {
        g[i].clear();
        vis[i] = artPoint[i] = 0;
        low[i] = start[i] = 0;
        par[i] = -1;
    }
    mpp.clear();
}