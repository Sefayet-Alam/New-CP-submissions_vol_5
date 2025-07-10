#include <bits/stdc++.h>
using namespace std;
const int sz = 20;

struct node {
    node* c[10];
    int cnt;
    node () {
        cnt = 0;
        for(int i = 0; i < 10; i++) c[i] = NULL;
    }
} *root;
int p[10];

void insert(string s) {
    node* cur = root;
    for(auto i : s) {
        i -= '0';
        if(cur -> c[i] == NULL) cur -> c[i] = new node();
        cur = cur -> c[i];
        cur -> cnt += 1;
    }
}

int solve(string s) {
    node* cur = root;
    int ans = 0;
    for(auto i : s) {
        i -= '0';
        for(int j = 0; j < 10; j++) {
            if(p[j] < p[i] && cur -> c[j]) {
                ans += cur -> c[j] -> cnt;
            }
        }
        if(cur -> c[i]) cur = cur -> c[i];
        else break;
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    root = new node();
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        while(s.size() < sz) s = "0" + s;
        insert(s);
    }
    int q;
    cin >> q;
    while(q--) {
        string s;
        for(int i = 0; i < 10; i++) {
            int x;
            cin >> x;
            p[x] = i;
        }
        cin >> s;
        while(s.size() < sz) s = "0" + s;
        cout << solve(s) << endl;
    }
}

