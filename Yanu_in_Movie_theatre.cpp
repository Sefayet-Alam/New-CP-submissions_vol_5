#include <bits/stdc++.h>
using namespace std;
#define Setpre(n) cout << fixed << setprecision(n)
int main()
{
    int a,b;
    while (cin>>a>>b)
    {
      if(a==0 && b==0) break;
      if(a==0) Setpre(6)<<1.000000;
      else if(a>b) Setpre(6)<<0.0000000;
      else{
        long double ans=(a*1.00-b+1.00)/(a*1.00+1.00);
        Setpre(6)<<ans;
      }
      cout<<endl;
    }

    return 0;
}