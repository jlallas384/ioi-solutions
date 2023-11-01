#include <bits/stdc++.h>
#include "aliens.h"
using namespace std;
using ll = long long;
long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c){
	vector<int> mx(m, -1);
	for(int i = 0; i < n; i++){
		if(r[i] > c[i]) swap(r[i], c[i]);
		mx[r[i]] = max(mx[r[i]], c[i]);
	}
	vector<int> nd(m);
	int lst = -1;
	int fst = -1;
	int lsti = 0;
	for(int i = 0; i < m; i++) if(mx[i] != -1){
		if(fst == -1) fst = i;
		lst = mx[i];
		nd[i] = mx[i] - i + 1;
		lsti = max(lsti, i + nd[i]);
	}
	vector<vector<ll>> dp(m + 1, vector<ll>(k + 1, 1e18));
	dp[fst][0] = 0;
	for(int i = 0; i < m; i++) if(nd[i]){
		for(int j = 0; j < k; j++){
			int lstl = 0;
			for(int ln = 1; i + ln <= m; ln++){
				if(nd[i + ln - 1]) lstl = max({lstl, mx[i + ln - 1] - i + 1});
				dp[i + lstl][j + 1] = min(dp[i + lstl][j + 1], dp[i][j] + lstl * lstl);
				ln += lstl - 1;
			}
		}
	}
	ll ans = 1e18;
	for(int i = lsti; i <= m; i++){
		ans = min(ans, *min_element(dp[i].begin(), dp[i].end()));
	}
	return ans;
}
