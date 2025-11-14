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
const ll N2 = 1e6 + 10;
const ll Q = 5e5 + 10;
const ll M = 1e9 + 7;

vector<ll> g[N];
vector<ll> in(N), out(N);
vector<ll> R(N);
ll cnt[N2], a[N];
ll ans[Q];
ll n, q;
const ll B = 440;
const ll B2 = 650;

ll totmissing;

ll sqert[B2][B2];
ll sum[B2];

struct query
{
    ll l, r, id, k;
    bool operator<(const query &x) const
    {
        if (l / B == x.l / B)
            return ((l / B) & 1) ? r > x.r : r < x.r;
        return l / B < x.l / B;
    }
};

ll timer;
void euler_tour(ll now, ll prev)
{
    in[now] = timer++;
    for (auto child : g[now])
    {
        if (child != prev)
            euler_tour(child, now);
    }
    out[now] = timer;
}

inline void add(ll i)
{
    ll x = a[i];
    if (cnt[x] == 0)
    {
        if (sqert[x / B2][x % B2] == 1)
        {
            sqert[x / B2][x % B2] = 0;
            sum[x / B2]--;
            totmissing--;
        }
    }
    cnt[x]++;
}

inline void remove(ll i)
{
    ll x = a[i];
    if (cnt[x] == 1)
    {
        if (sqert[x / B2][x % B2] == 0)
        {
            sqert[x / B2][x % B2] = 1;
            sum[x / B2]++;
            totmissing++;
        }
    }
    cnt[x]--;
}

void reset(ll n, ll q)
{
    timer = 0;
    for (ll i = 0; i <= n; i++)
    {
        g[i].clear();
    }

    for (ll i = 0; i < B2; i++)
    {
        sum[i] = 0;
        for (ll j = 0; j < B2; j++)
        {
            sqert[i][j] = 0;
        }
    }
    totmissing = 0;
    for (ll i = 1; i <= 2 * n; i++)
    {
        cnt[i] = 0;
        sqert[i / B2][i % B2] = 1;
        sum[i / B2]++;
        totmissing++;
    }
}


void setIO()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);

    freopen("output.txt", "w", stdout);
#endif // ONLINE_JUDGE
}

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    cin >> t;

    while (t--)
    {
        cin >> n >> q;
        reset(n, q);
        for (ll i = 0; i < n; i++)
        {
            cin >> R[i];
        }
        for (ll i = 0; i < n - 1; i++)
        {
            ll u, v;
            cin >> u >> v;
            u--;
            v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        euler_tour(0, -1);
        for (ll i = 0; i < n; i++)
        {
            a[in[i]] = R[i];
        }
        // for(ll i=0;i<n;i++){
        //     deb2(i,a[i]);
        // }
        vector<query> queries;
        for (ll i = 0; i < q; i++)
        {
            ll p, k;
            cin >> p >> k;
            p--;
            ll l = in[p];
            ll r = out[p] - 1;
            query qq = {l, r, i, k};
            queries.push_back(qq);
        }
        sort(all(queries));
        ll L = 0, R = -1;
        for (ll i = 0; i < q; i++)
        {
            auto qr = queries[i];
            ll l = qr.l, r = qr.r;
            ll qidx = qr.id;
            ll k = qr.k;
            // deb2(l,r);
            // deb2(qidx,k);
            while (L > l)
                add(--L);
            while (R < r)
                add(++R);
            while (L < l)
                remove(L++);
            while (R > r)
                remove(R--);
            if (k > totmissing)
            {
                ans[qidx] = (2 * n) + (k - totmissing);
                continue;
            }
            ll krem = k;
            ll iddx = 0;

            while (iddx < B2 && krem > sum[iddx])
            {
                krem -= sum[iddx];
                iddx++;
            }
            ll liddx = 0;
            while (liddx < B2)
            {
                krem -= sqert[iddx][liddx];
                if (krem == 0)
                {
                    break;
                }
                liddx++;
            }
            ans[qidx] = (ll)iddx * B2 + liddx;
        }
        for (ll i = 0; i < q; i++)
        {
            cout << ans[i] << nn;
        }
    }

    return 0;
}
