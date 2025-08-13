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

/// calc calculates maximum subsegment sum from l to r
struct item
{
    ll seg, pref, suff, sum;
};
struct segment_tree
{
    ll size;
    vector<item> tree;
    void init(ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        tree.resize(2 * size);
    }

    item neutral_ele = {0LL, 0LL, 0LL, 0LL};
    item merge(item a, item b)
    {
        return {max({a.seg, b.seg, a.suff + b.pref}), max(a.pref, a.sum + b.pref), max(b.suff, b.sum + a.suff), (a.sum + b.sum)};
    }

    item single(ll val)
    {
        if (val > 0)
        {
            return {val, val, val, val};
        }
        return {0LL, 0LL, 0LL, val};
    }
    void build(vector<ll> &a, ll x, ll lx, ll rx)
    {
        // linear time
        if (rx - lx == 1)
        {
            if (lx < a.size())
            {
                tree[x] = single(a[lx]);
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<ll> &a)
    {
        // linear time
        build(a, 0LL, 0LL, size);
    }
    void set(ll i, ll val, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            // leaf
            tree[x] = single(val);
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, val, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, val, 2 * x + 2, m, rx);
        }
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(ll i, ll val)
    {
        // assigns val at index i
        set(i, val, 0LL, 0LL, size);
    }
    item calc(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (lx >= r || l >= rx)
        {
            return neutral_ele;
        }
        if (lx >= l && rx <= r)
        {
            return tree[x];
        }
        ll m = (lx + rx) / 2;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }
    item calc(ll l, ll r)
    {
        // returns sum from l to r
        return calc(l, r, 0LL, 0LL, size);
    }
};
int main()
{
    fast;
    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<ll> a(n);
        vector<vector<ll>> block(n);
        for (ll i = 0; i < n; ++i)
        {
            cin >> a[i];
            --a[i]; // make 0-based
            block[a[i]].push_back(i);
        }
        segment_tree seg;
        seg.init(n);
        for (ll i = 0; i < n; i++)
        {
            seg.set(i, 1); // initially every position has value 1
        }
        auto check = [&](ll pos)
        {
            item pre = (pos == 0) ? seg.neutral_ele : seg.calc(0, pos);
            item suf = (pos + 1 == n) ? seg.neutral_ele : seg.calc(pos + 1, n);
            return pre.suff + suf.pref >= 1;
        }; //
        ll ans = 0;
        ll j = 0; // median
        for (ll i = 0; i < n; ++i)
        {
            for (ll pos : block[i])
            {
                while (j <= i || check(pos))
                {
                    for (ll p : block[j])
                    {
                        seg.set(p, -1); // make value -1
                        // for all j<=i we set values of those positions that have j in the
                        // main array to -1...This creates barriers and segments the array
                        // now check(pos) for a pos only checks j+1 to infinity if there's a segment
                        // where median can be j
                        // this is implemented by segment tree
                        // check checks for a position pos, if there's a segment before it (0 to pos-1) and after it(pos+1 to n-1)
                        // such that total segment length>=1
                    }
                    ++j;
                    // deb2(i,j);
                }
            }
            ans = max(ans, (j - 1) - i); // maximum median = j-1
            for (ll pos : block[i])
            {
                seg.set(pos, -(1LL << 30)); // simulate removal with large -ve
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
