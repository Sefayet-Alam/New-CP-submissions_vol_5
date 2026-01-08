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

// Printings & debugging
#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl

const double EPS = 1e-9;
const ll M = 1e9;


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
            product.a[i][k] += (a[i][j] * other.a[j][k]) % M;
            product.a[i][k] %= M;
        }
        return product;
    }
};
Matrix expo_power(Matrix a, ll k)
{
    int size = a.size;
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

ll calc(ll n, vector<ll> b, vector<ll> c)
{
    // suppose f[n]=c[0]*f[n-1]+c[1]*f[n-2]+c[n-3]*f[n-3]...
    // sequence is: b[0],b[1],b[2],...
    // need to find the nth element
    ll k = b.size();
    if (n <= k)
        return b[n - 1];
    Matrix mat(k);
    REP(i, k - 1)
    {
        mat.a[i][i + 1] = 1;
    }
    REP(i, k)
    {
        mat.a[k - 1][k - 1 - i] = c[i];
    }
    auto res = expo_power(mat, n - k);
    long sum = 0;
    REP(i, k)
    {
        sum = (sum + res.a[k - 1][i] * b[i]) % M;
    }
    return sum;
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
        ll m;
        cin>>m;
        vector<ll>b(m),c(m);
        for(ll i=0;i<m;i++) cin>>b[i];
        for(ll i=0;i<m;i++) cin>>c[i];
        ll n;
        cin>>n;
        cout<<calc(n,b,c)<<nn;
    }

    return 0;
}
