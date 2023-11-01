#include "plants.h"
#include <bits/stdc++.h>
using namespace std;
 
struct tree{
	pair<int,int> mn;
	tree *lc, *rc;
	int l,r,lz = 0;
	tree(int i, int j, vector<int> &a){
		l = i, r = j;
		if(l == r){
			mn = {a[l], l};
			lc = nullptr , rc = nullptr;
		}else{
			int m = (l + r) / 2;
			lc = new tree(l, m, a), rc = new tree(m + 1, r, a);
			mn = min(lc->mn, rc->mn);
		}
	}
	void push(){
		if(l != r){
			lc->lz += lz;
			lc->mn.first = max(0, lc->mn.first - lz);
			rc->lz += lz;
			rc->mn.first = max(0, rc->mn.first - lz);
		}
		lz = 0;
	}
	void dec(int i, int j){
		push();
		if(i > j){
			dec(0, j), dec(i, r);
			return;
		}else if(r < i || j < l) return;
		else if(i <= l && r <= j){
			lz++;
			mn.first = max(mn.first - 1, 0);
		}else{
			lc->dec(i, j), rc->dec(i, j);
			mn = min(lc->mn, rc->mn);
		}
	}
	pair<int,int> qry(int i, int j){
		push();
		if(i > j) return min(qry(0, j), qry(i, r));
		if(r < i || j < l) return {1e9, 1e9};
		if(i <= l && r <= j) return mn;
		return min(lc->qry(i,j), rc->qry(i,j));
	}
	void rem(int i){
		push();
		if(l == r){
			mn.first = 1e9;
		}else{
			if(i <= lc->r) lc->rem(i);
			else rc->rem(i);
			mn = min(lc->mn, rc->mn);
		}
	}
};
 
vector<int> ans;
void init(int k, std::vector<int> r) {
	int n = r.size();
	ans.resize(n);
	tree *t = new tree(0, n - 1, r);
	set<int> st, valid;
	auto add = [&](int x){
		st.insert(x);
		valid.insert(x);
		if(st.size() == 1) return;
		auto it = st.upper_bound(x);
		if(it != st.end() && *it - x < k){
			valid.erase(*it);
		}else if(it == st.end() && *st.begin() + n - x < k){
			valid.erase(*st.begin());
		}
		it = st.lower_bound(x);
		if(it == st.begin() && x + n - *st.rbegin() < k){
			valid.erase(x);
		}else if(it != st.begin() && x - *prev(it) < k){
			valid.erase(x);
		}
	};
	for(int i = 0; i < n; i++) if(r[i] == 0){
		add(i);
	}
	for(int val = n - 1; val >= 0; val--){
		assert(valid.size() == 1);
		int x = *valid.begin();
		t->dec((x - k + 1 + n) % n, (x - 1 + n) % n);
		while(true){
			auto [v, i] = t->qry((x - k + 1 + n) % n, (x - 1 + n) % n);
			if(v != 0) break;
			else{
				t->rem(i);
				add(i);
			}
		}
		ans[x] = val;
		valid.erase(x);
		st.erase(x);
		t->rem(x);
		auto it = st.upper_bound(x);
		if(it != st.end()) add(*it);
		else if(it == st.end()) add(*st.begin());
	}
}
 
int compare_plants(int x, int y) {
	if(ans[x] > ans[y]) return 1;
	else return -1;
}