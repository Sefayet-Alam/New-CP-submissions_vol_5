#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

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

typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vvl;

const ll N = 3e5 + 10;
ll n;
vl adj[N];
ll parentArr[N];
ll depthArr[N];

vl buildpath(ll u, ll v)
{
    vl leftnode, rightnode;
    ll curru = u, currv = v;
    while (curru != currv)
    {
        if (depthArr[curru] > depthArr[currv])
        {
            leftnode.push_back(curru);
            curru = parentArr[curru];
        }
        else if (depthArr[currv] > depthArr[curru])
        {
            rightnode.push_back(currv);
            currv = parentArr[currv];
        }
        else
        {
            leftnode.push_back(curru);
            rightnode.push_back(currv);
            curru = parentArr[curru];
            currv = parentArr[currv];
        }
    }
    leftnode.push_back(curru);
    reverse(all(rightnode));
    leftnode.insert(leftnode.end(), all(rightnode));
    return leftnode;
}

vpll decomposetreetopaths()
{
    if (n <= 1) return {};
    if (n == 2) {
        parentArr[0] = -1; depthArr[0] = 0;
        parentArr[1] = 0; depthArr[1] = 1;
        return {{0, 1}};
    }

    ll root = -1;
    for (ll i = 0; i < n; i++) {
        if (adj[i].size() > 1) {
            root = i;
            break;
        }
    }

    vl leaves;
    function<void(ll, ll, ll)> traverse = [&](ll u, ll p, ll d) {
        parentArr[u] = p;
        depthArr[u] = d;
        if (adj[u].size() == 1) leaves.push_back(u);
        for (ll v : adj[u]) {
            if (v != p) traverse(v, u, d + 1);
        }
    };
    traverse(root, -1, 0);

    vpll endpoints;
    ll lsize = leaves.size();
    ll pathcount = (lsize + 1) / 2;
    for (ll i = 0; i < pathcount; i++) {
        endpoints.push_back({leaves[i], leaves[(i + lsize / 2) % lsize]});
    }
    return endpoints;
}

bool ask(ll u, ll v)
{
    cout << "? " << u + 1 << " " << v + 1 << endl;
    int ret;
    if (!(cin >> ret) || ret == -1) exit(0);
    return (ret == 1);
}

int main()
{
    fast;
    int t;
    cin>>t;
    while (t--)
    {
        cin >> n;
        for (ll i = 0; i < n; i++) adj[i].clear();
        for (ll i = 0; i < n - 1; i++) {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        if (n == 1) {
            cout << "! 1" << endl;
            continue;
        }

        vpll endpoints = decomposetreetopaths();
        pll target = endpoints.back();

        for (int i = 0; i < (int)endpoints.size() - 1; i++) {
            if (ask(endpoints[i].first, endpoints[i].second)) {
                target = endpoints[i];
                break;
            }
        }

        vl p = buildpath(target.first, target.second);
        ll l = 0, r = (ll)p.size() - 1;
        while (l < r) {
            ll mid = l + (r - l) / 2;
            if (ask(p[l], p[mid])) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        cout << "! " << p[l] + 1 << endl;
    }
    return 0;
}