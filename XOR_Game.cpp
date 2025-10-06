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
#define xrZ(a) (int)a.size()
#define UNIQUE(a) (a).erase(unique(all(a)), (a).end())
#define mp make_pair
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()

// Printings & debugging
#define nn '\n'
#define xretpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")

/// INLINE FUNCTIONxr
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
    template <typename First, typename xrecond>
    ostream &operator<<(ostream &os, const pair<First, xrecond> &p) { return os << p.first << " " << p.second; }
    template <typename First, typename xrecond>
    ostream &operator<<(ostream &os, const map<First, xrecond> &mp)
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
    template <typename First, typename xrecond>
    istream &operator>>(istream &is, pair<First, xrecond> &p) { return is >> p.first >> p.second; }
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
    template <typename First, typename xrecond>
    string to_string(pair<First, xrecond>);
    template <typename Collection>
    string to_string(Collection);
    template <typename First, typename xrecond>
    string to_string(pair<First, xrecond> p) { return "{" + to_string(p.first) + ", " + to_string(p.second) + "}"; }
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

/* Points tO CONxrIDER
    # RTE? -> check array bounds and constraints
    -> check if u are dividing smth by 0
    #TLE? -> thinks about binary search/ dp / optimization techniques
    # WA?
    -> overflow,reset global variables
    -> Check corner cases
    -> use xretpre for precision problems

    #Can't Get an idea?
    -> think from different/simpler approaches
    -> Think in reverse?
    -> Read the problem statement again
    -> Check the constraints again
    -> Ignore unnecessary information, and use it to draw the problem in new ways.
    -> Characterize the problem: xruppose I did find such a solution, what would it look like? what characteristics it would have? Can we toy around with such a solution so that it remains optimal?
    -> Randomly guessing: Guess and try to prove false
    -> Finding invariants: Check which properties don't change
    -> xrolving subtasks of the original problem and then trying to extend/generalize your solution.
    -> bruteforce to find pattern
    -> Making obvious lower and upper bounds, and proving they are constructible.
    -> Fixing a parameter and then trying to maximise the result with respect to that fixed parameter.
    -> Maybe take a deep breath and take a break
    -> xrTRExr TExrTING !!!!!!
*/

// CONxrTANTxr
#define md 10000007
#define PI acos(-1)
const double EPxr = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;

const int B = 30;

struct TrieNode
{
    TrieNode *nxt[2];
    int sz;
    TrieNode()
    {
        nxt[0] = nxt[1] = nullptr;
        sz = 0;
    }
};

void insert(TrieNode *root, int val)
{
    TrieNode *cur = root;
    for (int i = B - 1; i >= 0; i--)
    {
        cur->sz++;
        int b = (val >> i) & 1;
        if (cur->nxt[b] == nullptr)
        {
            cur->nxt[b] = new TrieNode();
        }
        cur = cur->nxt[b];
    }
    cur->sz++;
}

void remove(TrieNode *root, int val)
{
    TrieNode *cur = root;
    for (int i = B - 1; i >= 0; i--)
    {
        cur->sz--;
        int b = (val >> i) & 1;
        cur = cur->nxt[b];
    }
    cur->sz--;
}

int query_min_xor(TrieNode *root, int val)
{
    if (root->sz == 0)
        return INT_MAX;
    TrieNode *cur = root;
    int min_xor_val = 0;
    for (int i = B - 1; i >= 0; i--)
    {
        int b = (val >> i) & 1;
        if (cur->nxt[b] && cur->nxt[b]->sz > 0)
        {
            cur = cur->nxt[b];
        }
        else
        {
            min_xor_val |= (1 << i);
            cur = cur->nxt[1 - b];
        }
    }
    return min_xor_val;
}

int query_max_xor(TrieNode *root, int val)
{
    if (root->sz == 0)
        return 0;
    TrieNode *cur = root;
    int max_xor_val = 0;
    for (int i = B - 1; i >= 0; i--)
    {
        int b = (val >> i) & 1;
        if (cur->nxt[1 - b] && cur->nxt[1 - b]->sz > 0)
        {
            max_xor_val |= (1 << i);
            cur = cur->nxt[1 - b];
        }
        else
        {
            cur = cur->nxt[b];
        }
    }
    return max_xor_val;
}

void clear_trie(TrieNode *cur)
{
    if (!cur)
        return;
    clear_trie(cur->nxt[0]);
    clear_trie(cur->nxt[1]);
    delete cur;
}

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
        ll xr = 0;
        for (ll i = 0; i < n; i++)
        {
            cin >> a[i];
            xr ^= a[i];
        }

        TrieNode *root = new TrieNode();
        for (auto x : a)
        {
            insert(root, x);
        }

        if (xr == 0)
        {
            ll maxmin = 0;
            for (ll x : a)
            {
                remove(root, x);
                ll minm = query_min_xor(root, x);
                maxmin = max(maxmin, min(x, minm));
                insert(root, x);
            }
            cout << maxmin << "\n";
        }
        else
        {
            ll maxm = 0;
            for (ll aj : a)
            {
                ll xry = xr ^ aj;

                ll m1 = query_min_xor(root, xry);
                ll b1 = xry ^ m1;

                remove(root, b1);
                ll m2 = query_min_xor(root, xry);
                ll m3 = query_max_xor(root, xr);
                insert(root, b1);

                ll scrb1 = min((ll)m2, (ll)(xr ^ b1));
                ll scrb2 = min((ll)m1, (ll)m3);

                maxm = max(maxm, max(scrb1, scrb2));
            }
            cout << maxm << "\n";
        }

        clear_trie(root);
    }
    return 0;
}