#include <bits/stdc++.h>
#include "crocodile.h"
using namespace std;
using ll = long long;
int travel_plan(int n, int m, int r[][2], int L[], int k, int p[]){
    vector<vector<pair<int,int>>> g(n);
    for(int i = 0; i < m; i++){
        g[r[i][0]].emplace_back(r[i][1], L[i]);
        g[r[i][1]].emplace_back(r[i][0], L[i]);
    }
    vector<int> ext(n);
    for(int i = 0; i < k; i++){
        ext[p[i]] = 1;
    }
    vector<ll> dist(n + 1, 1e18);
    vector<int> par(n), dep(n);
    priority_queue<pair<ll,int>> pq;
    pq.emplace(0, 0);
    dist[0] = 0;
    vector<vector<pair<int,int>>> dag(n);
    while(pq.size()){
        auto [d,v] = pq.top(); pq.pop();
        if(ext[v]) continue;
        if(-d > dist[v]) continue;
        for(auto [u,w]: g[v]){
            if(dist[v] + w < dist[u]){
                dist[u] = dist[v] + w;
                pq.emplace(-dist[u], u);
                dep[u] = dep[v] + 1;
                par[u] = v;
            }
            if(dep[v] <= dep[u]){
                dag[v].emplace_back(u, w);
            }else{
                int d = dep[v] - dep[u];
                int f = v;
                while(d--){
                    f = par[f];
                }
                if(f != u){
                    dag[v].emplace_back(u, w);
                }
            }
        }
    }
    vector<ll> dp(n, -1);
    function<ll(int)> dfs = [&](int v){
        if(ext[v]) return 0LL;
        if(dp[v] != -1) return dp[v];
        vector<ll> dists;
        for(auto [u,w]: dag[v]){
            dists.push_back(dfs(u) + w);
        }
        if(dists.size() < 2) return (ll) 1e10;
        sort(dists.begin(), dists.end());
        return dp[v] = dists[1];
    };
    return dfs(0);
}