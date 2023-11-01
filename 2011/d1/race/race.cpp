#include <bits/stdc++.h>
#include "race.h"
using namespace std;
const int MX = 1e6;
vector<vector<pair<int,int>>> g;
vector<int> sz, dead;

int dfs_sz(int v, int p){
    sz[v] = 1;
    for(auto [u, w]: g[v]) if(u != p && !dead[u]){
        sz[v] += dfs_sz(u, v);
    }
    return sz[v];
}

int cent(int v, int p, int n){
    for(auto [u, w]: g[v]) if(u != p && !dead[u] && sz[u] > n / 2){
        return cent(u, v, n);
    }
    return v;
}

void dfs(int v, int p, int ws, vector<pair<int,int>> &ps, int ln){
    if(ws > MX) return;
    ps.emplace_back(ws, ln);
    for(auto [u, w]: g[v]) if(u != p && !dead[u]){
        dfs(u, v, ws + w, ps, ln + 1);
    }
}

int dc(int v, int k){
    int n = dfs_sz(v, -1);
    int c = cent(v, -1, n);
    dead[c] = 1;
    vector<vector<pair<int,int>>> ps;
    for(auto [u, w]: g[c]) if(!dead[u]){
        ps.emplace_back();
        dfs(u, c, w, ps.back(), 1);
    }
    int ans = 1e9;
    map<int,int> mins;
    mins[0] = 0;
    for(auto chld: ps){
        for(auto [x, ln]: chld){
            if(k - x >= 0){
                if(mins.find(k - x) != mins.end()) ans = min(ans, mins[k - x] + ln);
            }
        }
        for(auto [x, ln]: chld){
            if(mins.find(x) != mins.end()) mins[x] = min(mins[x], ln);
            else mins[x] = ln;
        }
    }
    for(auto [u, w]: g[c]) if(!dead[u]){
        ans = min(ans, dc(u, k));
    }
    return ans;
}

int best_path(int n, int k, int h[][2], int l[]){
    g.resize(n);
    sz.resize(n);
    dead.resize(n);
    for(int i = 0; i < n - 1; i++){
        g[h[i][0]].emplace_back(h[i][1], l[i]);
        g[h[i][1]].emplace_back(h[i][0], l[i]);
    }    
    int ans = dc(0, k);
    if(ans >= 1e9) ans = -1;
    return ans;
}

