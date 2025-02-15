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

#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")
// Printings & debugging
#define nn '\n'

ll a, b, x, y, d;
const ll N = 2e5 + 10;
const ll M = 5e18 + 7;



int main()
{
    fast;
    ll t;
    t = 1;
    ll n;

    while (1)
    {
        cin>>n;
        if (n == 0)
            break;
        cin >> a >> b >> d;

        set<ll> dir1[105], dir2[105];

        for (ll i = 0; i < n; i++)
        {
            cin >> x >> y;

            dir1[y].insert(x);
            dir2[x].insert(y);
        }
        ll curdir = 1;
        bool round = 0;
        map<pair<pair<ll, ll>, ll>, ll> mpp;

        while (d > 0)
        {
            
            if (curdir == 1)
            {
                curdir = 2;
                auto pos = dir1[b].upper_bound(a);
                if (pos == dir1[b].end())
                {
                    a += d;
                    d = 0;
                    continue;
                }
                ll stop = *pos;
                ll go = min(stop - 1 - a, d);
                a += go;
                d -= go;
                
                
                
            }
            else if (curdir == 2)
            {
                curdir = 3;
                auto pos = dir2[a].upper_bound(b);
                if (pos == dir2[a].end())
                {
                    b += d;
                    d = 0;
                    continue;
                }
                ll stop = *pos;
                ll go = min(d, stop - 1 - b);
                b += go;
                d -= go;
                
            }
            else if (curdir == 3)
            {
                curdir = 4;
                auto pos = dir1[b].lower_bound(a);
                if (pos == dir1[b].begin())
                {
                    a -= d;
                    d = 0;
                    continue;
                }
                --pos;
                ll stop = *pos;
                ll go = min(d, a - stop - 1);
                
                a -= go;
                d -= go;
            }
            else
            {
                curdir = 1;
                auto pos = dir2[a].lower_bound(b);
                if (pos == dir2[a].begin())
                {
                    b -= d;
                    d = 0;
                    continue;
                }
                --pos;
                ll stop = *pos;
                ll go = min(d, b - stop - 1);
                b -= go;
                d -= go;
                
            }

            if (d && round == 0 && mpp.find({{a, b}, curdir}) != mpp.end())
            {
                round = 1;
                ll dist = mpp[{{a, b}, curdir}];
                ll len = dist - d;
                if(len==0) break;
                d %= len;
            }
            if (round == 0)
                mpp[{{a, b}, 1}] = d;
        }
        cout << a << " " << b << nn;
    }

    return 0;
}
