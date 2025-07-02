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
struct Hopcroft_Karp
{
    static const int inf = 1e9;
    vector<vector<int>> adj;
    int n, m;
    vector<int> lef, rig, dis;
    queue<int> q;

    Hopcroft_Karp(int n, int m) : n(n), m(m)
    {
        int p = n + m + 1;
        adj.resize(n + 1);  // Only need n+1 for left nodes
        lef.resize(n + 1, 0);
        rig.resize(m + 1, 0);  // Separate right nodes
        dis.resize(n + 1, 0);
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);  // No need for v + n adjustment
    }

    bool bfs()
    {
        for (int i = 1; i <= n; i++)
        {
            if (!lef[i])
            {
                dis[i] = 0;
                q.push(i);
            }
            else
                dis[i] = inf;
        }

        bool found = false;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (!rig[v])
                {
                    found = true;
                }
                else if (dis[rig[v]] == inf)
                {
                    dis[rig[v]] = dis[u] + 1;
                    q.push(rig[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u)
    {
        for (int v : adj[u])
        {
            if (!rig[v] || (dis[rig[v]] == dis[u] + 1 && dfs(rig[v])))
            {
                lef[u] = v;
                rig[v] = u;
                return true;
            }
        }
        dis[u] = inf;
        return false;
    }

    ll matching()
    {
        ll max_matching = 0;
        while (bfs())
        {
            for (int i = 1; i <= n; i++)
            {
                if (!lef[i] && dfs(i))
                    max_matching++;
            }
        }
        return max_matching;
    }
};


void solve()
{
    int n;
    cin >> n;
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++)
        cin >> a[i];
    vector<vector<int>> same(n + 1), diff;
    for (int i = 0; i < n; i++)
    {
        int x = a[2 * i], y = a[2 * i + 1];
        if (x == y)
            same[x].push_back(i);
        else
            diff.push_back({i, x, y});
    }
    vector<char> vis1(n, 0), vis2(n + 1, 0);
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!same[i].empty())
        {
            int j = same[i].back();
            vis1[j] = 1;
            vis2[i] = 1;
            res++;
        }
    }
    Hopcroft_Karp hop(n, n);
    for (auto &t : diff)
    {
        int i = t[0], x = t[1], y = t[2];
        if (vis1[i])
            continue;
        if (!vis2[x])
            hop.add_edge(i, x - 1);
        if (!vis2[y] && y != x)
            hop.add_edge(i, y - 1);
    }
    for (int v = 1; v <= n; v++)
    {
        if (same[v].size() > 1)
        {
            for (int k = 0; k < (int)same[v].size(); k++)
            {
                int i = same[v][k];
                if (vis1[i])
                    continue;
                if (!vis2[v])
                    hop.add_edge(i, v - 1);
            }
        }
    }
    int match = hop.matching();
    int temp = 2 * res + 1 * match;
    int ans = 2 * n - temp;
    cout << ans << endl;
}

int32_t main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}


