#include <bits/stdc++.h>

using namespace std;

// VVI
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll long long

// Printings & debugging
#define nn '\n'

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



#define REP(i, n) for (int i = 0; i < (n); i++)
/*
[1  1]   *   [f(n)    f(n-1)]
[1  0]       [f(n-1)  f(n-2)] 
results to:
[f(n+1)  f(n)  ]
[f(n)    f(n-1)]
so base_mat(1, 1, 1, 0); -> transforms f[n],f[n-1] to f[n+1],f[n]
base^x transforms f[n],f[n-1] to f[n+x],f[n+x-1]
*/
struct Matrix
{
    ll a[2][2] = {0};
    Matrix() {}
    Matrix(ll x, ll y, ll z, ll w)
    {
        a[0][0] = x;
        a[0][1] = y;
        a[1][0] = z;
        a[1][1] = w;
    }

    Matrix operator*(const Matrix &other) const
    {
        Matrix res;
        REP(i, 2)
        REP(j, 2) REP(k, 2)
        {
            res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % M;
        }
        return res;
    }

    Matrix operator+(const Matrix &other) const
    {
        Matrix res;
        REP(i, 2)
        REP(j, 2)
        {
            res.a[i][j] = (a[i][j] + other.a[i][j]) % M;
        }
        return res;
    }
};

Matrix base_mat(1, 1, 1, 0);
Matrix identity_mat(1, 0, 0, 1);
Matrix zero_mat(0, 0, 0, 0);


const int MAX_POW = 62; 
vector<Matrix> pow2;

void precompute_powers()
{
    pow2.resize(MAX_POW + 1);
    pow2[0] = base_mat;
    for (int i = 1; i <= MAX_POW; i++)
    {
        pow2[i] = pow2[i - 1] * pow2[i - 1];
    }
}

Matrix mat_power_fast(ll k)
{
    if (k < 0)
        return zero_mat;
    if (k == 0)
        return identity_mat;

    Matrix res = identity_mat;
    for (int i = 0; i <= MAX_POW; i++)
    {
        if (k & (1LL << i))
        {
            res = res * pow2[i];
        }
    }
    return res;
}

struct item
{
    /*
    mat is basically
    [f(n)    f(n-1)]
    [f(n-1)  f(n-2)]
    */
    Matrix mat;
    ll lazy;
    
};

struct segment_tree
{
    int size;
    vector<item> tree;
    ll no_op = 0;
    item initnode;

    segment_tree()
    {
        initnode.mat = zero_mat;
        initnode.lazy = no_op;
        size = 0;
    }

    item merge(const item &a, const item &b)
    {
        item ret;
        ret.mat = a.mat + b.mat;
        ret.lazy = no_op;
        return ret;
    }

    void init(int n)
    {
        size = 1;
        while (size < n)
            size <<= 1;
        tree.assign(2 * size, initnode);
    }

    void build(const vector<ll> &a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
            {
                tree[x].lazy = no_op;
                if (a[lx] <= 0)
                {
                    tree[x].mat = zero_mat;
                }
                else
                {
                    tree[x].mat = mat_power_fast(a[lx] - 1);
                }
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(const vector<ll> &a)
    {
        build(a, 0, 0, size);
    }

    void apply_lazy(int x, ll lazy_val)
    {
        if (lazy_val == 0)
            return;
        tree[x].lazy += lazy_val;
        Matrix shift = mat_power_fast(lazy_val); //find base^x
        tree[x].mat = tree[x].mat * shift;
    }
    /*
    Here,shift works coz fibonacci is linear:
    (fibo(a) + fibo(b) + fibo(c)) * base^k  i.e shifting sum by k
    = fibo(a)*base^k + fibo(b)*base^k + fibo(c)*base^k
    = fibo(a+k) + fibo(b+k) + fibo(c+k) i.e shifting all by k then sum
    */

    void propagate(int x, int lx, int rx)
    {
        if (tree[x].lazy == no_op)
            return;
        if (rx - lx > 1)
        {
            apply_lazy(2 * x + 1, tree[x].lazy);
            apply_lazy(2 * x + 2, tree[x].lazy);
        }
        tree[x].lazy = no_op;
    }

    ll RangeQuery(int l, int r, int x, int lx, int rx)
    {
        propagate(x, lx, rx);
        if (lx >= r || l >= rx)
            return 0;
        if (lx >= l && rx <= r)
        {
            return tree[x].mat.a[0][0] % M; //a[0][0] holds f[n] 
        }
        int m = (lx + rx) / 2;
        ll s1 = RangeQuery(l, r, 2 * x + 1, lx, m);
        ll s2 = RangeQuery(l, r, 2 * x + 2, m, rx);
        return (s1 + s2) % M;
    }

    ll RangeQuery(int l, int r)
    {
        return RangeQuery(l, r, 0, 0, size);
    }

    void RangeUpdate(int l, int r, ll v, int x, int lx, int rx)
    {
        propagate(x, lx, rx);
        if (lx >= r || l >= rx)
            return;
        if (lx >= l && rx <= r)
        {
            apply_lazy(x, v);
            return;
        }
        int m = (lx + rx) / 2;
        RangeUpdate(l, r, v, 2 * x + 1, lx, m);
        RangeUpdate(l, r, v, 2 * x + 2, m, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void RangeUpdate(int l, int r, ll v)
    {
        RangeUpdate(l, r, v, 0, 0, size);
    }
};
int main()
{
    fast;
    precompute_powers();

    ll n, q;
    cin >> n >> q;
    vector<ll> vec(n);
    cin >> vec;
    segment_tree sg;
    sg.init(n);
    sg.build(vec);
    while (q--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            sg.RangeUpdate(l, r + 1, x);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << sg.RangeQuery(l, r + 1) << nn;
        }
    }

    return 0;
}
