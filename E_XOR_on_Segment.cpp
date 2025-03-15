#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 7, B = 20;

class Node {
    public :
        int on [B] {}, off[B] {};

        Node () {}
        Node (int x) {
            for (int k = 0; k < B; k++) {
                ((x >> k) & 1) ? on[k]++ : off[k]++;
            }
        }
};


int arr[N], lazy[4 * N];
Node tree[4 * N];


void pull(int node){
    int left = 2 * node, right = 2 * node + 1;

    for (int k = 0; k < B; k++) {
        tree[node].on[k] = tree[left].on[k] + tree[right].on[k];
        tree[node].off[k] = tree[left].off[k] + tree[right].off[k];
    }
}
 
void build(int node,int b,int e){
    lazy[node] = 0;     // *** change this

    if(b == e){
        tree[node] = Node (arr[b]);
        return;
    }

    int left = 2 * node, right = 2 * node + 1;
    int mid = (b + e) / 2;
    build(left,b,mid);
    build(right,mid+1,e);

    pull(node);
}

void push(int node, int b, int e){     // *** change this
    if(lazy[node] == 0)
        return;
    
    int x = lazy[node];

    for (int k = 0; k < B; k++) {
        if ((x >> k) & 1) {
            swap(tree[node].on[k], tree[node].off[k]);
        }
    }

    if(b != e){
        int left = 2 * node, right = 2 * node + 1;
        lazy[left] = lazy[left] ^ lazy[node];
        lazy[right] = lazy[right] ^ lazy[node];
    }
 
    lazy[node] = 0;
}
 
Node combine(Node a, Node b){ // *** change this
    Node ans;

    for (int k = 0; k < B; k++) {
        ans.on[k] = a.on[k] + b.on[k];
        ans.off[k] = a.on[k] + b.on[k];
    }

return ans;
}
 
void update(int node,int b,int e,int l,int r,int x){
    push(node,b,e);
 
    if(b > r or e < l)
        return ;
    if(b >= l and e <= r){
        lazy[node] = x;     //***set lazy or value of propagation
        push(node,b,e);
    return;
    }
 
    int left = 2 * node, right = 2 * node + 1;
    int mid = (b + e) / 2;
    update(left,b,mid,l,r,x);
    update(right,mid+1,e,l,r,x);
 
    pull(node);
}
 
Node query(int node,int b,int e,int l,int r){
    push(node,b,e);
    if(b > r or e < l)
        return Node();		//***change this
    if(b >= l and e <= r)
        return tree[node];
 
    int left = 2 * node, right = 2 * node + 1;
    int mid = (b + e) / 2;
return combine(query(left,b,mid,l,r),query(right,mid+1,e,l,r));
}

void solve() {
    int n; cin >> n;

    for (int i = 1; i <= n; i++) cin >> arr[i];

    build (1, 1, n);

    int q; cin >> q;

    while (q--) {
        int ty; cin >> ty;

        if (ty == 1) {
            int l, r; cin >> l >> r;

            Node ans = query(1, 1, n, l, r);

            int sum = 0;

            for (int k = 0; k < B; k++) {
                sum += ans.on[k] * (1 << k);
            }

            cout << sum << "\n";

         } else {
            int l, r, x; cin >> l >> r >> x;

            update(1, 1, n, l, r, x);
        }
    }


}
 
int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    for(int i = 1; i <= t; i++){
        solve();
    }
    
    return 0;
}