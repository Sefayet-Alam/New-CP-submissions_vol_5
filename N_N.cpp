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



const ll N=2e5+10;
const ll INF = 1e18, NINF = -1e18;

/*
RangeAdd (add x from l to r-1)
RangeSum (Get sum from l to r-1)
RangeMinm (Get minm from l to r-1)
RangeMaxm (Get maxm from l to r-1)
GetAlive (Get how many nodes from l to r-1 has values > 0 )
RangeAssign (Assign x from l to r-1..Note that it can revive any dead nodes,
if x>0 , then all nodes from l to r-1 will be revived... 
Else if x<=0 all nodes from l to r-1 will be dead)
*/

struct SegTree {
    struct item {ll s, lz, as, liv, mn, mx;};
    ll sz; vector<item> t; const ll NOP = LLONG_MAX;

    item mk(ll h){if(h>0)return{h,0,NOP,1,h,h};return{0,0,NOP,0,INF,NINF};}
    item mrg(const item&a,const item&b){return{a.s+b.s,0,NOP,a.liv+b.liv,min(a.mn,b.mn),max(a.mx,b.mx)};}
    void app_as(ll x,ll v,ll len){t[x].as=v;t[x].lz=0;if(v>0){t[x].s=v*len;t[x].liv=len;t[x].mn=t[x].mx=v;}else{t[x].s=0;t[x].liv=0;t[x].mn=INF;t[x].mx=NINF;}}
    void app_ad(ll x,ll v,ll len){if(t[x].as!=NOP){app_as(x,t[x].as+v,len);return;}if(!t[x].liv)return;t[x].lz+=v;t[x].s+=v*t[x].liv;t[x].mn+=v;t[x].mx+=v;}
    void psh(ll x,ll lx,ll rx){if(rx-lx==1||(t[x].as==NOP&&t[x].lz==0))return;ll m=lx+(rx-lx)/2;if(t[x].as!=NOP){app_as(2*x+1,t[x].as,m-lx);app_as(2*x+2,t[x].as,rx-m);t[x].as=NOP;}if(t[x].lz!=0){app_ad(2*x+1,t[x].lz,m-lx);app_ad(2*x+2,t[x].lz,rx-m);t[x].lz=0;}}
    void pul(ll x){t[x]=mrg(t[2*x+1],t[2*x+2]);}
    void bld(const vl&a,ll x,ll lx,ll rx){if(rx-lx==1){if(lx<a.size())t[x]=mk(a[lx]);return;}ll m=lx+(rx-lx)/2;bld(a,2*x+1,lx,m);bld(a,2*x+2,m,rx);pul(x);}
    void r_add(ll l,ll r,ll v,ll x,ll lx,ll rx){if(lx>=r||rx<=l)return;if(lx>=l&&rx<=r&&t[x].mn+v>0){app_ad(x,v,rx-lx);return;}if(lx>=l&&rx<=r&&t[x].mx!=NINF&&t[x].mx+v<=0){app_as(x,0,rx-lx);return;}psh(x,lx,rx);if(rx-lx==1){t[x]=mk((t[x].liv>0?t[x].s:0)+v);return;}ll m=lx+(rx-lx)/2;r_add(l,r,v,2*x+1,lx,m);r_add(l,r,v,2*x+2,m,rx);pul(x);}
    void r_asgn(ll l,ll r,ll v,ll x,ll lx,ll rx){if(lx>=r||rx<=l)return;if(lx>=l&&rx<=r){app_as(x,v,rx-lx);return;}psh(x,lx,rx);ll m=lx+(rx-lx)/2;r_asgn(l,r,v,2*x+1,lx,m);r_asgn(l,r,v,2*x+2,m,rx);pul(x);}
    item qry(ll l,ll r,ll x,ll lx,ll rx){if(lx>=r||rx<=l)return{0,0,NOP,0,INF,NINF};if(lx>=l&&rx<=r)return t[x];psh(x,lx,rx);ll m=lx+(rx-lx)/2;return mrg(qry(l,r,2*x+1,lx,m),qry(l,r,2*x+2,m,rx));}
public:
    void build(const vl&a){sz=1;while(sz<a.size())sz<<=1;t.assign(2*sz,mk(0));bld(a,0,0,sz);}
    void RangeAdd(ll l,ll r,ll v){if(l<r)r_add(l,r,v,0,0,sz);}
    void RangeAssign(ll l,ll r,ll v){if(l<r)r_asgn(l,r,v,0,0,sz);}
    ll RangeSum(ll l,ll r){return l<r?qry(l,r,0,0,sz).s:0;}
    ll GetAlive(ll l,ll r){return l<r?qry(l,r,0,0,sz).liv:0;}
    ll RangeMinm(ll l,ll r){if(l>=r)return 0;ll res=qry(l,r,0,0,sz).mn;return res==INF?0:res;}
    ll RangeMaxm(ll l,ll r){if(l>=r)return 0;ll res=qry(l,r,0,0,sz).mx;return res==NINF?0:res;}
}; // use l to r+1 to get/upd l to r

vl g[N];
ll h[N];
ll in[N], out[N];
ll timer;
vl flath;
void euler_tour(ll now, ll prev)
{
    in[now] = timer++;
    for (auto child : g[now])
    {
        if (child != prev)
            euler_tour(child, now);
    }
    out[now] = timer;
}

void solve()
{
    ll n;
    cin >> n;
    h[0] = INF;
    for (ll i = 1; i <= n; i++)
    {
        ll sup;
        cin >> h[i] >> sup;
        g[sup].push_back(i);
    }

    timer = 0;
    euler_tour(0, -1);

    flath.assign(timer, INF);

    for (ll i = 0; i <= n; i++)
    {
        flath[in[i]] = h[i];
    }

    SegTree st;
    st.build(flath);

    ll q;
    cin >> q;
    while (q--)
    {
        ll type;
        cin >> type;
        if (type == 1)
        {
            ll a, x;
            cin >> a >> x;
            st.RangeAdd(in[a] + 1, out[a], -x);
        }
        else
        {
            ll a;
            cin >> a;
            cout << st.GetAlive(in[a] + 1, out[a]) << nn;
        }
    }
}

int main()
{
    fast;
    solve();
    return 0;
}