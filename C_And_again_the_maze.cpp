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

// Increase stack size for deep DFS recursion
#pragma comment(linker, "/STACK:256000000")

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

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;

const ll N = 1005;
const ll M = 1e9 + 7;


int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

ll n, m;
char grid[N][N];
ll d1[N][N]; // Distance from start
ll d2[N][N]; // Distance from end
bool vis[N][N];
ll tin[N][N], low[N][N];
ll timer;
bool iscut[N][N]; 
ll cnt[N * N];    

bool valid(ll x, ll y)
{
    return (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != 'X');
}

// BFS to calculate distances
void bfs(ll sx, ll sy, ll d[N][N])
{
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < m; j++)
            d[i][j] = M; 

    d[sx][sy] = 0;
    queue<pll> q;
    q.push({sx, sy});

    while (!q.empty())
    {
        pll curr = q.front();
        q.pop();
        ll x = curr.first;
        ll y = curr.second;

        for (int i = 0; i < 4; i++)
        {
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            if (valid(nx, ny) && d[nx][ny] == M)
            {
                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

bool dfs(ll x, ll y, ll px, ll py)
{
    vis[x][y] = 1;
    tin[x][y] = low[x][y] = ++timer;
    bool hasTarget = (x == n - 1 && y == m - 1);

    for (int i = 0; i < 4; i++)
    {
        ll nx = x + dx[i];
        ll ny = y + dy[i];

        if (!valid(nx, ny)) continue;
        if (nx == px && ny == py) continue;

        if (vis[nx][ny])
        {
            low[x][y] = min(low[x][y], tin[nx][ny]);
        }
        else
        {
            bool childHasTarget = dfs(nx, ny, x, y);
            low[x][y] = min(low[x][y], low[nx][ny]);
            if (childHasTarget)
            {
                hasTarget = true;
                if (low[nx][ny] >= tin[x][y])
                {
                    iscut[x][y] = true;
                }
            }
        }
    }
    return hasTarget;
}

int main()
{
    fast;
    cin >> n >> m;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    bfs(0, 0, d1);
    bfs(n - 1, m - 1, d2);

    ll minlen = d1[n - 1][m - 1];

    mem(cnt, 0);
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (d1[i][j] != M && d2[i][j] != M)
            {
                if (d1[i][j] + d2[i][j] == minlen)
                {
                    cnt[d1[i][j]]++;
                }
            }
        }
    }

    mem(vis, 0);
    mem(iscut, 0);
    timer = 0;
    dfs(0, 0, -1, -1);


    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == 'X') continue;

            if ((i == 0 && j == 0) || (i == n - 1 && j == m - 1)) continue;

            bool onShortest = (d1[i][j] != M && d2[i][j] != M && d1[i][j] + d2[i][j] == minlen);

            if (onShortest && cnt[d1[i][j]] == 1)
            {
                if (!iscut[i][j])
                {
                    grid[i][j] = '*';
                }
            }
        }
    }

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            cout << grid[i][j];
        }
        cout << nn;
    }

    return 0;
}


const int N = 1005;
int n, m;
char grid[N][N]; 
bool vis[N][N];
int tin[N][N], low[N][N];
int timer;


bool is_art[N][N]; // Articulation Points
vector<pair<pair<int,int>, pair<int,int>>> bridges; // Bridges


int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != '#'; 
}

// DFS Function
// Call initially as: dfs(start_x, start_y, -1, -1);
void artdfs(int x, int y, int px, int py) {
    vis[x][y] = true;
    tin[x][y] = low[x][y] = ++timer;
    int children = 0;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (!isValid(nx, ny)) continue;
        if (nx == px && ny == py) continue; 

        if (vis[nx][ny]) {

            low[x][y] = min(low[x][y], tin[nx][ny]);
        } else {

            children++;
            artdfs(nx, ny, x, y);
            
            low[x][y] = min(low[x][y], low[nx][ny]);

            // CHECK ARTICULATION POINT
            // If strictly inside the tree (not root) and
            //no back-edge from child subtree to ancestor
            if (px != -1 && low[nx][ny] >= tin[x][y]) {
                is_art[x][y] = true;
            }

            // BRIDGE
            // If no back-edge from child subtree to this node or ancestor
            if (low[nx][ny] > tin[x][y]) {
                bridges.push_back({{x, y}, {nx, ny}});
            }
        }
    }

    // Root special case for Articulation Point
    if (px == -1 && children > 1) {
        is_art[x][y] = true;
    }
}
