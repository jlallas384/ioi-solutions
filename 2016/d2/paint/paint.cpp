#include "paint.h"
#include <bits/stdc++.h>
using namespace std;
struct DP{
    array<array<array<int, 2>, 110>, 200101> dp;
    vector<int> s, c, pre;
    DP(vector<int> s, vector<int> c): s(s), c(c), pre(s.size() + 1){
        for(int i = 0; i < 200101; i++){
            for(int j = 0; j < 110; j++){
                for(int k = 0; k < 2; k++){
                    dp[i][j][k] = -1;
                }
            }
        }
        for(int i = 1; i <= s.size(); i++){
            pre[i] = pre[i - 1] + (s[i - 1] != 0);
        }
    }
    int f(int idx, int lft, int col){
        if(dp[idx][lft][col] != -1) return dp[idx][lft][col];
        if(idx == 0) return lft == 0;
        if(lft == 0 && col) return 0;
        if(s[idx - 1] != 2 && s[idx - 1] != col) return 0;
        int ans = 0;
        if(col == 0){
            ans |= f(idx - 1, lft, 0);
            ans |= f(idx - 1, lft, 1);
        }else{
            if(idx < c[lft - 1]) return 0;
            if(pre[idx] - pre[idx - c[lft - 1]] != c[lft - 1]) return 0;
            ans |= f(idx - c[lft - 1], lft - 1, 0);
        }
        return dp[idx][lft][col] = ans;
    };
};

std::string solve_puzzle(std::string s, std::vector<int> c) {
    int n = s.size(), k = c.size();
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        if(s[i] == '.') a[i] = 2;
        else if(s[i] == 'X') a[i] = 1;
        else a[i] = 0;
    }
    DP dpl(a, c);
    reverse(a.begin(), a.end());
    reverse(c.begin(), c.end());
    DP dpr(a, c);
    reverse(c.begin(), c.end());
    vector<int> w(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= k; j++){
            w[i] |= dpl.f(i, j, 0) && (dpr.f(n - i, k - j, 0) || dpr.f(n - i, k - j, 1));
            int can = dpl.f(i, j, 1) && (dpr.f(n - i, k - j, 0));
            if(can){
                b[i - c[j - 1] + 1]++;
                if(i != n) b[i + 1]--;
            }
        }
    }
    string ans(n, '*');
    for(int i = 1; i <= n; i++){
        if(b[i] && w[i]) ans[i - 1] = '?';
        else if(b[i]) ans[i - 1] = 'X';
        else if(w[i]) ans[i - 1] = '_';
        if(i != n) b[i + 1] += b[i];
    }
    return ans;
}
