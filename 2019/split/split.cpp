#include <bits/stdc++.h>
using namespace std;
const int N = 100100;
vector<int> g[N];

int ans[N], dead[N], vis[N], szs[N];
void dfs2(int v, int p, int who, int &sz);

int mn = 1e9, wv = 0, wp = 0;

int dfs(int v, int p, int who, int sz){
	szs[v] = 1;
	vis[v] = 1;
	for(int u: g[v]) if(u != p && !dead[u]){
		dfs(u, v, who, sz);
		szs[v] += szs[u];
	}
	if(szs[v] >= sz){
		if(szs[v] < mn){
			mn = szs[v];
			wv = v;
			wp = p;
		}
	}
	return 0;
}

void dfs2(int v, int p, int who, int &sz){
	dead[v] = 1;
	if(sz){
		sz--;
		ans[v] = who;
	}
	for(int u: g[v]) if(u != p && !dead[u]){
		dfs2(u, v, who, sz);
	}
}

std::vector<int> find_split(int n, int a, int b, int c, std::vector<int> p, std::vector<int> z){
	if(p.size() != n - 1) return vector<int>(n);
	for(int i = 0; i < p.size(); i++){
		g[p[i]].push_back(z[i]);
		g[z[i]].push_back(p[i]);
	}
	vector<int> s = {a, b, c};
	vector<int> ord = {0, 1, 2};
	sort(ord.begin(), ord.end(), [&](int i, int j){
		return s[i] < s[j];
	});
	dfs(0, -1, ord[0] + 1, s[ord[0]]);
	dfs2(wv, wp, ord[0] + 1, s[ord[0]]);
	for(int i = 0; i < n; i++){
		vis[i] = 0;
	}
	mn = 1e9;
	int has = 0;
	for(int i = 0; i < n; i++) if(!dead[i] && !vis[i]){
		dfs(i, -1, ord[1] + 1, s[ord[1]]);
	}
	if(mn == 1e9) return vector<int>(n);
	dfs2(wv, wp, ord[1] + 1, s[ord[1]]);
	vector<int> fans(n);
	for(int i = 0; i < n; i++){
		if(ans[i] == 0){
			fans[i] = ord[2] + 1;
		}else{
			fans[i] = ans[i];
		}
	}
	return fans;
}
