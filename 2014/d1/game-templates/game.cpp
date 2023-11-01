#include <bits/stdc++.h>
#include "game.h"
using namespace std;

struct ufds{
    vector<int> sz, par;
    vector<vector<int>> cnt;
    ufds(){}
    ufds(int n): sz(n, 1), par(n), cnt(n, vector<int>(n, 1)){
        iota(par.begin(), par.end(), 0);
    }
    int find(int a){
        return par[a] == a ? a : par[a] = find(par[a]);
    }
    int unite(int a, int b){
        a = find(a), b = find(b);
        int n = cnt.size();
        if(sz[a] < sz[b]) swap(a, b);
        cnt[a][b]--;
        cnt[b][a]--;
        if(cnt[a][b] == 0){
            vector<int> used(n);
            for(int i = 0; i < n; i++){
                int z = find(i);
                if(z == a || z == b) continue;
                if(!used[z]){
                    int nw = cnt[z][a] + cnt[z][b];
                    cnt[z][a] = cnt[a][z] = nw;
                    used[z] = 1;
                }
            }
            sz[a] += sz[b];
            par[b] = a;
            return 1;
        }
        return 0;
    }
};

ufds ds;

void initialize(int n) {
    ds = ufds(n);
}

int hasEdge(int u, int v) {
    return ds.unite(u,v);
}
