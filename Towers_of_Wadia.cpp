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

const ll N = 2e5 + 10;
const ll M = 1e9 + 7;
const double eps = 1e-9;

int sign(double x) { return (x > eps) - (x < -eps); }

struct PT
{
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator+(const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator-(const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator*(const double a) const { return PT(x * a, y * a); }
    friend PT operator*(const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator/(const double a) const { return PT(x / a, y / a); }
    bool operator==(PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator!=(PT a) const { return !(*this == a); }
    bool operator<(PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator>(PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }
    PT perp() { return PT(-y, x); }
    double arg() { return atan2(y, x); }
    PT truncate(double r)
    { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k))
            return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};

inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }

double area(vector<PT> &p)
{
    double ans = 0;
    int n = p.size();
    for (int i = 0; i < n; i++)
        ans += cross(p[i], p[(i + 1) % n]);
    return fabs(ans) * 0.5;
}
double area_of_triangle(PT a, PT b, PT c)
{
    return fabs(cross(b - a, c - a) * 0.5);
}
vector<PT> convex_hull(vector<PT> &p)
{
    if (p.size() <= 1)
        return p;
    vector<PT> v = p;
    sort(v.begin(), v.end());
    vector<PT> up, dn;
    for (auto &p : v)
    {
        while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0)
        {
            up.pop_back();
        }
        while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) <= 0)
        {
            dn.pop_back();
        }
        up.push_back(p);
        dn.push_back(p);
    }
    v = dn;
    if (v.size() > 1)
        v.pop_back();
    reverse(up.begin(), up.end());
    up.pop_back();
    for (auto &p : up)
    {
        v.push_back(p);
    }
    if (v.size() == 2 && v[0] == v[1])
        v.pop_back();
    return v;
}

bool half(PT p) {
    return p.y > 0.0 || (p.y == 0.0 && p.x < 0.0);
}
void polar_sort(vector<PT> &v) { // sort points in counterclockwise
    sort(v.begin(), v.end(), [](PT a,PT b) {
        return make_tuple(half(a), 0.0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2());
    });
}

ll n, k;
ll sz;
const double neginf = -(1e16 + 7) * 1.00;
const double EPS = 1e-6;


vector<PT> towers(N);
map<tuple<ll, ll, ll, ll, bool>, pair<double, ll>> dp;
bool isok[102][102];
PT head;

pair<double, ll> func(ll i, ll sti, ll prev, ll tek, bool st)
{
    if (i == sz)
    {
        if (st == 0)
            return {neginf, 0};
        else if (tek == k)
        {
            // deb2(prev, sti);
            // deb(isok[prev][sti]);
            if (isok[prev][sti])
            {
                // deb2(prev, sti);
                double last = area_of_triangle(towers[prev], head, towers[sti]);
                // deb(last);
                return {last, 1};
            }
            else
                return {neginf, 0};
        }
        else
            return {neginf, 0};
    }
    if (dp.find({i, sti, prev, tek, st}) != dp.end())
        return dp[{i, sti, prev, tek, st}];
    pair<double, ll> ret = {0.00, 0};
    if (st == 0) //not started taking points to create convex hull
    {
        if (tek + 1 <= k) //skip this point
        {
            auto now = func(i + 1, sti, prev, tek + 1, 0);
            if (now.first > EPS) //found an answer
            {
                ret.first += max(0.000, now.first);
                ret.second += now.second;
            }
        }
        auto now = func(i + 1, i, i, tek, 1); //take this point as first point
        if (now.first > EPS) 
        {
            ret.first += max(0.000, now.first);
            ret.second += now.second;
        }
    }
    else
    {
        if (isok[prev][i] == 0)
            return dp[{i, sti, prev, tek, st}] = {neginf, 0};

        double ar = area_of_triangle(towers[prev], head, towers[i]);
        auto now = func(i + 1, sti, i, tek, 1);
        if (now.first > EPS)
        {
            ret.first += max(0.000, ar + now.first);
            ret.second += now.second;
        }

        if (tek + 1 <= k)
        {
            auto now = func(i + 1, sti, prev, tek + 1, 1);
            if (now.first > EPS)
            {
                ret.first += max(0.000, now.first);
                ret.second += now.second;
            }
        }
    }
    return dp[{i, sti, prev, tek, st}] = ret;
}

int main()
{
    fast;
    cin >> n;
    cin >> head.x >> head.y;
    towers.resize(n - 1);
    for (ll i = 0; i < n - 1; i++)
    {
        cin >> towers[i].x >> towers[i].y;
    }

    cin >> k;
    if(k>=n-3){
        double ret = 0.0000000;
        Setpre(10) << ret << nn;
        return 0;
    }
    polar_sort(towers);
    towers=convex_hull(towers);
    // towers = convex_hull(towers);
    // for (auto it : towers)
    // {
    //     deb2(it.x, it.y);
    // }
    sz = towers.size();
    mem(isok, false);
    for (ll i = 0; i < sz; i++)
    {
        isok[i][(i + 1) % sz] = 1; // consecutive two points are always selectable
        auto ori = orientation(towers[i], head, towers[i + 1]);
        for (ll j = 1; j < sz; j++)
        {
            // we'll skip j-1 points...isok[i][nxt]=can we jump from i to nxt
            // without making head point an edge?

            ll nxt = (i + j) % sz;
            auto now = orientation(towers[i], head, towers[nxt]);
            // deb2(i,nxt);
            if (now == ori)
            {
                isok[i][nxt] = 1;
            }
            else
            {
                isok[i][nxt] = 0;
            }
            // deb(isok[i][nxt]);
        }
    }

    auto ans = func(0, 0, 0, 0, 0);
    // deb(ans);
    if (ans.second != 0)
    {
        double ret = ans.first / (1.00 * ans.second);
        Setpre(10) << ret << nn;
    }
    else
    {
        double ret = 0.0000000;
        Setpre(10) << ret << nn;
    }

    return 0;
}


