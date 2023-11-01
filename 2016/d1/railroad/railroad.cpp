#include <bits/stdc++.h>
#include "railroad.h"
using namespace std;
using ll = long long;
ll dp[(1 << 16)][16];
vector<int> s,t;
int n;

ll f(int msk, int who){
    if(msk == 0) return 0;
    if(dp[msk][who] != -1) return dp[msk][who];
    ll ans = 1e18;
    for(int i = 0; i < n; i++) if(msk & (1 << i)){
        ans = min(ans, f(msk ^ (1 << i), i) + max(0, t[i] - s[who]));
    }
    return dp[msk][who] = ans;
}

long long plan_roller_coaster(std::vector<int> S, std::vector<int> T) {
    n = (int) S.size();
    s = S, t = T;
    ll ans = 1e18;
    memset(dp, -1, sizeof(dp));
    int m = (1 << n) - 1;
    for(int i = 0; i < n; i++){
        ans = min(ans, f(m ^ (1 << i), i));
    }
    return ans;
}

