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

ll minans;

/// BIT MANIPULATION

#define Set(x, k) (x |= (1LL << k))
#define Unset(x, k) (x &= ~(1LL << k))
#define Check(x, k) (x & (1LL << k))
#define Toggle(x, k) (x ^ (1LL << k))

int popcount(ll x) { return __builtin_popcountll(x); };
int poplow(ll x) { return __builtin_ctzll(x); };
int pophigh(ll x) { return 63 - __builtin_clzll(x); };

struct Trie
{

    const ll B = 63; // Max bit position
    struct node
    {
        node *nxt[2];
        ll sz;
        node()
        {
            nxt[0] = nxt[1] = nullptr;
            sz = 0;
        }
    } *root;

    Trie()
    {
        root = new node();
    }

    // Inserts a value into the binary trie.
    // Usage: tr.insert(x);
    void insert(ll val)
    {
        node *cur = root;
        cur->sz++;
        for (ll i = B - 1; i >= 0; i--)
        {
            ll b = (val >> i) & 1;
            if (cur->nxt[b] == nullptr)
            {
                cur->nxt[b] = new node();
            }
            cur = cur->nxt[b];
            cur->sz++;
        }
    }

    // Removes a value from the trie (assumes it exists).
    // Usage: tr.remove(x);
    void remove(int val)
    {
        node *cur = root;
        vector<node *> path;
        path.push_back(cur);
        for (ll i = B - 1; i >= 0; i--)
        {
            ll b = (val >> i) & 1;
            cur = cur->nxt[b];
            path.push_back(cur);
        }
        for (auto *n : path)
        {
            n->sz--;
        }
    }

    // Returns maximum possible (value XOR x) from the trie.
    // Usage: ll best = tr.get_max(x);
    ll get_max(ll x)
    {
        node *cur = root;
        ll ans = 0;
        for (ll i = B - 1; i >= 0; i--)
        {
            if (cur == nullptr)
                break;
            ll b = (x >> i) & 1;
            if (cur->nxt[1 - b] != nullptr && cur->nxt[1 - b]->sz > 0)
            {
                ans |= (1 << i);
                cur = cur->nxt[1 - b];
            }
            else
            {
                cur = cur->nxt[b];
            }
        }
        return ans;
    }

    // Clears the allocated trie nodes recursively.
    // Usage: (called automatically in destructor)
    void clear(node *cur)
    {
        if (cur == nullptr)
            return;
        clear(cur->nxt[0]);
        clear(cur->nxt[1]);
        delete cur;
    }

    // Destructor to free memory.
    // Usage: (automatic)
    ~Trie()
    {
        clear(root);
    }

    // Counts how many values v satisfy (v XOR val) < k.
    // Usage: ll c = tr.count(val, k);
    ll count(ll val, ll k)
    {
        node *cur = root;
        ll res = 0;
        for (ll i = B - 1; i >= 0; --i)
        {
            if (cur == nullptr)
                break;
            ll val_bit = (val >> i) & 1;
            ll k_bit = (k >> i) & 1;
            if (k_bit)
            {
                if (cur->nxt[val_bit] != nullptr)
                    res += cur->nxt[val_bit]->sz;
                cur = cur->nxt[1 - val_bit];
            }
            else
            {
                cur = cur->nxt[val_bit];
            }
        }
        if (cur != nullptr && cur->sz > 0)
        {
            res += cur->sz;
        }
        return res;
    }

    // Returns minimum possible (value XOR x).
    // Usage: ll mn = tr.get_min(x);
    ll get_min(ll x)
    {
        node *cur = root;
        ll ans = 0;
        for (ll i = B - 1; i >= 0; i--)
        {
            if (cur == nullptr)
                break;
            ll k = (x >> i) & 1;
            if (cur->nxt[k] != nullptr && cur->nxt[k]->sz > 0)
            {
                cur = cur->nxt[k];
                ans = (ans << 1);
            }
            else
            {
                cur = cur->nxt[!k];
                ans = (ans << 1) | 1;
            }
        }
        return ans;
    }

    // Collects all numbers stored in subtree into vector v.
    // Usage: subtreeElements(tr.root, 0, B-1, v);
    void subtreeElements(node *cur, ll val, ll bit, vector<ll> &v)
    {
        if (!cur || bit < 0)
        {
            v.push_back(val);
            return;
        }
        if (cur->nxt[0])
            subtreeElements(cur->nxt[0], val, bit - 1, v);
        if (cur->nxt[1])
            subtreeElements(cur->nxt[1], val | (1LL << bit), bit - 1, v);
    }

    // DFS used for the special query: minimum possible x^u − x^v across trie.
    // Usage: tr.dfs(tr.root, tr.B-1);  // result stored in global minans
    void dfs(node *cur, ll bit)
    {
        if (!cur || bit < 0)
            return;
        node *small = cur->nxt[0];
        node *big = cur->nxt[1];
        if (cur->nxt[0] && cur->nxt[1])
        {
            // if (small->sz > big->sz)
            // {
            //     swap(small, big);
            // }
            vector<ll> vals;
            subtreeElements(small, 0, bit - 1, vals);
            ll lclmax = 0;
            for (auto x : vals)
            {
                ll ans = 0;
                node *trav = big;
                for (ll j = bit - 1; j >= 0; j--)
                {
                    if (trav == nullptr)
                        break;
                    ll isSet = !(!Check(x, j));

                    if (trav->nxt[1 - isSet])
                    {
                        ans |= (1LL << j);
                        trav = trav->nxt[1 - isSet];
                    }
                    else
                    {
                        trav = trav->nxt[isSet];
                    }
                }
                lclmax = max(lclmax, ans);
            }
            ll curc = (1LL << bit);
            minans = min(minans, curc - lclmax);
        }
        dfs(cur->nxt[0], bit - 1);
        dfs(cur->nxt[1], bit - 1);
    }
};

int main()
{
    fast;
    ll t;
    // setIO();
    ll tno = 1;
    ;
    t = 1;
    cin >> t;

    while (t--)
    {
        cout << "Case " << tno++ << ": ";
        ll n;
        cin >> n;
        vector<ll> vec(n);
        cin >> vec;
        map<ll,ll>mpp;
        bool ok=0;
        for(auto it:vec) mpp[it]++;
        for(auto it:mpp){
            if(it.second>1){
                ok=1;
            }
        }
        if(ok){
            cout<<0<<nn;
            continue;
        }
        Trie tr;
        for (ll i = 0; i < n; i++)
            tr.insert(vec[i]);
        minans = 4e18;
        tr.dfs(tr.root, tr.B - 1);
        cout << minans << nn;
    }

    return 0;
}
