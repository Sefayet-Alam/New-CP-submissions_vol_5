#include <bits/stdc++.h>
using namespace std;

#define FAST                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
using ll = long long;

int main()
{
    FAST;

    int tc = 1, ti;
    cin >> tc;

    for (ti = 1; ti <= tc; ++ti)
    {
        int n, i, j, l, r, len, ans;
        cin >> n;

        vector<int> a(n);
        for (i = 0; i < n; ++i)
            cin >> a[i];

        ans = n * (n + 1) / 2;
        for (l = 0; l < n; ++l)
            for (r = l; r < n; ++r)
            {
                len = r - l + 1;
                if (len & 1)
                    continue;
                if (len == 2)
                    continue;

                bool f;

                f = 0;
                i = l;
                j = r;
                while (i < j)
                {
                    if (a[i] == a[j])
                        f = 1;
                    ++i;
                    --j;
                }
                if (f)
                    continue;

                f = 0;
                for (i = l + 1; i <= r; ++i)
                {
                    if (a[i] == a[i - 1])
                    {
                        if ((i == l + 1) || (i == l + 2) || (i == l + len / 2 - 1))
                            f = 1;
                    }
                }
                if (!f)
                    ans -= 1;
            }

        cout << ans << "\n";
    }

    return 0;
}