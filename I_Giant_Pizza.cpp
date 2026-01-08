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

/*
zero Indexed
we have vars variables
F=(x_0 XXX y_0) and (x_1 XXX y_1) and ... (x_{vars-1} XXX y_{vars-1})
here {x_i,y_i} are variables
and XXX belongs to {OR,XOR}
is there any assignment of variables such that F=true
*/
struct twosat
{
    int n; // total size combining +, -. must be even.
    vector<vector<int>> g, gt;
    vector<bool> vis, res;
    vector<int> comp;
    stack<int> ts;
    twosat(int vars = 0)
    {
        n = vars << 1;
        g.resize(n);
        gt.resize(n);
    }

    // zero indexed, be careful
    // if you want to force variable a to be true in OR or XOR combination
    // add addOR (a,1,a,1);
    // if you want to force variable a to be false in OR or XOR combination
    // add addOR (a,0,a,0);

    //(x_a or (not x_b))-> af=1,bf=0
    void addOR(int a, bool af, int b, bool bf)
    {
        a += a + (af ^ 1);
        b += b + (bf ^ 1);
        g[a ^ 1].push_back(b); // !a => b
        g[b ^ 1].push_back(a); // !b => a
        gt[b].push_back(a ^ 1);
        gt[a].push_back(b ^ 1);
    }
    //(!x_a xor !x_b)-> af=0, bf=0
    void addXOR(int a, bool af, int b, bool bf)
    {
        addOR(a, af, b, bf);
        addOR(a, !af, b, !bf);
    }
    void _add(int a, bool af, int b, bool bf)
    {
        a += a + (af ^ 1);
        b += b + (bf ^ 1);
        g[a].push_back(b);
        gt[b].push_back(a);
    }
    // add this type of condition->
    // add(a,af,b,bf) means if a is af then b must need to be bf
    void add(int a, bool af, int b, bool bf)
    {
        _add(a, af, b, bf);
        _add(b, !bf, a, !af);
    }
    void dfs1(int u)
    {
        vis[u] = true;
        for (int v : g[u])
            if (!vis[v])
                dfs1(v);
        ts.push(u);
    }
    void dfs2(int u, int c)
    {
        comp[u] = c;
        for (int v : gt[u])
            if (comp[v] == -1)
                dfs2(v, c);
    }
    bool ok()
    {
        vis.resize(n, false);
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(i);
        int scc = 0;
        comp.resize(n, -1);
        while (!ts.empty())
        {
            int u = ts.top();
            ts.pop();
            if (comp[u] == -1)
                dfs2(u, scc++);
        }
        res.resize(n / 2);
        for (int i = 0; i < n; i += 2)
        {
            if (comp[i] == comp[i + 1])
                return false;
            res[i / 2] = (comp[i] > comp[i + 1]);
        }
        return true;
    }
};
int main()
{
    fast;

    int n, m;
    cin >> n >> m;

    twosat ts(m);

    for (int i = 0; i < n; i++)
    {
        char c1, c2;
        ll x, y;
        cin >> c1 >> x >> c2 >> y;
        --x, --y;
        bool a = (c1 == '+');
        bool b = (c2 == '+');
        ts.addOR(x, a, y, b);
    }

    if (!ts.ok())
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < m; i++)
        cout << (ts.res[i] ? '+' : '-');
    cout << '\n';
}