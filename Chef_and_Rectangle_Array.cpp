#include <bits/stdc++.h>
using namespace std;
int arr[1005][1005], rmq[1005][1005][105];
int aux[1005][1005], arr2[1005];

int main()
{
    int n, m, i, j;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    for (i = 0; i < m; i++)
        aux[0][i] = arr[0][i];
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            aux[i][j] = aux[i - 1][j] + arr[i][j];
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            aux[i][j] += aux[i][j - 1];
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            rmq[i][j][0] = arr[i][j];
        }
        for (j = 1; (1 << j) <= m; j++)
        {
            for (int k = 0; k + (1 << j) - 1 < m; k++)
            {
                rmq[i][k][j] = max(rmq[i][k][j - 1], rmq[i][k + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int q, k, l;
    int maxn;
    scanf("%d", &q);
    while (q--)
    {
        int a, b, ans = 1e9;
        scanf("%d %d", &a, &b);
        int xx = log2(b);
        for (j = 0; j <= (m - b); j++)
        {
            for (i = 0; i < n; i++)
            {
                // arr2[i]=query(1,0,m-1,j,j+b-1,i);
                arr2[i] = max(rmq[i][j][xx], rmq[i][j + b - 1 - (1 << xx) + 1][xx]);
            }
            deque<int> d(a);
            for (i = 0; i < a; i++)
            {
                while (!d.empty() && arr2[i] >= arr2[d.back()])
                    d.pop_back();
                d.push_back(i);
            }
            // cout<<arr2[d.front()]<<" ";
            arr2[0] = arr2[d.front()];
            for (; i < n; i++)
            {
                while (!d.empty() && d.front() < (i - a + 1))
                    d.pop_front();
                while (!d.empty() && arr2[i] >= arr2[d.back()])
                    d.pop_back();
                d.push_back(i);
                arr2[i - a + 1] = arr2[d.front()];
                // cout<<arr2[d.front()]<<" ";
            }
            // cout<<endl;
            int sum;

            for (i = 0; i <= (n - a); i++)
            {

                //	for(j=0;j<=(m-b);j++)
                //{
                if (i <= (n - a))
                {
                    sum = 0;
                    sum += aux[i + a - 1][j + b - 1];
                    if (j > 0)
                        sum -= aux[i + a - 1][j - 1];
                    if (i > 0)
                        sum -= aux[i - 1][j + b - 1];
                    if (j > 0 && i > 0)
                        sum += aux[i - 1][j - 1];
                }
                int k;
                maxn = arr2[i];
                // cout<<maxn<<" ";
                ans = min(maxn * a * b - sum, ans);
                //}
            }
            ans = min(maxn * a * b - sum, ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}