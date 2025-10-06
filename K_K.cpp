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


string s;
string p;
ll st, en;
void countSort(vector<ll> &p, vector<ll> &c)
{
    ll n = p.size();
    vector<ll> cnt(n);
    for (auto it : c)
        cnt[it]++;
    vector<ll> p_new(n), pos(n);
    pos[0] = 0;
    for (ll i = 1; i < n; i++)
        pos[i] = pos[i - 1] + cnt[i - 1];
    for (auto it : p)
    {
        ll i = c[it];
        p_new[pos[i]] = it;
        pos[i]++;
    }
    p = p_new;
}
pair<vl, vl> SuffixArray_LCP(string &s)
{
    s += '$';
    ll n = s.size();
    vector<pair<char, ll>> suf(n);
    for (ll i = 0; i < n; i++)
        suf[i] = {s[i], i};
    sort(suf.begin(), suf.end());
    vector<ll> p(n), c(n);
    for (ll i = 0; i < n; i++)
        p[i] = suf[i].second;
    c[p[0]] = 0;
    for (ll i = 1; i < n; i++)
    {
        if (suf[i].first == suf[i - 1].first)
            c[p[i]] = c[p[i - 1]];
        else
            c[p[i]] = c[p[i - 1]] + 1;
    }
    ll k = 0;
    while ((1 << k) < n)
    {
        for (ll i = 0; i < n; i++)
            p[i] = (p[i] - (1 << k) + n) % n;
        countSort(p, c);
        vector<ll> c_new(n);
        c_new[p[0]] = 0;
        for (ll i = 1; i < n; i++)
        {
            pair<ll, ll> last = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair<ll, ll> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            if (cur == last)
                c_new[p[i]] = c_new[p[i - 1]];
            else
                c_new[p[i]] = c_new[p[i - 1]] + 1;
        }
        c = c_new;
        k++;
    }

    vector<ll> lcp(n);
    k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        ll pi = c[i], j = p[pi - 1];
        while (s[i + k] == s[j + k])
            k++;
        lcp[pi] = k;
        k = max(k - 1, 0LL);
    }
    return {p, lcp};
}
// no of distinct substrings
unsigned ll countSubstrings(const vector<ll> &suffixArray, const vector<ll> &lcp)
{
    unsigned long long int res = suffixArray[0];
    for (ll i = 1; i < suffixArray.size(); i++)
    {
        res += suffixArray[i] - lcp[i]; // lcp is 1 based
    }
    return res;
}
//longest common substring of two strings
string findLCS(const string &s, const string &t)
{

    string tmp = s + "+" + t;
    auto pp = SuffixArray_LCP(tmp);

    auto lcp = pp.second;
    auto p = pp.first; // suffix array
    string result = "";
    int maxLength = 0, n1 = s.size(), n2 = s.size();
    for (int i = 0; i < lcp.size() - 1; i++)
    {
        bool iIsInS = (0 <= p[i] && p[i] <= n1 - 1), jIsIns = (0 <= p[i + 1] && p[i + 1] <= n1 - 1);
        // cout << i << ":" << iIsInS << " " << jIsIns << endl;
        if (iIsInS != jIsIns)
        {
            if (maxLength < lcp[i + 1])
            {
                maxLength = lcp[i + 1];
                result = s.substr(min(p[i], p[i + 1]), maxLength);
            }
        }
    }
    return result;
}
ll upperbound(ll low, ll high, vector<ll> &vec)
{
    ll mid;
    ll ans = -1;
    while (low <= high)
    {
        mid = (high + low) / 2;
        // cout<<mid<<" "<<func(mid)<<endl;
        string w = s.substr(vec[mid], min(s.size() - vec[mid], p.size() * 1LL));
        if (w < p)
        {
            low = mid + 1;
        }
        else if (w > p)
        {
            high = mid - 1;
        }
        else
        {
            ans = mid;
            low = mid + 1;
        }
    }
    return ans;
}

ll lowerbound(ll low, ll high, vector<ll> &vec)
{
    ll mid;
    ll ans = -1;
    while (low <= high)
    {
        mid = (high + low) / 2;
        // cout<<mid<<" "<<func(mid)<<endl;
        string w = s.substr(vec[mid], min(s.size() - vec[mid], p.size() * 1LL));
        if (w < p)
        {
            low = mid + 1;
        }
        else if (w > p)
        {
            high = mid - 1;
        }
        else
        {
            ans = mid;
            high = mid - 1;
        }
    }
    return ans;
}
//counts occurance as a substring in s of p
ll countoccurence(vector<ll> &sa)
{
    ll n = p.size();
    ll a = upperbound(0,sa.size()-1,sa);
    ll b = lowerbound(0,sa.size()-1,sa);
    if(a==-1) return 0;
    return a - b + 1;
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
      
    }

    return 0;
}


