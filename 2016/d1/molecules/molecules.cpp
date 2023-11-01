#include <bits/stdc++.h>
using namespace std;

std::vector<int> find_subset(int l, int u, std::vector<int> w){
    vector<pair<int,int>> a;
    for(int i = 0; i < w.size(); i++){
        a.emplace_back(w[i], i);
    }
    sort(a.begin(), a.end());
    while(a.size() && a.back().first > u) a.pop_back();
    int sum = 0;
    reverse(a.begin(), a.end());
    vector<int> ans;
    for(int i = 0; i <= a.size(); i++){
        int j = a.size() - 1;
        int ts = sum;
        vector<int> tmp;
        while(i <= j && ts < l){
            ts += a[j].first;
            tmp.push_back(a[j].second);
            j--;
        }
        if(l <= ts && ts <= u){
            for(int x: tmp){
                ans.push_back(x);
            }
            return ans;
        }
        if(i < a.size()){
            sum += a[i].first;
            ans.push_back(a[i].second);
        }
    }
    return {};
}


