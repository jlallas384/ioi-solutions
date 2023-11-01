#include <bits/stdc++.h>
using namespace std;

struct ufds{
    vector<int> sz, par;
    ufds(){}
    ufds(int n): sz(n, 1), par(n){
        iota(par.begin(), par.end(), 0);
    }
    int find(int a){
        return par[a] == a ? a : par[a] = find(par[a]);
    }
    int unite(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return 0;
        if(sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        return 1;
    }
};
 
set<int> ans;
vector<vector<int>> g, tree;
vector<int> deg;
int n = 0;
ufds ds;
 
int bad = 0;
int d4 = 0;
 
void Init(int N){
    assert(n == 0);
    n = N;
    g.resize(n);
    tree.resize(n);
    deg.resize(n);
    for(int i = 0; i < n; i++){
        ans.insert(i);
    }
    ds = ufds(n);
}
 
void proc(int a, int add = 1){
    if(deg[a] >= 4){
        if(add){
            if(deg[a] == 4) d4++;
            if(d4 == 2) ans = {};
        }
        if(!ans.count(a)) ans = {};
        else ans = {a};
    }else if(deg[a] == 3){
        set<int> nans;
        if(ans.count(a)) nans.insert(a);
        for(int u: g[a]){
            if(ans.count(u)) nans.insert(u);
        }
        ans = nans;
    }
}
 
int CountCritical(){    
    return ans.size();
}

int cyc = 0;
 
vector<int> path;
int dfs(int v, int p, int x){
    path.push_back(v);
    if(v == x) return 1;
    for(int u: tree[v]) if(u != p){
        if(dfs(u, v, x)) return 1;
    }
    path.pop_back();
    return 0;
}
 
vector<pair<int,int>> eds;
map<int, ufds> mp;
 
void Link(int a, int b){
    int res = ds.unite(a, b);
    deg[a]++, deg[b]++;
    g[a].push_back(b);
    g[b].push_back(a);
    eds.emplace_back(a, b);
    proc(a), proc(b);
    if(cyc == 2){
        set<int> nans;
        for(int x: ans){
            int tbad = 0;
            if(a != x && b != x && !mp[x].unite(a, b)){
                tbad = 1;
            }
            if(!tbad) nans.insert(x);
        }
        ans = nans;
    }
    if(!res){
        if(!cyc){
            dfs(a, -1, b);
            ans = {};
            for(int x: path){
                ans.insert(x);
            }
            for(int i = 0; i < n; i++){
                proc(i, 0);
            }
            cyc = 1;
        }else{
            if(cyc == 1){
                set<int> nans;
                for(int x: ans) if(deg[x] >= 3){
                    ufds f(n);
                    int tbad = 0;
                    for(auto [u, v]: eds){
                        if(u != x && v != x){
                            if(!f.unite(u, v)) tbad = 1;
                        }
                    }
                    if(!tbad) nans.insert(x), mp[x] = f;;
                }
                ans = nans;
            }
            cyc = 2;
        }
    }else{
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
}