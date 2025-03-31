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

template <typename S, typename T>
void smax(S &a, const T &b)
{
    if (a < b)
        a = b;
}
template <typename S, typename T>
void smin(S &a, const T &b)
{
    if (a > b)
        a = b;
}

#define rng_init mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define rng_seed(x) mt19937 rng(x)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
// #define int long long

struct UFDS
{
    int n;
    vector<int> info;

    UFDS(int _n = 0) { init(_n); }

    void init(int _n)
    {
        n = _n;
        info.assign(n, -1);
    }

    int find(int x) { return info[x] < 0 ? x : info[x] = find(info[x]); }

    bool unite(int u, int v)
    {
        if ((u = find(u)) == (v = find(v)))
            return false;

        if (info[u] > info[v])
            swap(u, v);
        info[u] += info[v];
        info[v] = u;

        return true;
    }

    bool connected(int u, int v) { return find(u) == find(v); }
};

const int MXN = 1e5 + 5, INF = 1e9 + 5;

bool is_lucky(int x)
{
    for (int i = x; i > 0; i /= 10)
        if (i % 10 != 4 && i % 10 != 7)
            return false;

    return true;
}

void solve()
{
    int N, M;
    cin >> N >> M;

    UFDS ufds(N);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;

        ufds.unite(u, v);
    }

    vector<bool> seen(N, false);
    vector<int> freq(N + 1, 0);

    for (int i = 0; i < N; i++)
    {
        int par = ufds.find(i);
        if (seen[par])
            continue;

        seen[par] = true;
        freq[-ufds.info[par]]++;
    }

    vector<pair<int, int>> components;
    for (int i = 1; i <= N; i++)
    {
        if (freq[i] > 0)
        {
            components.emplace_back(i, freq[i]);

            if (is_lucky(i))
            {
                cout << 0;
                return;
            }
        }
    }

    vector<int> dp(N + 1, INF);
    dp[0] = 0;

    for (const auto &[w, k] : components)
    {
        vector<int> ndp = dp;
        for (int i = 0; i < w; i++)
        {
            deque<pair<int, int>> window;

            for (int j = i, mul = 0; j <= N; j += w, mul++)
            {
                while (!window.empty() && window.front().second < mul - k)
                    window.pop_front();

                if (!window.empty())
                    smin(ndp[j], window.front().first + mul);

                while (!window.empty() && window.back().first >= dp[j] - mul)
                    window.pop_back();

                window.emplace_back(dp[j] - mul, mul);
            }
        }

        swap(ndp, dp);
    }

    int ans = INF;
    for (int i = 1; i <= N; i++)
    {
        if (dp[i] >= INF)
            continue;

        if (is_lucky(i))
            smin(ans, dp[i] - 1);
    }

    cout << (ans < INF ? ans : -1);
}

int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    // cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}


/* Given an array 𝐴
 of 𝑁
 elements where 0≤𝐴𝑖≤𝑋
 for some positive integer 𝑋
, find all possible subset sums.
*/

int main() {
    int N;
    cin >> N;

    // Sum of elements <= N implies that every element is <= N
    vector<int> freq(N + 1, 0);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        freq[x]++;
    }

    vector<pair<int, int>> compressed;
    for (int i = 1; i <= N; i++) {
        if (freq[i] > 0) compressed.emplace_back(i, freq[i]);
    }

    vector<int> dp(N + 1, 0);
    dp[0] = 1;

    for (const auto &[w, k] : compressed) {
        vector<int> ndp = dp;

        for (int p = 0; p < w; p++) {
            int sum = 0;

            for (int multiple = p, count = 0; multiple <= N; multiple += w, count++) {
                if (count > k) {
                    sum -= dp[multiple - w * count];
                    count--;
                }
                
                if (sum > 0) ndp[multiple] = 1;
                sum += dp[multiple];
            }
        }

        swap(dp, ndp);
    }

    cout << "Possible subset sums are:\n";
    for (int i = 0; i <= N; i++) {
        if (dp[i] > 0) cout << i << " ";
    }
}
