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
#define nn '\n'
const ll M = 1e9 ;

#define REP(i, n) for (int i = 0; i < (n); i++)

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
        ll k;
        cin>>k;
        vector<ll>b(k);
        REP(i,k) cin>>b[i];
        Matrix mat(k);
        REP(i, k - 1) mat.a[i][i + 1] = 1;
        REP(i, k) cin >> mat.a[k - 1][k - 1 - i];
        ll n;
        cin>>n;
        if(n<=k) cout<<b[n-1]<<nn;
        else{
            auto res=expo_power(mat,n-k);
            long sum = 0;
            REP(i, k) sum = (sum + res.a[k - 1][i] * b[i]) % M;
            cout << sum << endl;

        }

    }

    return 0;
}

