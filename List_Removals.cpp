#include <bits/stdc++.h>
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
#define ll long long
using namespace std;
#define left(i) (2 * i + 1)
#define right(i) (2 * i + 2)
#define parent(i) ((i - 1) / 2)
#include <vector>

template <class T>
class SegmentTree
{
public:
    SegmentTree(std::vector<T> data, T value, T (*combine)(T obj1, T obj2));
    SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));
    T query(int l, int r);
    void update(int idx, T val);
    // TODO lazy propagation
private:
    T *tree;
    void buildTree(std::vector<T> data);
    int segTreeSize;
    T valueForExtraNodes;
    T (*combine)(T obj1, T obj2);
    int calculateSize(int n);
    T queryHelper(int l, int r, int st, int ed, int node);
};

template <class T>
SegmentTree<T>::SegmentTree(std::vector<T> data,
                            T value, T (*combine)(T obj1, T obj2))
{
    this->combine = combine;
    valueForExtraNodes = value;
    segTreeSize = calculateSize(data.size());
    buildTree(data);
}

template <class T>
SegmentTree<T>::SegmentTree(T ar[], int n,
                            T value, T (*combine)(T obj1, T obj2))
{
    this->combine = combine;
    valueForExtraNodes = value;
    segTreeSize = calculateSize(n);

    std::vector<T> data;
    for (int i = 0; i < n; i++)
        data.push_back(ar[i]);

    buildTree(data);
}

template <class T>
int SegmentTree<T>::calculateSize(int n)
{
    int pow2 = 1;
    while (pow2 < n)
    {
        pow2 = pow2 << 1;
    }
    return 2 * pow2 - 1;
}

template <class T>
T SegmentTree<T>::query(int l, int r)
{
    int st = 0, ed = segTreeSize / 2;
    return queryHelper(l, r, st, ed, 0);
}

template <class T>
T SegmentTree<T>::queryHelper(int l, int r, int st, int ed, int node)
{
    if ((r < st) || (l > ed) || (l > r))
        return valueForExtraNodes;
    if (st >= l && ed <= r)
        return tree[node];
    T leftVal = queryHelper(l, r, st, (st + ed) / 2, left(node));
    T rightVal = queryHelper(l, r, (st + ed) / 2 + 1, ed, right(node));
    return combine(leftVal, rightVal);
}

template <class T>
void SegmentTree<T>::buildTree(std::vector<T> data)
{
    int n = data.size();
    tree = new T[segTreeSize];
    int extraNodes = (segTreeSize / 2 + 1) - n;
    for (int i = segTreeSize - 1; i >= 0; i--)
    {
        if (extraNodes > 0)
        {
            tree[i] = valueForExtraNodes;
            extraNodes--;
        }
        else if (n > 0)
        {
            tree[i] = data[n - 1];
            n--;
        }
        else
            tree[i] = combine(tree[left(i)], tree[right(i)]);
    }
}

template <class T>
void SegmentTree<T>::update(int idx, T val)
{
    int segTreeIdx = (segTreeSize / 2) + idx;
    tree[segTreeIdx] = val;
    while (parent(segTreeIdx) >= 0)
    {
        segTreeIdx = parent(segTreeIdx);
        if (right(segTreeIdx) < segTreeSize)
            tree[segTreeIdx] = combine(tree[left(segTreeIdx)], tree[right(segTreeIdx)]);
        if (segTreeIdx == 0)
            break;
    }
}

int sum(int x, int y) { return x + y; }
int main()
{
    fast_io;
    int n;
    cin >> n;

    vector<int> v(n);
    vector<int> present(n, 1);

    for (int i = 0; i < n; i++)
        cin >> v[i];

    SegmentTree<int> rangeSumQueries(present, 0, sum);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        int lo = 0, hi = n - 1;
        while (lo != hi)
        {
            int mid = (lo + hi) / 2;
            int till_mid = rangeSumQueries.query(0, mid);
            if (till_mid > x)
                hi = mid - 1;
            else if (till_mid < x)
                lo = mid + 1;
            else
            {
                if (present[mid])
                {
                    lo = mid;
                    break;
                }
                else
                    hi = mid - 1;
            }
        }
        present[lo] = 0;
        rangeSumQueries.update(lo, 0);
        cout << v[lo] << ' ';
    }
    return 0;
}
