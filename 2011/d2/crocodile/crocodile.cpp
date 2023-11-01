#include <bits/stdc++.h>
#include "crocodile.h"
using namespace std;
using ll = long long;

int change(vector<pair<ll,int>> o, vector<pair<ll,int>> n){
    return o != n;
}

int travel_plan(int n, int m, int r[][2], int L[], int k, int p[]){
    vector<int> lst(n);
    priority_queue<pair<ll,int>> pq;
    vector<vector<pair<ll,int>>> dist(n);
    for(int i = 0; i < k; i++){
        pq.emplace(0, p[i]);
        lst[p[i]] = 1;
        dist[p[i]].emplace_back(0, p[i]);
        dist[p[i]].emplace_back(0, p[i]);
    }
    vector<vector<pair<int,int>>> g(n);
    for(int i = 0; i < m; i++){
        g[r[i][0]].emplace_back(r[i][1], L[i]);
        g[r[i][1]].emplace_back(r[i][0], L[i]);
    }
    ll ans = 1e18;
    while(pq.size()){
        auto [d, v] = pq.top(); pq.pop();
        if(-d > dist[v].back().first) continue;
        if(v == 0) return dist[v].back().first;
        for(auto [u, w]: g[v]){
            if(dist[u].empty()){
                dist[u].emplace_back(-d + w, v);
            }else{
                int has = 0;
                vector<pair<ll,int>> o = dist[u];
                for(auto &[pd, pv]: dist[u]) if(pv == v){
                    has = 1;
                    if(pd > -d + w){
                        pd = -d + w;
                        sort(dist[u].begin(), dist[u].end());
                        if(dist[u].size() == 2){
                            if(change(o, dist[u])) pq.emplace(-dist[u].back().first, u);
                        }
                    }
                }
                if(!has){
                    dist[u].emplace_back(-d + w, v);
                    sort(dist[u].begin(), dist[u].end());
                    if(dist[u].size() == 3) dist[u].pop_back();
                    if(dist[u].size() == 2){
                        if(change(o, dist[u])) pq.emplace(-dist[u].back().first, u);
                    }
                }
            }
        }
    }
    return ans;
}





