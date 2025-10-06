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

#define ll int
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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 5e5 + 10;
const ll M = 1e9 + 7;

vector<int> smallest_factor;
vector<bool> prime;
vector<int> primes;

void sieve(int maximum)
{
    maximum = max(maximum, 2);
    smallest_factor.assign(maximum + 1, 0);
    prime.assign(maximum + 1, true);
    prime[0] = prime[1] = false;
    primes = {2};

    for (int p = 2; p <= maximum; p += 2)
    {
        prime[p] = p == 2;
        smallest_factor[p] = 2;
    }

    for (int p = 3; p * p <= maximum; p += 2)
        if (prime[p])
            for (int i = p * p; i <= maximum; i += 2 * p)
                if (prime[i])
                {
                    prime[i] = false;
                    smallest_factor[i] = p;
                }

    for (int p = 3; p <= maximum; p += 2)
        if (prime[p])
        {
            smallest_factor[p] = p;
            primes.push_back(p);
        }
}

ll n;
vector<ll> vec(N);

vl divisors[N];

void divisor_store()
{
    for (int i = 1; i < N; i++)
    {
        for (int j = i; j < N; j += i)
        {
            divisors[j].push_back(i);
        }
    }
    for (ll i = 1; i < N; i++)
    {
        sort(all(divisors[i]), greater<ll>());
    }
}
const ll O = 1420;

ll dp[2][O];

ll dp2[N];
ll count(ll x)
{
    if (x == 0) return 0;
    ll nowx = x;
    ll ret = 0;
    if (dp2[nowx] != -1)
        return dp2[nowx];
    while (x > 1 && smallest_factor[x] != 0)
    {
        x /= smallest_factor[x];
        ret++;
    }
    if (x > 1) ret++;
    return dp2[nowx] = ret;
}

int main()
{
    fast;
    ll t;
    t = 1;
    cin >> t;
    sieve(N);
    divisor_store();

    mem(dp2, -1);
    while (t--)
    {
        cin >> n;
        vec.resize(n);
        cin >> vec;

        if (n == 1)
        {
            cout << 0 << nn;
            continue;
        }

        for (ll i = 0; i < 2; i++)
        {
            for (ll j = 0; j < O; j++)
            {
                dp[i][j] = INT_MAX;
            }
        }

        ll curr = 0;
        for (ll j = 0; j < SZ(divisors[vec[0]]); j++)
        {
            dp[curr][j] = count(vec[0] / divisors[vec[0]][j]);
        }

        for (ll i = 1; i < n - 1; i++)
        {
            curr = i % 2;
            ll prev = (i - 1) % 2;
            for(ll j = 0; j < O; j++) dp[curr][j] = INT_MAX;

            ll prevcnt = SZ(divisors[vec[i - 1]]);
            if(prevcnt == 0) continue;

            vl suffprev(prevcnt + 1, INT_MAX);
            for (ll k = prevcnt - 1; k >= 0; k--)
            {
                suffprev[k] = min(suffprev[k + 1], dp[prev][k]);
            }

            ll pp = 0;
            for (ll j = 0; j < SZ(divisors[vec[i]]); j++)
            {
                ll curdiv = divisors[vec[i]][j];
                while (pp < prevcnt && divisors[vec[i - 1]][pp] > curdiv)
                {
                    pp++;
                }
                
                if (pp < prevcnt)
                {
                    ll minprev = suffprev[pp];
                    if (minprev != INT_MAX)
                    {
                        ll cost = count(vec[i] / curdiv);
                        dp[curr][j] = cost + minprev;
                    }
                }
            }
        }

        ll ans = INT_MAX;
        ll lastidx = n - 2;
        ll cons = divisors[vec[n - 1]][0];
        curr = lastidx % 2;

        for (ll j = 0; j < SZ(divisors[vec[lastidx]]); j++)
        {
            if (divisors[vec[lastidx]][j] <= cons)
            {
                ans = min(ans, dp[curr][j]);
            }
        }
        
        if (ans == INT_MAX)
        {
            ans = 0;
        }
        cout << ans << nn;
    }

    return 0;
}