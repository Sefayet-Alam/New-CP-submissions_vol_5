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

#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 998244353;


#define REP(i, n) for (int i = 0; i < (n); i++)
// solution for eqn like 𝑓𝑛=∑𝑘𝑖=1𝑐𝑖∗𝑓𝑛−𝑖
// matrix will be like: 
// 0 1 0 0
// 0 0 1 0
// 0 0 0 1
//  .....
// ck-1 ck-2 ck-3 ck-4 ....(k-1) th row

// b:
// f[0]=b[0], f[1]=b[1],... f[k-1]=b[k-1] ,...first k values are given
struct Matrix
{
    ll size;
    ll a[12][12] = {0}; 
    Matrix(int sz) : size(sz) {}

    Matrix operator*(const Matrix &other)
    {
        Matrix product(size);
        REP(i, size)
        REP(j, size)
        REP(k, size)
        {
            product.a[i][k] += (a[i][j] * other.a[j][k])%M;
            product.a[i][k]%=M;
        }
        return product;
    }
};
Matrix expo_power(Matrix a, ll k)
{
    int size=a.size;
    Matrix product(size);
    REP(i, size)
    product.a[i][i] = 1;
    while (k > 0)
    {
        if (k % 2)
        {
            product = (product * a);
        }
        a = a * a;
        k /= 2;
    }
    return product;
}

ll fibonacci_at(ll n, ll a, ll b) {
    if (n == 0) return (a + b) % M;
    if (n == 1) return (a + 2 * b) % M;
    
    ll k = 2;  // Fibonacci: f[n] = f[n-1] + f[n-2]
    vector<ll> b_vec(k);
    b_vec[0] = (a + b) % M;      // f[0]
    b_vec[1] = (a + 2 * b) % M;  // f[1]

    Matrix mat(k);
    // Standard Fibonacci matrix for your template:
    mat.a[0][1] = 1;           // [0, 1]
    mat.a[1][0] = 1;           // c2 = 1 (coefficient for f[n-2])
    mat.a[1][1] = 1;           // c1 = 1 (coefficient for f[n-1])

    if (n < k) {
        return b_vec[n] % M;
    }
    
    auto res = expo_power(mat, n - 1);
    ll sum = 0;
    REP(i, k) {
        sum = (sum + (res.a[k - 1][i] * b_vec[i]) % M) % M;
    }
    return sum % M;
}

vl fibobrute(ll n,ll a,ll b){
    vector<ll>f(n+1,0);
    f[0]=(a+b);
    f[1]=(a+b+b);
    for(ll i=2;i<=n;i++){
        f[i]=(f[i-1]+f[i-2]);
    }
    for(ll i=1;i<=n;i++) f[i]+=f[i-1];
    return f;
}

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
        ll n;
        cin >> n;
        vector<ll> vec(n);
        cin >> vec;

        ll k = 3;
        Matrix finl(k);
        ll maxm = 0;
        ll maxi[54];
        mem(maxi,0);
        ll maxms[54];
        mem(maxms,0);
        for (ll i = 0; i < n - 1; i++)
        {
            ll a=min(vec[i],vec[i+1]);
            ll b=max(vec[i],vec[i+1]);
            auto til54=fibobrute(54,a,b);
            // deb2(i,til54);
            for(ll j=0;j<54;j++){
                if(til54[j]>maxms[j]){
                    maxms[j]=til54[j];
                    maxi[j]=i;
                }
            }
        }
        ll q;
        cin >> q;
        Matrix init(k);
        while (q--)
        {
            ll x;
            cin >> x;
            x--;
            
            ll x2=min(52LL,x);
            ll idx=maxi[x2];
            ll a=min(vec[idx],vec[idx+1]);
            ll b=max(vec[idx],vec[idx+1]);
            ll fnp2=fibonacci_at(x+2,a,b);
            ll fn1=fibonacci_at(1,a,b);
            ll maxm=(fnp2-fn1+M)%M;
            cout<<maxm<<" ";

        }
        cout << nn;
    }

    return 0;
}


