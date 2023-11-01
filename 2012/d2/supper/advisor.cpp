#include <bits/stdc++.h>
#include "advisor.h"
using namespace std;
void ComputeAdvice(int *C, int N, int K, int M) {
  vector<vector<int>> nxt(N);
  for(int i = N - 1; i >= 0; i--){
    nxt[C[i]].push_back(i);
  }
  priority_queue<pair<int,int>> pq;
  for(int i = 0; i < K; i++){
    pq.emplace(nxt[i].empty() ? N : nxt[i].back(), i);
  }
  vector<int> hv(N);
  for(int i = 0; i < K; i++){
    hv[i] = 1;
  }
  for(int i = 0; i < N; i++){
    nxt[C[i]].pop_back();
    if(hv[C[i]]) WriteAdvice('0');
    else{
      WriteAdvice('1');
      auto [id, t] = pq.top(); pq.pop();
      hv[t] = 0;
      for(int bit = 0; bit <= 16; bit++){
        if(t & (1 << bit)) WriteAdvice('1');
        else WriteAdvice('0');
      }
      pq.emplace(nxt[C[i]].empty() ? N : nxt[C[i]].back(), C[i]);
      hv[C[i]] = 1;
    }
  }
}
