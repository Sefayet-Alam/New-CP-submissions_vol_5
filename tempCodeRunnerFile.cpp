#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;



// CONSTANTS
#define md 10000007
#define PI acos(-1)
const double EPS = 1e-9;



string func(int pos){
    cout<<"Q "<<pos<<endl;

    string ret;
    cin>>ret;
    return ret;
}

void bs(int low,int high){
    int mid;
    int ans=0;
    while(low<=high){
        mid=low+(high-low)/2;
        //cout<<mid<<" "<<func(mid)<<endl;
        auto k=func(mid);
        if(k=="<"){
            low=mid+1;
        }
        else if(k==">"){
            high=mid-1;
        }
        else{
            ans=mid;
        }
    }

}

int main()
{
    int l=1,r=100;
    bs(l,r);

    return 0;
}


