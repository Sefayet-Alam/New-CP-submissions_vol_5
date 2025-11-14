#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll long long
#define SZ(a) (ll)a.size()
#define UNIQUE(a) (a).erase(unique(all(a)), (a).end())
#define mp make_pair
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()
#define nn '\n'

typedef pair<ll, ll> pll;
typedef vector<ll> vl;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

namespace io{
    template<typename First, typename Second> ostream& operator << ( ostream &os, const pair<First, Second> &p ) { return os << p.first << " " << p.second; }
    template<typename First, typename Second> ostream& operator << ( ostream &os, const map<First, Second> &mp ) { for( auto it : mp ) { os << it << endl;  } return os; }
    template<typename First> ostream& operator << ( ostream &os, const vector<First> &v ) { bool space = false; for( First x : v ) { if( space ) os << " "; space = true; os << x; } return os; }
    template<typename First> ostream& operator << ( ostream &os, const set<First> &st ) { bool space = false; for( First x : st ) { if( space ) os << " "; space = true; os << x; } return os; }
    template<typename First> ostream& operator << ( ostream &os, const multiset<First> &st ) { bool space = false; for( First x : st ) { if( space ) os << " "; space = true; os << x; } return os; }
    template<typename First, typename Second> istream& operator >> ( istream &is, pair<First, Second> &p ) { return is >> p.first >> p.second; }
    template<typename First> istream& operator >> ( istream &is, vector<First> &v ) { for( First &x : v ) { is >> x; } return is; }
    long long fastread(){ char c; long long d = 1, x = 0; do c = getchar(); while( c == ' ' || c == '\n' ); if( c == '-' ) c = getchar(), d = -1; while( isdigit( c ) ){ x = x * 10 + c - '0'; c = getchar(); } return d * x; }
} using namespace io;


/// BIT MANIPULATION

#define Set(x, k) (x |= (1LL << k))
#define Unset(x, k) (x &= ~(1LL << k))
#define Check(x, k) (x & (1LL << k))
#define Toggle(x, k) (x ^ (1LL << k))

ll popcount(ll x) { return __builtin_popcountll(x); };
ll poplow(ll x) { return __builtin_ctzll(x); };
ll pophigh(ll x) { return 63 - __builtin_clzll(x); };
struct SparseTable {
    vector<vector<ll>> st;
    ll n;
    ll op(ll a, ll b) { return a & b; }
    void init(const vector<ll> &vec) {
        n = SZ(vec);
        if (n == 0) return;
        ll K = __lg(n) + 1;
        st.assign(K, vector<ll>(n));
        st[0] = vec;
        for (ll j = 0; (2 << j) <= n; j++) {
            for (ll i = 0; i + (2 << j) <= n; i++) {
                st[j + 1][i] = op(st[j][i], st[j][i + (1 << j)]);
            }
        }
    }
    ll query(ll l, ll r) {
        if (l >= r) return -1;
        ll j = __lg(r - l);
        return op(st[j][l], st[j][r - (1 << j)]);
    }
};

bool check(vector<ll> &a, SparseTable &sparse, vector<ll> pos0[30], ll mask) {
    ll n = SZ(a);
    //we'll try to swap one element such that
    //(L|R) is a super set of the mask = mask


    //is there any element that is a superset of mask? if there is, we can 
    //make it L or R by swap
    for (ll i = 0; i < n; i++) if ((a[i] & mask) == mask) return true;


    for (ll i = 0; i < 30; i++) {    
        //if mask bit is not on or all elements have that bit,
        //then we can ignore
        if (!Check(mask,i) || pos0[i].empty()) continue;

        //till swap_left-1, all elements have ith bit set
        ll swap_left = pos0[i][0];

        //making a partition on [0,swap_left-1] , [swap_left,n-1]
        //is L|R a superset of mask?
        if (swap_left > 0 && ((sparse.query(0, swap_left) | sparse.query(swap_left, n)) & mask) == mask) return true;
        
        
        for (ll j = 0; j < 30; j++) {
            //let's find another bit such that from 0 to k-1,
            //all elements j-th bit is set and k>swap_left
            ll k;
            
            if (i == j) {
                if (SZ(pos0[i]) < 2) continue;
                k = pos0[i][1];
            } else {
                if (!Check(mask,j) || pos0[j].empty()) continue;
                k = pos0[j][0];
                
            }

            if (k <= swap_left) continue; 
            //does not follow our assumption


            //we will swap a[swap_left] to another right subarray

            ll L = (sparse.query(0, swap_left) & 
            sparse.query(swap_left + 1, k) & mask);
            //now we have L's submask...we need complementary R such that
            //(L|R) is mask so,
            ll R = mask ^ L;
            if ((a[swap_left] & R) != R) continue;

            //now let's find if all elements in the right array
            // can actually create the and value R or R's superset
            //and if there is an element that we can swap with swap_left

            //find the most 2 rightmost elements that violate right_contrib
            ll viol1 = -1, viol2 = -1;
            for (ll l = 0; l < 30; l++) {
                if (!Check(R,l)) continue;
                if (!pos0[l].empty()) {

                    ll last = pos0[l].back();
                    if (last > viol1) { viol2 = viol1; viol1 = last; }
                    else if (last < viol1 && last > viol2) { viol2 = last; }
                }
                if (SZ(pos0[l]) >= 2) {
                    ll second_last = pos0[l][SZ(pos0[l]) - 2];
                    if (second_last > viol1) { viol2 = viol1; viol1 = second_last; }
                    else if (second_last < viol1 && second_last > viol2) { viol2 = second_last; }
                }
            }
            if (viol1 < k) {
                //none of right most elements violate R,
                // we swap k and swap_left
                if (k != swap_left + 1) return true;
            } else if (viol2 < k) {
                //swap swap_left and viol1
                if ((a[viol1] & L) == L) return true;
            }

            for (ll l = 0; l < 30; l++) {
                if (SZ(pos0[l]) != 1) continue;
                ll x = pos0[l][0];
                //can we swap x with swap_left?
                if (x < k) continue;
                if ((((sparse.query(0, swap_left) & a[x] & sparse.query(swap_left+1, k)) | (sparse.query(k, x) & a[swap_left] & sparse.query(x+1, n))) & mask) == mask) return true;
            }
        }
    }
    return false;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;
    vector<ll> arev = a;
    reverse(all(arev));
    SparseTable sparse;
    sparse.init(a);
    SparseTable rsparse;
    rsparse.init(arev);
    vector<ll> pos0[30], pos0r[30];
    for (ll i = 0; i < 30; i++) {
        for (ll j = 0; j < n; j++) if (!((a[j] >> i) & 1)) pos0[i].push_back(j);
        for (ll j = 0; j < n; j++) if (!((arev[j] >> i) & 1)) pos0r[i].push_back(j);
    }
    ll ans = 0;
    ll total_and = sparse.query(0, n);
    for (ll bit = 29; bit >= 0; --bit) {
        // if ((total_and >> bit) & 1) continue;
        ll current_mask = ans | (1 << bit);
        if (check(a, sparse, pos0, current_mask) || check(arev, rsparse, pos0r, current_mask)) {
            ans |= (1 << bit);
        }
    }
    cout << ans + total_and << nn;
}

int main() {
    fast;
    ll t;
    t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
