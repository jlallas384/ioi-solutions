#include <bits/stdc++.h>
#include "stations.h"
using namespace std;
const int N = 1010;
int tin[N], tout[N], cur = 0;
vector<int> g[N];

void dfs(int v, int p){
	tin[v] = cur++;
	for(int u: g[v]) if(u != p){
		dfs(u, v);
	}
	tout[v] = cur - 1;
}

void dfs2(int v, int p){
	tin[v] = cur++;
	for(int u: g[v]) if(u != p){
		dfs2(u, v);
	}
}

std::vector<int> label(int n, int k, std::vector<int> u, std::vector<int> v){
	for(int i = 0; i < n; i++){
		g[i].clear();
	}
	cur = 0;
	int bt = 1;
	for(int i = 0; i < n - 1; i++){
		g[u[i]].push_back(v[i]);
		g[v[i]].push_back(u[i]);
		bt &= (u[i] == i + 1 && v[i] == i / 2) || (v[i] == i + 1 && u[i] == i / 2);
	}
	if(bt){
		vector<int> res(n);
		iota(res.begin(), res.end(), 0);
		return res;
	}
	int mx = 0;
	for(int i = 0; i < n; i++){
		mx = max(mx, (int) g[i].size());
	}
	if(mx <= 2){
		vector<int> res(n);
		for(int i = 0; i < n; i++) if(g[i].size() == 1){
			dfs2(i, -1);
			break;
		}
		for(int i = 0; i < n; i++){
			res[i] = tin[i];
		}
		return res;
	}
	dfs(0, -1);
	vector<int> res(n);
	for(int i = 0; i < n; i++){
		res[i] = tin[i] * 1000 + tout[i];
	}
	return res;
}

pair<int,int> f(int v){
	return {v / 1000, v % 1000};
};

int is_anc(int anc, int desc){
	auto [ti1, to1] = f(anc);
	auto [ti2, to2] = f(desc);
	return ti1 <= ti2 && to2 <= to1;
}

int find_next_station(int s, int t, std::vector<int> c){

	if(max(*max_element(c.begin(), c.end()), s) < 1000){
		int mxdif = 0;
		for(int x: c){
			mxdif = max(mxdif, x - s);
		}
		if(mxdif <= 1){
			if(s <= t){
				return *max_element(c.begin(), c.end());
			}else{
				return *min_element(c.begin(), c.end());
			}
		}else{
			int st = t;
			while(true){
				if(find(c.begin(), c.end(), st) != c.end()) return st;
				if(st == 0) break;
				st = (st - 1) / 2;
			}
			return (s - 1) / 2;
		}
	}
	if(is_anc(t, s)){
		return *min_element(c.begin(), c.end());
	}else if(is_anc(s, t)){
		int mx = 0;
		for(int x: c){
			if(is_anc(x, t)) mx = max(mx, x);
		}
		return mx;
	}else{
		return *min_element(c.begin(), c.end());
	}
}
