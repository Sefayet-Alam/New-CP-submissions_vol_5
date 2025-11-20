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
const ll M = 998244353;
string s, l, r;
ll k, sz;

struct hash_tuple
{
    template <class T1, class T2, class T3, class T4>
    size_t operator()(const tuple<T1, T2, T3, T4> &x) const
    {
        auto [a, b, c, d] = x;
        return ((a * 131 + b) * 131 + c) * 131 + d;
    }
};

unordered_map<tuple<ll, ll, ll, ll>, ll, hash_tuple> dp;

ll func(ll i, ll sum, ll msk, ll f)
{
    if (i == sz)
        return 1;

    ll remaining = sz - i;
    if (__builtin_popcountll(msk) + remaining > k)
        return 0;

    auto key = make_tuple(i, sum, msk, f);
    if (dp.count(key))
        return dp[key];

    ll limit = f ? (s[i] - '0') : 9;
    ll ret = 0;

    ll start = (i == 0) ? 1 : 0;
    for (ll dig = start; dig <= limit; dig++)
    {
        ll cursm = (sum + dig) % k;
        if (msk & (1LL << cursm))
            continue;
        ll nmask = msk | (1LL << cursm);
        ll newf = f && (dig == limit);
        ret = (ret + func(i + 1, cursm, nmask, newf)) % M;
    }
    return dp[key] = ret;
}

string subon(string num)
{
    ll i = num.length() - 1;
    while (i >= 0 && num[i] == '0')
        num[i--] = '9';
    if (i >= 0)
        num[i]--;
    if (num[0] == '0' && num.length() > 1)
        num = num.substr(1);
    return num;
}

ll calcc(string num)
{
    ll res = 0;
    for (char c : num)
        res = (res * 10 + (c - '0')) % M;
    return res;
}

ll calcallens(string p)
{
    ll len = p.length();
    if (len >= k)
    {
        ll totgd = 0;
        for (ll n = 1; n < k; n++)
        {
            s = string(n, '9');
            sz = n;
            dp.clear();
            totgd = (totgd + func(0, 0, 1, 1)) % M;
        }
        return totgd;
    }
    else
    {
        ll totgd = 0;
        for (ll n = 1; n < len; n++)
        {
            s = string(n, '9');
            sz = n;
            dp.clear();
            totgd = (totgd + func(0, 0, 1, 1)) % M;
        }
        s = p;
        sz = len;
        dp.clear();
        totgd = (totgd + func(0, 0, 1, 1)) % M;
        return totgd;
    }
}


void setIO()
{
#ifndef ONLINE_JUDGE
    freopen("dividing_passcodes_validation_input.txt", "r", stdin);

    freopen("dividing_passcodes_validation_output.txt", "w", stdout);
#endif // ONLINE_JUDGE
}


int main()
{
    fast;
    setIO();


    ll t, tno = 1;
    cin >> t;

    while (t--)
    {
        cout << "Case #" << tno++ << ": ";
        cin >> l >> r >> k;
        if (k == 1)
        {
            cout << 0 << "\n";
            continue;
        }
        string lm1 = subon(l);

        ll totr = calcc(r);
        ll totlm1 = calcc(lm1);

        ll goodr = calcallens(r);
        ll goodlm1 = calcallens(lm1);

        ll wkr = (totr - goodr + M) % M;
        ll wkl = (totlm1 - goodlm1 + M) % M;

        ll ans = (wkr - wkl + M) % M;
        cout << ans << "\n";
    }

    return 0;
}