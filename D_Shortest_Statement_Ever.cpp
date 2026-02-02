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

const ll INF = 4e18;

ll dp[35][3][3];
ll psx[35][3][3], psy[35][3][3];
ll chp[35][3][3], chq[35][3][3];

int main()
{
    fast;
    ll t;
    cin >> t;
    while (t--)
    {
        ll x, y;
        cin >> x >> y;

        for (ll i = 0; i < 35; i++)
        {
            for (ll j = 0; j < 3; j++)
            {
                for (ll k = 0; k < 3; k++)
                {
                    dp[i][j][k] = INF;
                }
            }
        }

        dp[31][1][1] = 0;

        for (ll b = 30; b >= 0; b--)
        {
            ll xb = (x >> b) & 1;
            ll yb = (y >> b) & 1;
            for (ll sx = 0; sx < 3; sx++)
            {
                for (ll sy = 0; sy < 3; sy++)
                {
                    if (dp[b + 1][sx][sy] == INF)
                        continue;
                    for (ll pb = 0; pb <= 1; pb++)
                    {
                        for (ll qb = 0; qb <= 1; qb++)
                        {
                            if (pb && qb)
                                continue;
                            ll nsx = sx, nsy = sy;
                            ll cost = 0;
                            if (sx == 1)
                            {
                                if (pb < xb)
                                    nsx = 0;
                                else if (pb > xb)
                                    nsx = 2;
                            }
                            if (nsx == 0)
                                cost += 1LL * ((xb - pb) << b);
                            else if (nsx == 2)
                                cost += 1LL * ((pb - xb) << b);
                            if (sy == 1)
                            {
                                if (qb < yb)
                                    nsy = 0;
                                else if (qb > yb)
                                    nsy = 2;
                            }
                            if (nsy == 0)
                                cost += 1LL * ((yb - qb) << b);
                            else if (nsy == 2)
                                cost += 1LL * ((qb - yb) << b);

                            if (dp[b + 1][sx][sy] + cost < dp[b][nsx][nsy])
                            {
                                dp[b][nsx][nsy] = dp[b + 1][sx][sy] + cost;
                                psx[b][nsx][nsy] = sx;
                                psy[b][nsx][nsy] = sy;
                                chp[b][nsx][nsy] = pb;
                                chq[b][nsx][nsy] = qb;
                            }
                        }
                    }
                }
            }
        }

        ll resdist = INF;
        ll cursx = 1, cursy = 1;
        for (ll i = 0; i < 3; i++)
        {
            for (ll j = 0; j < 3; j++)
            {
                if (dp[0][i][j] < resdist)
                {
                    resdist = dp[0][i][j];
                    cursx = i;
                    cursy = j;
                }
            }
        }

        ll p = 0, q = 0;
        for (ll b = 0; b <= 30; b++)
        {
            ll pb = chp[b][cursx][cursy];
            ll qb = chq[b][cursx][cursy];
            if (pb)
                p |= (1LL << b);
            if (qb)
                q |= (1LL << b);

            ll nxtsx = psx[b][cursx][cursy];
            ll nxtsy = psy[b][cursx][cursy];
            cursx = nxtsx;
            cursy = nxtsy;
        }
        cout << p << " " << q << nn;
    }
    return 0;
}