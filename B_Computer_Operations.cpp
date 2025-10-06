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

// Printings & debugging
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
namespace io
{
    template <typename First, typename Second>
    ostream &operator<<(ostream &os, const pair<First, Second> &p) { return os << p.first << " " << p.second; }
    template <typename First, typename Second>
    ostream &operator<<(ostream &os, const map<First, Second> &mp)
    {
        for (auto it : mp)
        {
            os << it << endl;
        }
        return os;
    }
    template <typename First>
    ostream &operator<<(ostream &os, const vector<First> &v)
    {
        bool space = false;
        for (First x : v)
        {
            if (space)
                os << " ";
            space = true;
            os << x;
        }
        return os;
    }
    template <typename First>
    ostream &operator<<(ostream &os, const set<First> &st)
    {
        bool space = false;
        for (First x : st)
        {
            if (space)
                os << " ";
            space = true;
            os << x;
        }
        return os;
    }
    template <typename First>
    ostream &operator<<(ostream &os, const multiset<First> &st)
    {
        bool space = false;
        for (First x : st)
        {
            if (space)
                os << " ";
            space = true;
            os << x;
        }
        return os;
    }
    template <typename First, typename Second>
    istream &operator>>(istream &is, pair<First, Second> &p) { return is >> p.first >> p.second; }
    template <typename First>
    istream &operator>>(istream &is, vector<First> &v)
    {
        for (First &x : v)
        {
            is >> x;
        }
        return is;
    }

    long long fastread()
    {
        char c;
        long long d = 1, x = 0;
        do
            c = getchar();
        while (c == ' ' || c == '\n');
        if (c == '-')
            c = getchar(), d = -1;
        while (isdigit(c))
        {
            x = x * 10 + c - '0';
            c = getchar();
        }
        return d * x;
    }
    static bool sep = false;
    using std::to_string;
    string to_string(bool x) { return (x ? "true" : "false"); }
    string to_string(const string &s) { return "\"" + s + "\""; }
    string to_string(const char *s) { return "\"" + string(s) + "\""; }
    string to_string(const char &c)
    {
        string s;
        s += c;
        return "\'" + s + "\'";
    }
    template <typename Type>
    string to_string(vector<Type>);
    template <typename First, typename Second>
    string to_string(pair<First, Second>);
    template <typename Collection>
    string to_string(Collection);
    template <typename First, typename Second>
    string to_string(pair<First, Second> p) { return "{" + to_string(p.first) + ", " + to_string(p.second) + "}"; }
    template <typename Type>
    string to_string(vector<Type> v)
    {
        bool sep = false;
        string s = "[";
        for (Type x : v)
        {
            if (sep)
                s += ", ";
            sep = true;
            s += to_string(x);
        }
        s += "]";
        return s;
    }
    template <typename Collection>
    string to_string(Collection collection)
    {
        bool sep = false;
        string s = "{";
        for (auto x : collection)
        {
            if (sep)
                s += ", ";
            sep = true;
            s += to_string(x);
        }
        s += "}";
        return s;
    }
    void print()
    {
        cerr << endl;
        sep = false;
    }
    template <typename First, typename... Other>
    void print(First first, Other... other)
    {
        if (sep)
            cerr << " | ";
        sep = true;
        cerr << to_string(first);
        print(other...);
    }
}
using namespace io;

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


ll n;
vector<ll> a(N);
vector<ll> g[N];
ll dp[N][2][2];
// dp[u][op_u][child_xor_sum] = min_cost
/*
child_xor_sum: This represents the XOR sum of the operations performed
on the immediate children of u. For example, if u has children c1, c2, c3,
this value is op(c1) ^ op(c2) ^ op(c3). This single value is sufficient
because in the state equation for node u, the individual operations on
children only appear as an XOR sum.

min_cost: The value stored in the DP table.
It is the minimum number of operations required
within the entire subtree of u (including u itself if op_u=1) to
satisfy the 'on' condition for every single node in that subtree,
*/

void dfs(int vertex, int par = -1)
{
    // Initialize base costs for operating or not on u itself
    dp[vertex][0][0] = 0; // The child_xor_sum is 0 as there are no children yet.
    dp[vertex][0][1] = M; // children take= unknown cost=infinity
    dp[vertex][1][0] = 1;
    dp[vertex][1][1] = M;

    for (auto child : g[vertex])
    {
        if (child == par)
            continue;
        dfs(child, vertex);
        ll tempdp[2][2];
        mem(tempdp, M);

        // Iterate over choices for op(u)
        for (ll opu = 0; opu < 2; opu++) // make operation on vertex->opu
        {
            for (ll childxr = 0; childxr < 2; childxr++)
            {
                // if (dp[vertex][opu][childxr] == M)
                //     continue;

                for (ll opv = 0; opv < 2; opv++) // make operation on children->opv
                {
                    // Equation for node v:
                    // A[v] ^ opv ^ op_u ^ (grandchild_xor_sum) = 1
                    ll grandchxr = 1 ^ a[child] ^ opv ^ opu;

                    if (dp[child][opv][grandchxr] != M)
                    {
                        ll curcost = dp[vertex][opu][childxr];
                        ll child_cost = dp[child][opv][grandchxr];
                        ll newchildxr = childxr ^ opv;

                        tempdp[opu][newchildxr] = min(tempdp[opu][newchildxr], curcost + child_cost);
                    }
                }
            }
        }

        // Update dp[u] with the combined results
        for (ll i = 0; i < 2; i++)
            for (ll j = 0; j < 2; j++)
                dp[vertex][i][j] = tempdp[i][j];
    }
}
void reset(ll n)
{
    for (ll i = 0; i <= n; i++)
    {
        g[i].clear();
    }
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
        cin >> n;
        a.resize(n);
        cin >> a;
        reset(n);
        for (ll i = 0; i < n - 1; i++)
        {
            ll x, y;
            cin >> x >> y;
            x--;
            y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs(0);
        ll cost = M;

        // Case 1: op(root) = 0. Parent op is 0.
        // Equation for root: A[0] ^ op(0) ^ op(parent) ^ child_xor_sum = 1
        // A[0] ^ 0 ^ 0 ^ child_xor_sum = 1  => child_xor_sum = 1 ^ A[0]
        ll reqcxrsum0 = 1 ^ a[0];
        cost = min(cost, dp[0][0][reqcxrsum0]);

        // Case 2: op(root) = 1. Parent op is 0.
        // A[0] ^ 1 ^ 0 ^ child_xor_sum = 1  => child_xor_sum = 1 ^ A[0] ^ 1
        ll reqcxsum1 = a[0];
        cost = min(cost, dp[0][1][reqcxsum1]);
        if(cost<M) cout<<"YES"<<nn;
        else cout<<"NO"<<nn;
    }

    return 0;
}
