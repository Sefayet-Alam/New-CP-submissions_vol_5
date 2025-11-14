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
using namespace io;

/* Points tO CONSIDER
    # RTE? -> check array bounds and constraints
    -> check if u are dividing smth by 0
    #TLE? -> thinks about binary search/ dp / optimization techniques
    # WA?
    -> overflow,reset global variables
    -> Check corner cases
    -> use Setpre for precision problems

    #Can't Get an idea?
    -> think from different/simpler approaches
    -> Think in reverse?
    -> Read the problem statement again
    -> Check the constraints again
    -> Ignore unnecessary information, and use it to draw the problem in new ways.
    -> Characterize the problem: Suppose I did find such a solution, what would it look like? what characteristics it would have? Can we toy around with such a solution so that it remains optimal?
    -> Randomly guessing: Guess and try to prove false
    -> Finding invariants: Check which properties don't change
    -> Solving subtasks of the original problem and then trying to extend/generalize your solution.
    -> bruteforce to find pattern
    -> Making obvious lower and upper bounds, and proving they are constructible.
    -> Fixing a parameter and then trying to maximise the result with respect to that fixed parameter.
    -> Maybe take a deep breath and take a break
    -> STRESS TESTING !!!!!!
*/

// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;


struct Node {
    unordered_map<unsigned char, Node*> next;
    bool isWord = false;
    int cnt = 0; 
    // number of words passing through this node (prefix count)
};

struct Trie {
    Node* root = new Node();

    // insert string
    void insert(const string &s) {
        Node* cur = root;
        for (unsigned char c : s) {
            if (!cur->next.count(c)) cur->next[c] = new Node();
            cur = cur->next[c];
            cur->cnt++;
        }
        cur->isWord = true;
    }

    // search string
    bool search(const string &s) {
        Node* cur = root;
        for (unsigned char c : s) {
            if (!cur->next.count(c)) return false;
            cur = cur->next[c];
        }
        return cur->isWord;
    }

    // erase string
    bool erase(const string &s) {
        return eraseHelper(root, s, 0);
    }

    // count how many strings start with prefix p
    int startsWith(const string &p) {
        Node* cur = root;
        for (unsigned char c : p) {
            if (!cur->next.count(c)) return 0;
            cur = cur->next[c];
        }
        return cur->cnt + (cur->isWord ? 1 : 0);
    }

    // erase all strings that have prefix p
    void erasePrefix(const string &p) {
        Node* cur = root;
        vector<Node*> path;
        for (unsigned char c : p) {
            if (!cur->next.count(c)) return;
            path.push_back(cur);
            cur = cur->next[c];
        }
        int removed = cur->cnt + (cur->isWord ? 1 : 0);
        freeSubtree(cur);
        unsigned char last = p.back();
        path.back()->next.erase(last);
        for (Node* node : path) node->cnt -= removed;
    }

    // return length of longest prefix of s that exists in Trie
    int longestPrefix(const string &s) {
        Node* cur = root;
        int len = 0, best = 0;
        for (unsigned char c : s) {
            if (!cur->next.count(c)) break;
            cur = cur->next[c];
            len++;
            if (cur->isWord) best = len;
        }
        return best;
    }

    // return lexicographically smallest word in Trie
    string smallestWord() {
        return dfsLex(root, true);
    }

    // return lexicographically largest word in Trie
    string largestWord() {
        return dfsLex(root, false);
    }

    // free entire trie
    void clear() {
        freeSubtree(root);
        root = new Node();
    }

private:
    void freeSubtree(Node* node) {
        if (!node) return;
        for (auto &p : node->next)
            freeSubtree(p.second);
        delete node;
    }

    bool eraseHelper(Node* cur, const string &s, int i) {
        if (!cur) return false;
        if (i == (int)s.size()) {
            if (!cur->isWord) return false;
            cur->isWord = false;
            return true;
        }
        unsigned char c = s[i];
        if (!cur->next.count(c)) return false;
        bool erased = eraseHelper(cur->next[c], s, i + 1);
        if (erased) {
            cur->next[c]->cnt--;
            if (cur->next[c]->cnt == 0 && !cur->next[c]->isWord) {
                delete cur->next[c];
                cur->next.erase(c);
            }
        }
        return erased;
    }

    string dfsLex(Node* node, bool smallest, string prefix = "") {
        if (!node) return "";
        if (node->isWord && node->next.empty()) return prefix;
        if (node->isWord) return prefix; // return first found word
        vector<unsigned char> keys;
        for (auto &p : node->next) keys.push_back(p.first);
        if (smallest) sort(keys.begin(), keys.end());
        else sort(keys.rbegin(), keys.rend());
        for (unsigned char c : keys) {
            string res = dfsLex(node->next[c], smallest, prefix + (char)c);
            if (!res.empty()) return res;
        }
        return "";
    }
};

int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;
    ll n;
    cin >> n;
    Trie tr1, tr2;
    vector<string> vec;
    for (ll i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        tr1.insert(s);
        vec.push_back(s);
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++)
    {
        tr1.erase(vec[i]);
        string now = "";
        string p = vec[i];
        bool f = 0;
        for (ll j = 0; j < p.size(); j++)
        {
            now += p[j];
            if (tr2.startsWith(now) && !tr1.startsWith(now))
            {
                f = 1;
                ans-=tr2.startsWith(now);
                tr2.erasePrefix(now);
                tr2.insert(now);
                ans++;
                break;
            }
        }
        if (!f)
        {
            tr2.insert(now);
            ans++;
        }
        cout << ans << nn;
    }

    return 0;
}
