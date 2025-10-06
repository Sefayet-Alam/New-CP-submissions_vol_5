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

#define ll long long int
#define lc ((node) << 1)
#define rc ((node) << 1 | 1)
#define pb push_back
#define all(x) x.begin(), x.end()

struct MergeSortTree
{
    int n;
    vector<vector<ll>> st;
    ll min_val, max_val;

    MergeSortTree(const vector<ll> &arr)
    {
        n = arr.size();
        st.resize(4 * n);
        build(1, 0, n - 1, arr);
        if (!arr.empty())
        {
            min_val = st[1].front();
            max_val = st[1].back();  
        }
    }

    void build(int node, int start, int end, const vector<ll> &arr)
    {
        if (start == end)
        {
            st[node].pb(arr[start]);
            return;
        }
        int mid = start + (end - start) / 2;
        build(lc, start, mid, arr);
        build(rc, mid + 1, end, arr);
        st[node].resize(st[lc].size() + st[rc].size());
        merge(all(st[lc]), all(st[rc]), st[node].begin());
    }

    // Internal helper to query count of elements <= val in range [l, r].
    ll query_internal(int node, int start, int end, int l, int r, ll val)
    {
        if (r < start || end < l)
        {
            return 0;
        }
        if (l <= start && end <= r)
        {
            return upper_bound(all(st[node]), val) - st[node].begin();
        }
        int mid = start + (end - start) / 2;
        ll p1 = query_internal(lc, start, mid, l, r, val);
        ll p2 = query_internal(rc, mid + 1, end, l, r, val);
        return p1 + p2;
    }

    // Finds the k-th smallest element in the subarray range [l, r].
    ll find_kth(int l, int r, int k)
    {
        ll low = min_val, high = max_val, ans = -1;
        while (low <= high)
        {
            ll mid_val = low + (high - low) / 2;
            ll count_le = query_internal(1, 0, n - 1, l, r, mid_val);
            if (count_le >= k)
            {
                ans = mid_val;
                high = mid_val - 1;
            }
            else
            {
                low = mid_val + 1;
            }
        }
        return ans;
    }
};

bool cmp(pll a, pll b)
{
    if (a.first != b.first)
        return a.first > b.first;
    return a.second < b.second;
}
int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    // cin >> t;

    while (t--)
    {
        ll n;
        cin >> n;

        vector<ll> vec(n);
        for (ll i = 0; i < n; i++)
            cin >> vec[i];

        vector<pll> pars;
        for (ll i = 0; i < n; i++)
        {
            pars.push_back({vec[i], i});
        }
        sort(all(pars), cmp);
        // for (auto it : pars)
        //     deb(it);
        vector<ll> sorted_inds(n);

        for (ll i = 0; i < n; i++)
        {
            sorted_inds[i] = pars[i].second;
        }

        MergeSortTree mst(sorted_inds);
        ll m;
        cin >> m;
        while (m--)
        {
            ll k, x;
            cin >> k >> x;

            ll ans = mst.find_kth(0, k - 1, x);

            cout << vec[ans] << nn;
        }
    }

    return 0;
}
