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



const int MAX_N = 10005;


/*

Removing edges to form a bipartite graph

blog: https://codeforces.com/blog/entry/68138
problem: 03
*/
struct Edge
{
    int other, id;

    Edge() {}

    Edge(int t_other, int t_id) : other(t_other), id(t_id) {}
};

pair<int, int> edges[MAX_N];
vector<Edge> adj[MAX_N];

void initPaint(int vertex, vector<int> &color, int curColor, bool &ok)
{
    color[vertex] = curColor;

    for (Edge nxt : adj[vertex])
    {
        if (color[nxt.other] == color[vertex])
        {
            ok = false;
        }
        else if (color[nxt.other] == 0)
        {
            initPaint(nxt.other, color, -curColor, ok);
        }
    }
}

vector<Edge> children[MAX_N];
Edge parent[MAX_N];
bool isSpan[MAX_N];
bool inTree[MAX_N];

void buildDfs(int vertex, vector<int> &vis)
{
    vis[vertex] = true;
    inTree[vertex] = true;
    for (Edge nxt : adj[vertex])
    {
        if (!vis[nxt.other])
        {
            isSpan[nxt.id] = 1;
            children[vertex].push_back(nxt);
            parent[nxt.other] = nxt;
            buildDfs(nxt.other, vis);
        }
    }
}

int treeColor[MAX_N];
int lvl[MAX_N];
void paintTree(int vertex, int curColor, int curLvl)
{
    treeColor[vertex] = curColor;
    lvl[vertex] = curLvl;
    for (Edge nxt : children[vertex])
    {
        paintTree(nxt.other, -curColor, curLvl + 1);
    }
}

vector<int> ans;
int contraCnt;

int contras[MAX_N];
int satis[MAX_N];
pair<int, int> accumulate(int vertex, int root)
{
    int curContras = contras[vertex];
    int curSatis = satis[vertex];
    for (Edge nxt : children[vertex])
    {
        pair<int, int> pr = accumulate(nxt.other, root);
        curContras += pr.first;
        curSatis += pr.second;
    }
    if (curContras == contraCnt && curSatis == 0 && vertex != root)
    {
        ans.push_back(parent[vertex].id);
    }
    return make_pair(curContras, curSatis);
}

int main()
{
    ios::sync_with_stdio(false);

    int vertexc, edgec;
    cin >> vertexc >> edgec;

    for (int i = 1; i <= edgec; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(Edge(v, i));
        adj[v].push_back(Edge(u, i));
        edges[i].first = u;
        edges[i].second = v;
    }

    vector<int> initColors(vertexc + 1, 0);
    vector<int> badRoots;
    for (int i = 1; i <= vertexc; i++)
    {
        if (initColors[i] == 0)
        {
            bool ok = true;
            initPaint(i, initColors, 1, ok);
            if (!ok)
            {
                badRoots.push_back(i);
            }
        }
    }

    if ((int)badRoots.size() == 0)
    {
        cout << edgec << '\n';
        for (int i = 1; i <= edgec; i++)
        {
            cout << i << " ";
        }
        cout << '\n';
        return 0;
    }

    if ((int)badRoots.size() >= 2)
    {
        cout << 0 << '\n';
        return 0;
    }

    int root = badRoots[0];
    vector<int> vis(vertexc + 1, 0);
    buildDfs(root, vis);
    paintTree(root, 1, 0);

    contraCnt = 0;
    for (int i = 1; i <= edgec; i++)
    {
        if (!isSpan[i] && inTree[edges[i].first])
        {
            if (treeColor[edges[i].first] == treeColor[edges[i].second])
            {
                contraCnt++;
            }
        }
    }

    for (int i = 1; i <= edgec; i++)
    {
        if (!isSpan[i] && inTree[edges[i].first])
        {
            if (treeColor[edges[i].first] == treeColor[edges[i].second])
            {
                if (contraCnt == 1)
                {
                    ans.push_back(i);
                }
            }

            if (lvl[edges[i].first] > lvl[edges[i].second])
            {
                swap(edges[i].first, edges[i].second);
            }

            if (treeColor[edges[i].first] == treeColor[edges[i].second])
            {
                contras[edges[i].second]++;
                contras[edges[i].first]--;
            }
            else
            {
                satis[edges[i].second]++;
                satis[edges[i].first]--;
            }
        }
    }

    accumulate(root, root);

    sort(ans.begin(), ans.end());

    cout << (int)ans.size() << '\n';
    for (int u : ans)
    {
        cout << u << " ";
    }
    cout << '\n';
}
