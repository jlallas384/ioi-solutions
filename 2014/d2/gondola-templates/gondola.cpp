#include <bits/stdc++.h>
#include "gondola.h"
using namespace std;
using ll = long long;
const int mod = 1e9 + 9;
int valid(int n, int inputSeq[]){
    set<int> used;
    int idx = 0;
    for(int i = 0; i < n; i++){
        if(used.count(inputSeq[i])) return 0;
        used.insert(inputSeq[i]);
        if(inputSeq[i] <= n){
            idx = i;
        }
    }
    int nd = inputSeq[idx];
    for(int i = 0; i < n; i++){
        int j = (idx + i) % n;
        if(inputSeq[j] <= n && inputSeq[j] != nd) return 0;
        nd++;
        if(nd > n) nd = 1;
    }
    return 1;
}

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
    int idx = -1;
    for(int i = 0; i < n; i++){
        if(gondolaSeq[i] <= n){
            idx = i;
            break;
        }
    }
    vector<int> st(n);
    int nd = (idx == -1 ? 1 : gondolaSeq[idx]);
    if(idx == -1) idx = 0;
    for(int i = 0; i < n; i++){
        st[(idx + i) % n] = nd++;
        if(nd > n) nd = 1;
    }
    vector<pair<int,int>> srt;
    for(int i = 0; i < n; i++){
        if(gondolaSeq[i] > n) srt.emplace_back(gondolaSeq[i], i);
    }
    sort(srt.begin(), srt.end());
    int l = 0;
    int c = n + 1;
    for(auto [v, i]: srt){
        replacementSeq[l++] = st[i];
        while(c < v){
            replacementSeq[l++] = c++;
        }
        c++;
    }
    return l;
}


ll pwr(int x, int y){
    ll res = 1;
    while(y){
        if(y % 2) res = res * x % mod;
        x = (ll) x * x % mod;
        y /= 2;
    }
    return res;
}

int countReplacement(int n, int inputSeq[]){
    if(!valid(n, inputSeq)) return 0;
    vector<int> a;
    for(int i = 0; i < n; i++){
        if(inputSeq[i] > n) a.push_back(inputSeq[i]);
    }
    sort(a.begin(), a.end());
    ll ans = 1;
    int prv = n;
    for(int i = 0; i < a.size(); i++){
        ans = (ans * pwr((int) a.size() - i, a[i] - prv - 1)) % mod;
        prv = a[i];
    }
    if(a.size() == n){
        ans = ans * n % mod;
    }
    return ans;
}