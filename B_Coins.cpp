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
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;

using T = __int128;
T extended_euclid(T a, T b, T &x, T &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    T x1, y1;
    T d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
T inverse(T a, T m)
{
    T x, y;
    T g = extended_euclid(a, m, x, y);
    if (g != 1)
        return -1;
    return (x % m + m) % m;
}
T sumsq(T n)
{
    return n / 2 * ((n - 1) | 1);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) / m}, O(log m)
T floor_sum(T a, T d, T m, T n)
{
    T res = d / m * sumsq(n) + a / m * n;
    d %= m;
    a %= m;
    if (!d)
        return res;
    T to = (n * d + a) / m;
    return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
// number of solutions to ax + by + cz = n s.t. x, y, z >= 0
// a, b, c >= 1, a, b and c are pairwise coprime
// O(log(max(a, b, c)));
T count(T a, T b, T c, T n)
{
    assert(__gcd(a, b) == 1);
    assert(__gcd(b, c) == 1);
    assert(__gcd(a, c) == 1);
    T b1p = (-n % a * inverse(b, a) % a + a) % a;
    if (b1p == 0)
        b1p = a;
    T c1p = (b % a * inverse(c, a) % a + a) % a;
    if (c1p == 0)
        c1p = a;
    T c2p = (-n % b * inverse(c, b) % b + b) % b;
    if (c2p == 0)
        c2p = b;
    T a2p = (c % b * inverse(a, b) % b + b) % b;
    if (a2p == 0)
        a2p = b;
    T a3p = (-n % c * inverse(a, c) % c + c) % c;
    if (a3p == 0)
        a3p = c;
    T b3p = (a % c * inverse(b, c) % c + c) % c;
    if (b3p == 0)
        b3p = c;
    T N1 = n * (n + a + b + c);
    N1 += c * b * b1p * (a + 1 - c1p * (b1p - 1));
    N1 += a * c * c2p * (b + 1 - a2p * (c2p - 1));
    N1 += b * a * a3p * (c + 1 - b3p * (a3p - 1));
    T ans = N1 / (2 * a * b * c);
    ans += floor_sum(0, c1p, a, b1p);
    ans += floor_sum(0, a2p, b, c2p);
    ans += floor_sum(0, b3p, c, a3p);
    ans -= 2;
    return ans;
}
// number of solutions to ax + by + cz = n s.t. x, y, z >= 0
// a, b, c >= 1
// O(log(max(a, b, c)));
// paper: https://cs.uwaterloo.ca/journals/JIS/VOL23/Binner/binner4.pdf
T yo(T a, T b, T c, T n)
{
    T g = __gcd(__gcd(a, b), c);
    if (n % g != 0)
        return 0;
    a /= g;
    b /= g;
    c /= g;
    n /= g;
    T g1 = __gcd(b, c), g2 = __gcd(c, a), g3 = __gcd(a, b);
    T a1 = inverse(a, g1), b2 = inverse(b, g2), c3 = inverse(c, g3);
    T n1 = n * a1 % g1, n2 = n * b2 % g2, n3 = n * c3 % g3;
    T A = a / g2 / g3, B = b / g3 / g1, C = c / g1 / g2;
    T N = (n - a * n1 - b * n2 - c * n3) / g1 / g2 / g3;
    return count(A, B, C, N);
}
T brute(T a, T b, T c, T n)
{
    T ans = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= n; k++)
            {
                if (i * a + j * b + k * c == n)
                    ++ans;
            }
        }
    }
    return ans;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int a = 1; a <= 5; a++)
    {
        for (int b = 1; b <= 5; b++)
        {
            for (int c = 1; c <= 5; c++)
            {
                for (int n = 1; n <= 50; n++)
                {
                    T x = yo(a, b, c, n), y = brute(a, b, c, n);
                    assert(x == y);
                }
            }
        }
    }
    return 0;
}
