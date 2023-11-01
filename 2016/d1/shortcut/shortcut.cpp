#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll diam(int v, int ban, int it, auto &g){
	ll bst = 0, what = v;
	queue<tuple<int,int,ll>> q;
	q.emplace(v, -1, 0);
	while(q.size()){
		auto [v, p, d] = q.front(); q.pop();
		if(d > bst){
			bst = d;
			what = v;
		}
		for(auto [u, w]: g[v]) if(u != p && u != ban){
			q.emplace(u, v, d + w);
		}
	}
	if(it == 1) return bst;
	else return diam(what, ban, 1, g);
}

long long find_shortcut(int n, vector <int> l, vector <int> d, int c){
	vector<vector<pair<int,int>>> g(n * 2);
	int cur = n;
	for(int i = 0; i < n; i++){
		if(i + 1 < n){
			g[i].emplace_back(i + 1, l[i]);
			g[i + 1].emplace_back(i, l[i]);
		}
		if(d[i]){
			g[i].emplace_back(cur, d[i]);
			g[cur].emplace_back(i, d[i]);
			cur++;
		}
	}
	vector<ll> dl1(n), dr1(n), dl2(n), dr2(n);
	for(int i = 0; i < n; i++){
		dl1[i] = diam(i, i + 1, 1, g);
		dl2[i] = diam(i, i + 1, 2, g);
		dr1[i] = diam(i, i - 1, 1, g);
		dr2[i] = diam(i, i - 1, 2, g);
	}
	ll ans = 1e18;
	vector<ll> pre(n);
	for(int i = 0; i < n - 1; i++){
		pre[i + 1] = pre[i] + l[i];
	}
	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; j++){
			ll ths = max({dl2[i], dr2[j], dl1[i] + dr1[j] + min((ll) c, pre[j] - pre[i])});
			for(int i1 = i; i1 <= j; i1++){
				if(i1 != j) ths = max(ths, d[i1] + min(pre[j] - pre[i1], pre[i1] - pre[i] + c) + dr1[j]);
				if(i1 != i) ths = max(ths, d[i1] + min(pre[j] - pre[i1] + c, pre[i1] - pre[i]) + dl1[i]);
				for(int i2 = i1 + 1; i2 <= j; i2++){
					ths = max(ths, min(pre[i1] - pre[i] + pre[j] - pre[i2] + c, pre[i2] - pre[i1]) + d[i1] + d[i2]);
				}
			}
			ans = min(ans, ths);
		}
	}
	return ans;
}
