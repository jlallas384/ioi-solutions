#include <bits/stdc++.h>
using namespace std;
struct tree{
	tree *lc = nullptr, *rc = nullptr;
	int sum = 0, l, r;
	tree(int i, int j){
		l = i, r = j;
		if(l == r){
			sum = 1;
		}else{
			int m = (l + r) / 2;
			lc = new tree(l, m);
			rc = new tree(m + 1, r);
			sum = lc->sum + rc->sum;
		}
	}
	void upd(int i){
		if(l == r){
			sum = 0;
		}else{
			if(i <= lc->r) lc->upd(i);
			else rc->upd(i);
			sum = lc->sum + rc->sum;
		}
	}
	int kth(int i){
		if(l == r) return l;
		int ls = lc->sum;
		if(i > ls) return rc->kth(i - ls);
		else return lc->kth(i);
	}
};


int GetBestPosition(int n, int c, int r, int k[], int s[], int e[]){
	vector<int> a;
	for(int i = 0; i < n - 1; i++){
		a.push_back(k[i]);
	}
	int bst = -1, idx = -1;
	for(int i = 0; i <= n - 1; i++){
		tree *st = new tree(0, n);
		set<int> sts;
		for(int i = 0; i < n; i++){
			sts.insert(i);
		}
		int ths = 0;
		for(int j = 0; j < c; j++){
			int li = st->kth(s[j] + 1), ri = st->kth(e[j] + 1);
			vector<pair<int,int>> arr;
			auto it = sts.lower_bound(li);
			while(it != sts.end() && *it <= ri){
				if(*it == i) arr.emplace_back(r, *it);
				else arr.emplace_back(k[*it - (*it > i)], *it);
				it = next(it);
			}
			sort(arr.begin(), arr.end());
			if(arr.back().first == r) ths++;
			for(int l = 0; l < arr.size() - 1; l++){
				st->upd(arr[l].second);
				sts.erase(arr[l].second);
			}
		}
		if(ths > bst){
			bst = ths;
			idx = i;
		}
	}
	return idx;
}
