#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9;

pair<vector<ll>,vector<ll>> comp(vector<int> xs, map<int,int> c){
	vector<ll> res;
	vector<ll> cnt;
	for(int x: xs){
		res.push_back((res.empty() ? 0 : res.back()) + x * c[x]);
		cnt.push_back((cnt.empty() ? 0 : cnt.back()) + c[x]);
	}
	return {res, cnt};
}

int DistanceSum(int n, int X[], int Y[]){
	if(!(n <= 2000)){
		vector<int> xs, ys;
		for(int i = 0; i < n; i++){
			xs.push_back(X[i]);
			ys.push_back(Y[i]);
		}
		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());
		map<int,int> c1, c2;
		for(int x: xs){
			c1[x]++;
		}
		for(int y: ys){
			c2[y]++;
		}
		xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
		ys.resize(unique(ys.begin(), ys.end()) - ys.begin());	
		vector<pair<int,int>> xy;
		for(int i = 0; i < n; i++){
			xy.emplace_back(X[i], Y[i]);
		}
		auto [px, cx] = comp(xs, c1);
		auto [py, cy] = comp(ys, c2);
		ll ans = 0;
		for(auto [x,y]: xy){
			int it = prev(upper_bound(xs.begin(), xs.end(), x)) - xs.begin();

			ans += x * cx[it] - px[it] + px.back() - px[it] - (cx.back() - cx[it]) * x;
			it = prev(upper_bound(ys.begin(), ys.end(), y)) - ys.begin();

			ans += y * cy[it] - py[it] + py.back() - py[it] - (cy.back() - cy[it]) * y;
		}
		return ans / 2 % mod;
	}else{
		vector<int> xs, ys;
		for(int i = 0; i < n; i++){
			xs.push_back(X[i]);
			ys.push_back(Y[i]);
		}
		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());
		xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
		ys.resize(unique(ys.begin(), ys.end()) - ys.begin());	
		vector<pair<int,int>> xy;
		for(int i = 0; i < n; i++){
			xy.emplace_back(lower_bound(xs.begin(), xs.end(), X[i]) - xs.begin(), lower_bound(ys.begin(), ys.end(), Y[i]) - ys.begin());
		}
		vector<vector<int>> g(n);
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				if(abs(xy[i].first - xy[j].first) + abs(xy[i].second - xy[j].second) == 1){
					g[i].push_back(j);
					g[j].push_back(i);
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i++){
			vector<int> dist(n, -1);
			dist[i] = 0;
			queue<int> q;
			q.push(i);
			while(q.size()){
				int v = q.front(); q.pop();
				for(int u: g[v]) if(dist[u] == -1){
					dist[u] = dist[v] + 1;
					q.push(u);
				}
			}
			for(int j = i; j < n; j++){
				ans = (ans + dist[j]) % mod;
			}
		}
		return ans;
	}
}