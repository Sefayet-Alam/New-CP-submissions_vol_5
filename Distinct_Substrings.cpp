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


struct SuffixAutomaton
{
    struct State
    {
        map<char, ll> next;
        ll link = -1, len = 0, first_pos = -1;
        ll cnt = 0; // occurrence count used for frequency-based queries
    };

    vector<State> st;
    ll last;
    vector<ll> terminals;
    vector<vector<ll>> children;
    vector<bool> isTerminal;

    vector<ll> dpDistinct; // memo for counting distinct substrings starting at state
    vector<ll> dpFreq;     // memo for counting freq substrings starting at state
    vector<ll> dpOccur;    // memo for counting occurrences of substrings from a node

    SuffixAutomaton(string s)
    {
        st.push_back(State());
        last = 0;

        for (ll i = 0; i < (ll)s.size(); i++)
        {
            char c = s[i];
            st.push_back(State());
            ll cur = st.size() - 1;
            st[cur].len = i + 1;
            st[cur].first_pos = i;
            st[cur].cnt = 1; // every new state (non-clone) counts as 1 occurrence initially

            ll p = last;
            while (p != -1 && !st[p].next.count(c))
            {
                st[p].next[c] = cur;
                p = st[p].link;
            }
            if (p == -1)
            {
                st[cur].link = 0;
            }
            else
            {
                ll q = st[p].next[c];
                if (st[p].len + 1 == st[q].len)
                {
                    st[cur].link = q;
                }
                else
                {
                    st.push_back(st[q]);
                    ll clone = st.size() - 1;
                    st[clone].len = st[p].len + 1;
                    st[clone].first_pos = st[q].first_pos;
                    st[clone].cnt = 0; // clone node doesn't count as new occurrence
                    while (p != -1 && st[p].next[c] == q)
                    {
                        st[p].next[c] = clone;
                        p = st[p].link;
                    }
                    st[q].link = st[cur].link = clone;
                }
            }
            last = cur;
        }

        // Calculate terminals by suffix links from last
        ll p = last;
        while (p > 0)
        {
            terminals.push_back(p);
            p = st[p].link;
        }

        isTerminal.assign(st.size(), false);
        for (ll x : terminals)
            isTerminal[x] = true;

        // Build children for suffix tree representation
        children.assign(st.size(), {});
        for (ll i = 1; i < (ll)st.size(); i++)
            children[st[i].link].push_back(i);

        // Prepare dp arrays
        dpDistinct.assign(st.size(), -1);
        dpFreq.assign(st.size(), -1);
        dpOccur.assign(st.size(), -1);

        // Calculate cnt propagation (occurrences) from leaves to root (topological order by len desc)
        vector<pair<ll, ll>> order; // pair(len, index)
        for (ll i = 0; i < (ll)st.size(); i++)
            order.emplace_back(st[i].len, i);
        sort(order.rbegin(), order.rend()); // descending by len
        for (auto &[len, idx] : order)
        {
            if (st[idx].link != -1)
                st[st[idx].link].cnt += st[idx].cnt;
        }
    }

    // 1) Check if w is substring
    bool isSubstring(const string &w)
    {
        ll node = 0;
        for (char c : w)
        {
            if (!st[node].next.count(c))
                return false;
            node = st[node].next[c];
        }
        return true;
    }

    // 2) Check if w is suffix
    bool isSuffix(const string &w)
    {
        ll node = 0;
        for (char c : w)
        {
            if (!st[node].next.count(c))
                return false;
            node = st[node].next[c];
        }
        return isTerminal[node];
    }

    // 3) Count number of distinct substrings
    ll countDistinctSubstrings()
    {
        return dfsDistinct(0) - 1; // subtract empty substring
    }

    // 4) Count occurrences of w
    ll countOccurrences(const string &w)
    {
        ll node = 0;
        for (char c : w)
        {
            if (!st[node].next.count(c))
                return 0;
            node = st[node].next[c];
        }
        return dfsOccur(node);
    }

    // 5) First occurrence of w (1-based)
    ll firstOccurrence(const string &w)
    {
        ll node = 0;
        for (char c : w)
        {
            if (!st[node].next.count(c))
                return -1;
            node = st[node].next[c];
        }
        return st[node].first_pos - (ll)w.size() + 2;
    }

    // 6) All positions where w occurs (sorted, 0-based indexing)
    vector<ll> allOccurrences(const string &w)
    {
        ll node = 0;
        for (char c : w)
        {
            if (!st[node].next.count(c))
                return {};
            node = st[node].next[c];
        }
        vector<ll> res;
        dfsAllPositions(node, (ll)w.size(), res);
        sort(res.begin(), res.end());
        return res;
    }

    // 7) kth distinct substring (lex order)
    string kthDistinctSubstring(ll k)
    {
        string res;
        ll u = 0;
        while (k > 0)
        {
            if (k == 1)
                return res;
            k--;
            bool found = false;
            for (char c = 'a'; c <= 'z'; c++)
            {
                if (!st[u].next.count(c))
                    continue;
                ll v = st[u].next[c];
                ll cnt = dfsDistinct(v);
                if (cnt >= k)
                {
                    res.push_back(c);
                    u = v;
                    found = true;
                    break;
                }
                else
                    k -= cnt;
            }
            if (!found)
                break;
        }
        return res;
    }

private:
    // DFS for counting distinct substrings starting from u
    ll dfsDistinct(ll u)
    {
        if (dpDistinct[u] != -1)
            return dpDistinct[u];
        ll res = 1; // count empty substring here
        for (auto &p : st[u].next)
            res += dfsDistinct(p.second);
        return dpDistinct[u] = res;
    }

    // DFS for counting substrings with duplicates (frequencies)
    ll dfsFreq(ll u)
    {
        if (dpFreq[u] != -1)
            return dpFreq[u];
        ll res = st[u].cnt; // occurrences of substring represented by this node
        for (auto &p : st[u].next)
            res += dfsFreq(p.second);
        return dpFreq[u] = res;
    }

    // DFS for counting number of occurrences of substrings starting at node u
    ll dfsOccur(ll u)
    {
        if (dpOccur[u] != -1)
            return dpOccur[u];
        ll res = isTerminal[u] ? 1 : 0;
        for (ll v : children[u])
            res += dfsOccur(v);
        return dpOccur[u] = res;
    }

    // DFS for collecting all occurrences positions for substring w
    void dfsAllPositions(ll u, ll lenW, vector<ll> &res)
    {
        if (children[u].empty())
            res.push_back(st[u].len - lenW);
        for (ll v : children[u])
            dfsAllPositions(v, lenW, res);
    }
};
int main()
{
    fast;
    string s;
    cin>>s;
    SuffixAutomaton SA(s);
    cout<<SA.countDistinctSubstrings()<<nn;

    return 0;
}


