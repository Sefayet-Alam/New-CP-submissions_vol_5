#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#define pll pair<ll,ll>
#define vl vector<ll>
#define vpll vector<pll>
#define all(x) x.begin(), x.end()

template <typename T>
using PQ = priority_queue<T>;
template <typename T>
using QP = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    fast;
    ll t; cin >> t;
    while(t--){
        ll n,m,k; cin >> n >> m >> k;

        vector<vector<pair<pll,int>>> tadj(n); // {{length, neighbor}, company}
        vector<unordered_map<ll,vpll>> adj(m); // per company: u -> {{v,length}}

        for(ll i=0;i<m;i++){
            ll u,v,c,l; cin >> u >> v >> c >> l;
            u--; v--; c--;
            tadj[u].push_back({{l,v},c});
            tadj[v].push_back({{l,u},c});
            adj[c][u].push_back({v,l});
            adj[c][v].push_back({u,l});
        }

        vector<QP<pair<ll,pll>>> pq(m); // company PQ //dist,{from,destination}
        vl reachable(n,0); reachable[0]=1;

        for(auto &p: tadj[0])
            pq[p.second].push({p.first.first,{0,p.first.second}});

        for(ll ticket=0; ticket<k; ticket++){
            ll a,b; 
            cin >> a >> b; 
            a--;
            set<ll> st; // newly reachable
            QP<pll> cpq;//{dist,node}

            while(!pq[a].empty() && pq[a].top().first <= b){
                auto p = pq[a].top(); pq[a].pop();
                if(reachable[p.second.second]) continue;
                cpq.push({p.first, p.second.second});
            }
            
            while(!cpq.empty()){
                auto p = cpq.top(); cpq.pop();
                ll d = p.first, u = p.second;
                if(reachable[u]) continue;
                reachable[u]=1;
                st.insert(u);

                for(auto &e: adj[a][u]){
                    ll v = e.first, w = e.second;
                    ll nd = d + w;
                    if(nd > b) continue;
                    cpq.push({nd,v});
                }
            }
            for(auto u: st){
                for(auto &v: tadj[u]){
                    if(!reachable[v.first.second])
                        pq[v.second].push({v.first.first,{u,v.first.second}});
                }
            }
        }

        for(ll i=0;i<n;i++) cout << reachable[i];
        cout << "\n";
    }
}



