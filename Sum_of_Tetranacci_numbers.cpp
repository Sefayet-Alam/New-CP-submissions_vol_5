#include <bits/stdc++.h>

using namespace std;

#define eb emplace_back
#define ii pair<int, int>
#define OK (cerr << "OK" << endl)
#define debug(x) cerr << #x " = " << (x) << endl
#define ff first
#define ss second
#define int long long
#define tt tuple<int, int, int>
#define all(x) x.begin(), x.end()
#define vvi vector<vector<int>>
#define vvii vector<vector<pair<int, int>>>
#define Mat(n, m, v) vector<vector<int>>(n, vector<int>(m, v))
#define endl '\n'

constexpr int INF = 2e18;
constexpr int MOD = 1000000007;
constexpr int MAXN = 2e5 + 3;

static int mod(int n) {
  n %= MOD;
  if (n < 0)
    n += MOD;
  return n;
}

struct Matrix {
  static constexpr int MOD = 1000000007;

  // static matrix, if it's created multiple times, it's recommended
  // to avoid TLE.
  static constexpr int MAXN = 5, MAXM = 5;
  array<array<int, MAXM>, MAXN> mat = {};
  int n, m;
  Matrix(const int n, const int m) : n(n), m(m) {
    assert(n <= MAXN), assert(m <= MAXM);
  }

  /// Creates a n x n identity matrix.
  ///
  /// Time Complexity: O(n*n)
  Matrix identity() {
    assert(n == m);
    Matrix mat_identity(n, m);
    for (int i = 0; i < n; ++i)
      mat_identity.mat[i][i] = 1;
    return mat_identity;
  }

  /// Multiplies matrices mat and other.
  ///
  /// Time Complexity: O(mat.size() ^ 3)
  Matrix operator*(const Matrix &other) const {
    assert(m == other.n);
    Matrix ans(n, other.m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        for (int k = 0; k < m; ++k)
          ans.mat[i][j] = mod(ans.mat[i][j] + mat[i][k] * other.mat[k][j]);
    return ans;
  }

  /// Exponentiates the matrix mat to the power of p.
  ///
  /// Time Complexity: O((mat.size() ^ 3) * log2(p))
  Matrix expo(int p) {
    assert(p >= 0);
    Matrix ans = identity(), cur_power(n, m);
    cur_power.mat = mat;
    while (p) {
      if (p & 1)
        ans = ans * cur_power;

      cur_power = cur_power * cur_power;
      p >>= 1;
    }
    return ans;
  }
};

int calc(int n) {
  if (n <= 4)
    return (n == 4);
  // vector<int> dp(5);
  // vector<int> new_dp(5);
  // dp[3] = 1;

  // for (int i = 4; i <= n; ++i) {

  //   new_dp[3] = dp[3] + dp[2] + dp[1] + dp[0];
  //   new_dp[3] %= MOD;
  //   new_dp[4] = new_dp[4] + dp[3];
  //   new_dp[4] %= MOD;

  //   for (int j = 0; j < 3; ++j)
  //     new_dp[j] = dp[j + 1];

  //   dp = new_dp;
  // }

  // return dp[4];

  Matrix mat(5, 5);
  mat.mat[3][3] = 1;
  mat.mat[3][2] = 1;
  mat.mat[3][1] = 1;
  mat.mat[3][0] = 1;
  mat.mat[4][4] = 1;
  mat.mat[4][3] = 1;

  for (int i = 0; i < 3; ++i)
    mat.mat[i][i + 1] = 1;

  Matrix ini(5, 1);
  ini.mat[3][0] = 1;

  mat = mat.expo(n - 3);
  mat = mat * ini;

  return mat.mat[4][0];
}

#define MULTIPLE_TEST_CASES
void solve() {
  int a, b;
  cin >> a >> b;

  cout << mod(calc(++b) - calc(a)) << endl;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t = 1;
#ifdef MULTIPLE_TEST_CASES
  cin >> t;
#endif
  while (t--)
    solve();
}