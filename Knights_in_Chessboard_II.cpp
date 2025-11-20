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
        adj.resize(p);
        lef.resize(p, 0);
        rig.resize(p, 0);
        dis.resize(p, 0);
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v + n);
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

        dis[0] = inf;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i];
                if (dis[rig[v]] == inf)
                {
                    dis[rig[v]] = dis[u] + 1;
                    q.push(rig[v]);
                }
            }
        }

        return dis[0] != inf;
    }

    bool dfs(int u)
    {
        if (!u)
            return true;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (dis[rig[v]] == dis[u] + 1 && dfs(rig[v]))
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

ll m, n, k;
map<pll, ll> broke;
vpll knight = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
bool isok(ll x, ll y)
{
    return (x >= 0 && x < m && y >= 0 && y < n && broke.find({x, y}) == broke.end());
}
int main()
{
    fast;
    ll t;
    // setIO();
    ll tno = 1;
    t = 1;
    cin >> t;

    while (t--)
    {
        cout << "Case " << tno++ << ": ";

        ll m, n, k;
        cin >> m >> n >> k;
        set<pll> broke;
        for (ll i = 0; i < k; i++)
        {
            ll x, y;
            cin >> x >> y;
            broke.insert({x - 1, y - 1});
        }

        map<pll, ll> idx;
        ll idx_cnt = 1;
        map<pll, bool> left_node; 
        for (ll i = 0; i < m; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (broke.count({i, j}) == 0)
                {
                    idx[{i, j}] = idx_cnt++;
                    left_node[{i, j}] = ((i + j) % 2 == 0);
                }
            }
        }

        ll left_cnt = 0;
        ll right_cnt = 0;
        for (auto &p : left_node)
        {
            if (p.second)
                left_cnt++;
            else
                right_cnt++;
        }

        Hopcroft_Karp hg(left_cnt, right_cnt);

        map<pll, ll> left_idx, right_idx;
        ll l_id = 1, r_id = 1;
        for (auto &p : left_node)
        {
            if (p.second)
                left_idx[p.first] = l_id++;
            else
                right_idx[p.first] = r_id++;
        }

        for (auto &p : left_node)
        {
            if (!p.second)
                continue; 
            ll i = p.first.first;
            ll j = p.first.second;
            ll u = left_idx[{i, j}];
            for (auto move : knight)
            {
                ll ni = i + move.first;
                ll nj = j + move.second;
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && broke.count({ni, nj}) == 0)
                {
                    ll v = right_idx[{ni, nj}];
                    hg.add_edge(u, v);
                }
            }
        }

        ll total_free = idx_cnt - 1;
        ll ans = total_free - hg.matching();
        cout << ans << "\n";
    }
}
