#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9 + 5;
 
long long max_weights(int n, int m, vector<int> x, vector<int> y,
                      vector<int> w) { 
    vector<vector<pair<int,int>>> g(n + 2, vector<pair<int,int>>(1, {0,0}));
    vector<vector<int>> pts(n + 2, vector<int>(1, 0));
    for(int i = 0; i < m; i++){
        g[x[i] + 1].emplace_back(y[i] + 1, w[i]);
        if(x[i] != 0) pts[x[i]].push_back(y[i] + 1);
        pts[x[i] + 2].push_back(y[i] + 1);
    }
    for(int i = 0; i <= n + 1; i++){
        sort(g[i].begin(), g[i].end());
        sort(pts[i].begin(), pts[i].end());
        pts[i].resize(unique(pts[i].begin(), pts[i].end()) - pts[i].begin());
    }
    for(int i = 1; i <= n; i++){
        if(pts[i].back() != n){
            pts[i].push_back(n);
        }
    }
    vector<vector<ll>> sums(n + 2);
    for(int i = 0; i <= n + 1; i++){
        for(auto [j, x]: g[i]){
            sums[i].push_back(x + (sums[i].empty() ? 0 : sums[i].back()));
        }
    }
    vector<vector<ll>> dpl(n + 1);
    vector<vector<ll>> dpr(n + 1);
    vector<vector<ll>> dpr2(n + 1);
    vector<vector<ll>> ans(n + 1);
    dpl[0].push_back(0);
    dpr[0].push_back(0);
    dpr2[0].push_back(0);
    ll fans = 0;
    ll pre = 0;
    for(int col = 1; col <= n; col++){
        for(int row: pts[col]){
 
            if(col >= 3){
                pre = max(dpr[col - 3].front(), pre);
                pre = max(dpl[col - 3].back(), pre);
            }
 
            auto it = prev(upper_bound(g[col].begin(), g[col].end(), make_pair(row, INF)));
            ll sumUp = sums[col].back() - sums[col][it - g[col].begin()];
            it = prev(upper_bound(g[col - 1].begin(), g[col - 1].end(), make_pair(row, INF)));
            ll removeLeft = sums[col - 1].back() - sums[col - 1][it - g[col - 1].begin()];
 
            auto it2 = prev(upper_bound(pts[col - 1].begin(), pts[col - 1].end(), row));
 
            // left to left
            if(row == 0){
                dpl[col].push_back(dpl[col - 1][it2 - pts[col - 1].begin()] + sumUp - removeLeft);
            }else{
                dpl[col].push_back(max(dpl[col].back(), dpl[col - 1][it2 - pts[col - 1].begin()] + sumUp - removeLeft));
            }
 
            //left to right
            it = prev(upper_bound(g[col + 1].begin(), g[col + 1].end(), make_pair(row, INF)));
            ll rsum = sums[col + 1][it - g[col + 1].begin()];
            dpr[col].push_back(dpl[col - 1][it2 - pts[col - 1].begin()] - removeLeft + rsum);
 
            // right to right
            it = prev(upper_bound(g[col].begin(), g[col].end(), make_pair(row, INF)));
            it2 = lower_bound(pts[col - 1].begin(), pts[col - 1].end(), row);
 
            ll ss = 0;

            if(it2 != pts[col - 1].end()){
                ss = dpr[col - 1][it2 - pts[col - 1].begin()] - sums[col][it - g[col].begin()];
                dpr[col].back() = max(dpr[col].back(), dpr[col - 1][it2 - pts[col - 1].begin()] + rsum - sums[col][it - g[col].begin()]);
            }
 
            if(row == 0) dpr2[col].push_back(dpr[col].back() - rsum);
            else dpr2[col].push_back(max(dpr2[col].back(), ss));
 
            if(col >= 2){
                // lower prev higher now 
                it2 = prev(upper_bound(pts[col - 2].begin(), pts[col - 2].end(), row));
 
                dpl[col].back() = max(dpl[col].back(), dpr2[col - 2][it2 - pts[col - 2].begin()] + sumUp + sums[col - 1].back() - removeLeft);
 
                it2 = lower_bound(pts[col - 2].begin(), pts[col - 2].end(), row);
                if(it2 != pts[col - 2].end()){
                    dpr[col].back() = max(dpr[col].back(), dpr[col - 2][it2 - pts[col - 2].begin()] + rsum);
                }
            }
 
            dpl[col].back() = max(dpl[col].back(), pre + sumUp + sums[col - 1].back() - removeLeft);
            dpr[col].back() = max(dpr[col].back(), pre + sums[col - 1].back() - removeLeft + rsum);
            fans = max(fans, dpr[col].back());
        }
        for(int i = (int) dpr[col].size() - 2; i >= 0; i--){
            dpr[col][i] = max(dpr[col][i], dpr[col][i + 1]);
        }
    }
    return fans;
}