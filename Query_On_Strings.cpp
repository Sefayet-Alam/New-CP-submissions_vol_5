#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long int
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void init() {
    #ifndef PRATHAMESH
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}

class TrieNode{
public:
    int freq = 0;
    TrieNode* links[26] = {NULL};
};
class Trie{
private:
    TrieNode* root;
public:
    Trie(){
        root = new TrieNode();
    }
    void add(string word, map<ll, multiset<ll> >&mp){
        TrieNode* node = root;
        ll level = 0;
        for(ll i = word.length() - 1; i >= 0; i --){
            if(node->links[word[i] - 'a'] == NULL){
                node->links[word[i] - 'a'] = new TrieNode();
            }
            node = node->links[word[i] - 'a'];
            node->freq ++;
            level ++;
            if(node->freq > 1){
                mp[level].erase(mp[level].find(node->freq - 1));
            }
            mp[level].insert(node->freq);
        }
    }
    void remove(string word, map<ll, multiset<ll> >&mp){
        TrieNode* node = root;
        ll level = 0;
        for(ll i = word.length() - 1; i >= 0; i --){
            node = node->links[word[i] - 'a'];
            level ++;
            mp[level].erase(mp[level].find(node->freq));
            node->freq --;
            mp[level].insert(node->freq);
        }
    }
};
void bol_bacchan() {
    ll q;
    cin >> q;
    map<ll, multiset<ll> >mp;
    map<ll, string>index;
    Trie trie;
    for(ll i = 1; i <= q; i ++){
        ll type ;
        cin >> type;
        if(type == 1){
            string word;
            cin >> word;
            trie.add(word, mp);
            index[i] = word;
        }
        else if(type == 2){
            ll k, len;
            cin >> k >> len;
            string ans = "NO";
            if(mp.find(len) != mp.end() && *(mp[len].rbegin()) >= k){
                ans = "YES";
            }
            cout << ans << endl;
        }
        else if(type == 3){
            ll ind ;
            cin >> ind;
            if(index.find(ind) != index.end()) {
                string word = index[ind];
                trie.remove(word, mp);
                index.erase(ind);
            }
        }
    }
}

int main() {
    fast
    bol_bacchan();
    // cout << 1 << endl;
}