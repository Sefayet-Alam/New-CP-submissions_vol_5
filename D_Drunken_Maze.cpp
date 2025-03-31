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
const ll N = 1e3 + 10;
const ll M = 1e9 + 7;
ll enx, eny;

ll n, m;
vector<vector<char>> g;

vpll Move = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool isValid(ll x, ll y)
{
    return (x >= 0 && y >= 0 && x < n && y < m && g[x][y] != '#');
}

int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    cin >> n >> m;

    ll dist[n + 3][m + 3][5][5];
    g.resize(n, vector<char>(m));
    for (ll i = 0; i <= n + 1; i++)
    {
        for (ll j = 0; j <= m + 1; j++)
        {
            for (ll p = 0; p < 4; p++)
            {
                for (ll o = 0; o < 4; o++)
                {
                    dist[i][j][p][o] = M;
                }
            }
        }
    }

    ll stx, sty;
    for (ll i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (ll j = 0; j < m; j++)
        {
            g[i][j] = s[j];
            if (s[j] == 'T')
            {
                enx = i;
                eny = j;
            }
            else if (s[j] == 'S')
            {
                stx = i;
                sty = j;
            }
        }
    }

    ll srcx = stx, srcy = sty;

    QP<pair<pll, array<ll, 3>>> pq;
    pq.push({{0, 0}, {srcx, srcy, 4}});
    dist[srcx][srcy][0][0] = 0;
    dist[srcx][srcy][0][1] = 0;
    dist[srcx][srcy][0][2] = 0;
    dist[srcx][srcy][0][3] = 0;
    while (pq.size())
    {
        auto ar = pq.top().second;
        auto pr = pq.top().first;

        ll vx = ar[0];
        ll vy = ar[1];
        ll dir = ar[2];

        ll v_dist = pr.first;
        ll stp = pr.second;
        pq.pop();
        if (dist[vx][vy][stp][dir] < v_dist)
            continue;
        for (ll i = 0; i < 4; i++)
        {
            ll child_vx = vx + Move[i].first;
            ll child_vy = vy + Move[i].second;
            if (!isValid(child_vx, child_vy))
                continue;
            if (i == dir)
            {
                if (stp == 3 && dist[vx][vy][stp][dir] + 3 < dist[child_vx][child_vy][2][i])
                {
                    dist[child_vx][child_vy][2][i] = dist[vx][vy][stp][dir] + 3;
                    pq.push({{dist[child_vx][child_vy][2][i], 2}, {child_vx, child_vy, i}});
                }
                else if (stp < 3 && dist[vx][vy][stp][dir] + 1 < dist[child_vx][child_vy][stp + 1][i])
                {
                    dist[child_vx][child_vy][stp + 1][i] = dist[vx][vy][stp][i] + 1;
                    pq.push({{dist[child_vx][child_vy][stp + 1][i], stp + 1}, {child_vx, child_vy, i}});
                }
            }
            else
            {
                if (dist[vx][vy][stp][dir] + 1 < dist[child_vx][child_vy][1][i])
                {
                    dist[child_vx][child_vy][1][i] = dist[vx][vy][stp][dir] + 1;
                    pq.push({{dist[child_vx][child_vy][1][i], 1}, {child_vx, child_vy, i}});
                }
            }
        }
    }
    ll ans = M;
    for (ll i = 0; i < 4; i++)
    {
        for (ll j = 0; j < 4; j++)
        {
            ans = min(ans, dist[enx][eny][i][j]);
        }
    }
    // deb(ans);
    if (ans >= M / 2)
        cout << -1 << nn;
    else
        cout << ans << nn;

    return 0;
}