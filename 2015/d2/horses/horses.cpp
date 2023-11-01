#include "horses.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;

vector<int> x, y;
int n;

struct tree{
	tree *lc, *rc;
	int mx, l, r;
	tree(){}
	tree(int i, int j){
		l = i, r = j;
		if(l != r){
			int m = (l + r) / 2;
			lc = new tree(l, m);
			rc = new tree(m + 1, r);
		}
	}
	void upd(int i, int x){
		if(l == r) mx = x;
		else{
			if(i <= lc->r) lc->upd(i, x);
			else rc->upd(i, x);
			mx = max(lc->mx, rc->mx);
		}
	};
	int qry(int i, int j){
		if(r < i || j < l) return 0;
		if(i <= l && r <= j) return mx;
		return max(lc->qry(i, j), rc->qry(i, j));
	};
};

struct FT{
	vector<ll> ft;
	int n;
	FT(){}
	FT(int n): n(n), ft(n + 1, 1){}
	void upd(int i, ll x){
		for(; i <= n; i += i & -i){
			ft[i] = ft[i] * x % mod;
		}
	}
	ll qry(int i){
		ll res = 1;
		for(; i > 0; i -= i & -i){
			res = res * ft[i] % mod;
		}
		return res;
	}
};

ll pwr(ll x, ll y){
	ll res = 1;
	while(y){
		if(y % 2){
			res = res * x % mod;
		}
		x = x * x % mod;
		y /= 2;
	}
	return res;
}



tree *st;
FT ft;
set<int> big;

int solve(){
	auto it = big.begin();
	vector<int> hv;
	while(it != big.end() && hv.size() < 30){
		hv.push_back(-(*it));
		it = next(it);
	}
	hv.push_back(-1);
	reverse(hv.begin(), hv.end());
	ll cur = 1;
	if(hv.size() != 1) cur = ft.qry(hv[1]);
	hv.push_back(n);
	vector<pair<int,int>> a;
	for(int i = 0; i < (int) hv.size() - 1; i++){
		if(hv[i] != -1) a.emplace_back(x[hv[i]], y[hv[i]]);
		if(hv[i] + 1 != hv[i + 1]){
			a.emplace_back(1, st->qry(hv[i] + 1, hv[i + 1] - 1));
		}
	}
	for(int i = 0; i < a.size(); i++){
		ll pre = 1;
		ll bst = 0;
		cur = cur * a[i].first % mod;
		for(int j = i + 1; j < a.size(); j++){
			pre *= a[j].first;
			if(pre > 1e9){
				bst = -1;
				break;
			}
			bst = max(bst, pre * a[j].second);
		}
		if(bst != -1 && bst < a[i].second){
			return cur * a[i].second % mod;
		}
	}
	return -1;
}

int init(int N, int X[], int Y[]) {
	n = N;
	x.resize(n), y.resize(n);
	st = new tree(0, n - 1);
	ft = FT(n);
	for(int i = 0; i < n; i++){
		x[i] = X[i];
		y[i] = Y[i];
		st->upd(i, y[i]);
		ft.upd(i + 1, x[i]);
		if(x[i] > 1) big.insert(-i);
	}
	return solve();
}


int updateX(int pos, int val) {	
	if(x[pos] > 1 && val == 1){
		big.erase(-pos);
	}else if(x[pos] == 1 && val > 1){
		big.insert(-pos);
	}
	ft.upd(pos + 1, pwr(x[pos], mod - 2) * val % mod);
	x[pos] = val;
	return solve();
}

int updateY(int pos, int val) {
	st->upd(pos, val);
	y[pos] = val;
	return solve();
}
