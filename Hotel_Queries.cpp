#include <bits/stdc++.h>

using namespace std;


// VVI
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll long long

#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;

struct Vertex
{
    int value;
    int index;
};
const int MAXN = 200011;
Vertex tree[4 * MAXN];
#define INF -1e9 + 7;

// This generates a segment tree which can give me
// the maximum element in a range as well as the index of that element.

void build(int a[], int v, int tl, int tr)
{

    if (tl == tr)
    {
        tree[v].value = a[tl];
        tree[v].index = tl + 1;
        return;
    }
    int mid = (tl + tr) / 2;
    build(a, 2 * v, tl, mid);
    build(a, 2 * v + 1, mid + 1, tr);
    if (tree[2 * v].value >= tree[2 * v + 1].value)
    {
        tree[v] = tree[2 * v];
    }
    else
    {
        tree[v] = tree[2 * v + 1];
    }
}

int query(int v, int tl, int tr, int num)
{

    if (tree[v].value < num)
        return 0;

    if (tl == tr)
    {

        tree[v].value = tree[v].value - num;
        return tree[v].index;
    }

    int mid = (tl + tr) / 2;

    if (tree[2 * v].value >= num)
    {
        int idx = query(2 * v, tl, mid, num);
        if (tree[2 * v].value >= tree[2 * v + 1].value)
        {
            tree[v] = tree[2 * v];
        }
        else
        {
            tree[v] = tree[2 * v + 1];
        }
        return idx;
    }
    else
    {
        int idx = query(2 * v + 1, mid + 1, tr, num);
        if (tree[2 * v].value >= tree[2 * v + 1].value)
        {
            tree[v] = tree[2 * v];
        }
        else
        {
            tree[v] = tree[2 * v + 1];
        }

        return idx;
    }
}

void solve()
{

    int n, m;
    cin >> n >> m;
    int h[n], r[m];
    for (int i = 0; i < n; i++)
        cin >> h[i];
    for (int i = 0; i < m; i++)
        cin >> r[i];
    build(h, 1, 0, n - 1);

    for (int i = 0; i < m; i++)
        cout << query(1, 0, n - 1, r[i]) << " ";
}

int main(){
    solve();
    return 0;
}