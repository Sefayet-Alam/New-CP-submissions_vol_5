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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;

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

#define ll long long
#define endl '\n'
inline int sq(int a) { return a * a; }
struct pt
{
    int x, y, id, ty;
    pt() {}
    pt(int _x, int _y, int _id, int _ty) { x = _x, y = _y, id = _id, ty = _ty; }
    bool operator<(pt a) const
    {
        if (x == a.x)
            return y < a.y;
        return x < a.x;
    }
};
inline int dist2(pt &a, pt &b)
{
    return (sq(a.x - b.x) + sq(a.y - b.y));
}
vector<pt> t;
pair<int, pair<pt, pt>> mergesort(int l, int r, vector<pt> &a)
{
    if (r - l <= 2)
    {
        pair<int, pair<pt, pt>> mi(1000000000, {pt(0, 0, 0, 0), pt(0, 0, 0, 0)});
        for (int i = l; i <= r; i++)
        {
            for (int j = i + 1; j <= r; j++)
            {
                if (a[i].id != a[j].id)
                {
                    mi = min(mi, make_pair(dist2(a[i], a[j]), make_pair(a[i], a[j])));
                }
            }
        }
        sort(a.begin() + l, a.begin() + r + 1, [](pt a, pt b)
             {
			if (a.y == b.y)return a.x < b.x;
			return a.y < b.y; });
        return mi;
    }
    int mid = l + r >> 1;
    int midx = a[mid].x;
    pair<int, pair<pt, pt>> mi = min(mergesort(l, mid - 1, a), mergesort(mid, r, a));
    merge(a.begin() + l, a.begin() + mid, a.begin() + mid, a.begin() + r + 1, t.begin(), [](pt a, pt b)
          {
		if (a.y == b.y)return a.x < b.x;
		return a.y < b.y; });
    copy(t.begin(), t.begin() + r - l + 1, a.begin() + l);
    int tsz = 0;
    for (int i = l; i <= r; ++i)
    {
        if (sq(a[i].x - midx) < mi.first)
        {
            for (int j = tsz - 1; j >= 0 && sq(a[i].y - t[j].y) < mi.first; --j)
            {
                if (a[i].id != t[j].id)
                {
                    mi = min(mi, make_pair(dist2(a[i], t[j]), make_pair(a[i], t[j])));
                }
            }
            t[tsz++] = a[i];
        }
    }
    return mi;
}

int32_t main()
{

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    t.resize(n * 4);
    vector<pt> v;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        v.push_back(pt(x, y, i, 1));
        v.push_back(pt(-x, y, i, 2));
        v.push_back(pt(x, -y, i, 3));
        v.push_back(pt(-x, -y, i, 4));
    }
    sort(v.begin(), v.end());
    auto ans = mergesort(0, 4 * n - 1, v);
    cout << ans.second.first.id << ' ' << ans.second.first.ty << ' ' << ans.second.second.id << ' ' << 5 - ans.second.second.ty << '\n';

    return 0;
}