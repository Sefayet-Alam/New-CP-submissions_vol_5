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
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;

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

/***
 *
 * 64-bit hashing for vectors or strings
 * Get the forward and reverse hash of any segment
 * Base is chosen randomly to prevent anti-hash cases from being constructed
 *
 * Complexity - O(n) to build, O(1) for each hash query
 *
 ***/

#define MAXLEN 1000010
constexpr uint64_t mod = (1ULL << 61) - 1;

const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (mod / 3) + (mod / 3);

uint64_t base_pow[MAXLEN];

int64_t modmul(uint64_t a, uint64_t b)
{
    uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}

void init()
{
    base_pow[0] = 1;
    for (int i = 1; i < MAXLEN; i++)
    {
        base_pow[i] = modmul(base_pow[i - 1], base);
    }
}

struct PolyHash
{
    /// Remove suff vector and usage if reverse hash is not required for more speed
    vector<int64_t> pref, suff;

    PolyHash() {}

    template <typename T>
    PolyHash(const vector<T> &ar)
    {
        if (!base_pow[0])
            init();

        int n = ar.size();
        assert(n < MAXLEN);
        pref.resize(n + 3, 0), suff.resize(n + 3, 0);

        for (int i = 1; i <= n; i++)
        {
            pref[i] = modmul(pref[i - 1], base) + ar[i - 1] + 997;
            if (pref[i] >= mod)
                pref[i] -= mod;
        }

        for (int i = n; i >= 1; i--)
        {
            suff[i] = modmul(suff[i + 1], base) + ar[i - 1] + 997;
            if (suff[i] >= mod)
                suff[i] -= mod;
        }
    }

    PolyHash(const char *str)
        : PolyHash(vector<char>(str, str + strlen(str))) {}
    PolyHash(string str)
        : PolyHash(vector<char>(all(str))) {}
    uint64_t get_hash(int l, int r)
    {
        int64_t h = pref[r + 1] - modmul(base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + mod : h;
    }

    uint64_t rev_hash(int l, int r)
    {
        int64_t h = suff[l + 1] - modmul(base_pow[r - l + 1], suff[r + 2]);
        return h < 0 ? h + mod : h;
    }
};
int main()
{
    fast;
    ll n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    if (n == 1)
    {
        cout << 1 << nn;
        return 0;
    }
    bool f = 0;
    map<char, ll> mpp;
    for (ll i = 0; i < m; i++)
    {
        mpp[t[i]]++;
    }
    set<ll> poses;
    for (ll i = 0; i < n; i++)
    {
        if (mpp[s[i]] == 0)
        {
            f = 1;
            poses.insert(i);
        }
    }
    ll ans = n;
    if (f)
    {
        if (poses.find(0) != poses.end() || poses.find(n - 1) != poses.end())
            ans = min(ans, 2LL);
        else if (poses.size())
            ans = min(ans, 3LL);
    }
    if (s[0] != t[0] || s.back() != t.back())
    {
        ans = min(ans, 2LL);
    }
    vector<ll> lastpos(30, -1), firstpos(30, M);
    for (ll i = 0; i < m; i++)
    {
        lastpos[t[i] - 'a'] = max(lastpos[t[i] - 'a'], i);
    }
    for (ll i = 0; i < m; i++)
    {
        firstpos[t[i] - 'a'] = min(firstpos[t[i] - 'a'], i);
    }
    //*a*b*
    for (ll i = 0; i < n; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            ll a = s[i] - 'a';
            ll b = s[j] - 'a';
            if (firstpos[a] == M || lastpos[b] == -1)
                continue;
            if (firstpos[a] > lastpos[b])
            {
                if (i == 0)
                {
                    if (j == n - 1)
                    {
                        if (j == i + 1)
                            ans = min(ans, 2LL);
                        else
                            ans = min(ans, 3LL);
                    }
                    else if (j == i + 1)
                        ans = min(ans, 3LL);
                    else
                        ans = min(ans, 4LL);
                }
                else
                {
                    if (j == n - 1)
                    {
                        if (j == i + 1)
                            ans = min(ans, 3LL);
                        else
                            ans = min(ans, 4LL);
                    }
                    else
                    {
                        if (j == i + 1)
                            ans = min(ans, 4LL);
                        else
                            ans = min(ans, 5LL);
                    }
                }
            }
        }
    }
    set<ll> hashes;
    for (ll i = 0; i < m; i++)
    {
        string now = "";
        for (ll j = i; j < m; j++)
        {
            now += t[j];
            string ex = "";
            for (ll k = j + 1; k < m; k++)
            {
                ex += t[k];
                string tmp = now + ex;
                PolyHash hs(tmp);
                hashes.insert(hs.get_hash(0, tmp.size() - 1));
            }
        }
    }
    for (ll i = 0; i < n; i++)
    {
        string now = "";
        for (ll j = i; j < n; j++)
        {
            now += s[j];
            string ex = "";
            for (ll k = j + 1; k < n; k++)
            {
                ex += s[k];
                string tmp = now + ex;
                PolyHash hs2(tmp);
                if (hashes.find(hs2.get_hash(0, tmp.size() - 1)) == hashes.end())
                {
                    ll cur = tmp.size() + 3;
                    if (i == 0)
                        cur--;
                    if (j == n - 1)
                        cur--;
                    if (k == j + 1)
                        cur--;
                    ans = min(ans, cur);
                    
                }
            }
        }
    }

    cout << ans << nn;
    return 0;
}
