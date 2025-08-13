#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


const int MAXN = 200005;


long long N, K;
long long A[MAXN], B[MAXN];

struct Node {
    
    long long ans[2];
    
    int end_state[2]; 
};


Node tree[4 * MAXN];


Node merge(const Node& left, const Node& right) {
    Node res;

    res.ans[0] = left.ans[0] + right.ans[left.end_state[0]];
    res.end_state[0] = right.end_state[left.end_state[0]];

    res.ans[1] = left.ans[1] + right.ans[left.end_state[1]];
    res.end_state[1] = right.end_state[left.end_state[1]];
    
    return res;
}


void build(int node, int start, int end) {

    if (start == end) {
        int i = start;
        

        bool swap_decision0 = (A[i] + K < B[i]);
        tree[node].ans[0] = swap_decision0 ? B[i] : A[i];
        tree[node].end_state[0] = swap_decision0; // 0 ^ swap_decision0


        bool swap_decision1 = (B[i] + K < A[i]);
        tree[node].ans[1] = swap_decision1 ? A[i] : B[i];
        tree[node].end_state[1] = 1 ^ swap_decision1;
        return;
    }
    

    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx) {
    // Base case: reached the leaf for the updated index.
    if (start == end) {
        int i = start;
        // Recalculate the leaf's values.
        bool swap_decision0 = (A[i] + K < B[i]);
        tree[node].ans[0] = swap_decision0 ? B[i] : A[i];
        tree[node].end_state[0] = swap_decision0;

        bool swap_decision1 = (B[i] + K < A[i]);
        tree[node].ans[1] = swap_decision1 ? A[i] : B[i];
        tree[node].end_state[1] = 1 ^ swap_decision1;
        return;
    }
    

    int mid = start + (end - start) / 2;
    if (start <= idx && idx <= mid) {
        update(2 * node, start, mid, idx);
    } else {
        update(2 * node + 1, mid + 1, end, idx);
    }

    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}


void solve() {
    cin >> N >> K;

    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> B[i];

    build(1, 1, N);

    int Q;
    cin >> Q;
    while (Q--) {
        int type, p;
        long long x;
        cin >> type >> p >> x;
        
        if (type == 1) {
            A[p] = x;
        } else {
            B[p] = x;
        }
        
        update(1, 1, N, p);
        
        cout << tree[1].ans[0] << "\n";
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}