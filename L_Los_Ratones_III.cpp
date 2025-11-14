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

#define pb push_back
const ll sz = 1e5 + 10;
vector<ll> g[sz];
ll sub[sz], in[sz], out[sz], head[sz], tim;
ll par[sz], tr[4 * sz];

void dfs_siz(ll u, ll p)
{
    sub[u] = 1, par[u] = p;
    for (ll &v : g[u])
    {
        if (v == p)
            continue;
        dfs_siz(v, u);
        sub[u] += sub[v];
        if (sub[v] > sub[g[u][0]])
            swap(v, g[u][0]);
    }
}

/* DFS for Heavy-Light Decomposition
 * head[u] = Head of the chain of node u
 * Operations can be performed in [in[head[u]],in[u]] range.
 * As DFS-time is used, [in[u],out[u]] range can be used
   for performing operations on the subtree of node u.
*/
void dfs_hld(ll u, ll p)
{
    if (p == -1)
        head[u] = u; // root
    in[u] = ++tim;
    for (ll &v : g[u])
    {
        if (v == p)
            continue;
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v, u);
    }
    out[u] = tim;
}

// Typical Segment Tree on [1, tim] range
void build(ll lo, ll hi, ll node)
{
    if (lo == hi)
    {
        tr[node] = 0;
        return;
    }
    ll mid = lo + hi >> 1, lft = node << 1, rgt = lft | 1;
    build(lo, mid, lft);
    build(mid + 1, hi, rgt);
    tr[node] = 0;
}

void update(ll lo, ll hi, ll idx, ll v, ll node)
{
    if (lo > idx || hi < idx)
        return;
    if (lo == hi)
    {
        tr[node] = v;
        return;
    }
    ll mid = lo + hi >> 1, lft = node << 1, rgt = lft | 1;
    update(lo, mid, idx, v, lft);
    update(mid + 1, hi, idx, v, rgt);
    tr[node] = tr[lft] + tr[rgt];
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if (lo > r || hi < l)
        return 0;
    if (lo >= l && hi <= r)
        return tr[node];
    ll mid = lo + hi >> 1, lft = node << 1, rgt = lft | 1;
    return query(lo, mid, l, r, lft) + query(mid + 1, hi, l, r, rgt);
}
// Segment Tree Ends

inline bool isAncestor(int p, int u)
{
    return in[p] <= in[u] && out[p] >= out[u];
}

void upd_val(ll u, ll val)
{
    update(1, tim, in[u], val, 1);
}

ll query_path(ll u, ll v)
{
    ll ret = 0;
    while (!isAncestor(head[u], v))
    {
        ret += query(1, tim, in[head[u]], in[u], 1);
        u = par[head[u]];
    }
    swap(u, v);
    while (!isAncestor(head[u], v))
    {
        ret += query(1, tim, in[head[u]], in[u], 1);
        u = par[head[u]];
    }
    if (in[v] < in[u])
        swap(u, v);
    ret += query(1, tim, in[u], in[v], 1); // u is LCA
    return ret;
}

void clr(ll n)
{
    tim = 0;
    for (ll i = 1; i <= n; i++)
        g[i].clear();
}
int main()
{
    ll t = 1, n, q, u, v, w, x, op, root = 1;
    // cin >> t;
    while (t--)
    {
        scanf("%lld", &n);
        clr(n);

        for (ll i = 1; i < n; i++)
        {
            cin>>u>>v>>w;
            g[u].pb(v), g[v].pb(u);
        }

        dfs_siz(root, -1);
        dfs_hld(root, -1);
        build(1, tim, 1);

        scanf("%lld", &q);
        while (q--)
        {
            scanf("%lld %lld %lld", &op, &u, &v);
            if (op == 1)
                upd_val(u, v);
            else
                printf("%lld\n", query_path(u, v));
        }
    }
    return 0;
}