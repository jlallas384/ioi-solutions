#include <bits/stdc++.h>
#include "teams.h"
using namespace std;
vector<pair<int,int>> seg;

void init(int N, int A[], int B[]) {
	for(int i = 0; i < N; i++){
		seg.emplace_back(A[i], B[i]);
	}
	sort(seg.begin(), seg.end());
}

int can(int m, int K[]) {
	vector<int> k;
	for(int i = 0; i < m; i++){
		k.push_back(K[i]);
	}
	sort(k.begin(), k.end());
	multiset<int> ms;
	int ptr = 0;
	for(int x: k){
		while(ptr < seg.size() && seg[ptr].first <= x){
			ms.insert(seg[ptr++].second);
		}
		while(ms.size() && *ms.begin() < x){
			ms.erase(ms.find(*ms.begin()));
		}
		if(ms.size() < x) return 0;
		for(int it = 0; it < x; it++){
			ms.erase(ms.find(*ms.begin()));
		}
	}
	return 1;
}
