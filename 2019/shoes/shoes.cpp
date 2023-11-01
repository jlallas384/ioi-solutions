#include <bits/stdc++.h>
using namespace std;
struct FT{
	vector<int> ft;
	int n;
	FT(int n): ft(n + 1), n(n){}
	void upd(int i){
		for(; i <= n; i += i & -i){
			ft[i]++;
		}
	}
	int qry(int i){
		int res = 0;
		for(; i > 0; i -= i & -i){
			res += ft[i];
		}
		return res;
	}
	int inv(int i){
		return qry(n) - qry(i);
	}
};

long long count_swaps(std::vector<int> a){
	int n = a.size();
	map<int, queue<int>> mp;
	for(int i = 0; i < n; i++){
		mp[a[i]].push(i);
	}
	vector<int> idx(n, -1);
	int cur = 1;
	for(int i = 0; i < n; i++){
		if(idx[i] == -1){
			if(a[i] < 0){
				idx[i] = cur++;
				idx[mp[a[i] * -1].front()] = cur++;
			}else{
				idx[mp[a[i] * -1].front()] = cur++;	
				idx[i] = cur++;			
			}
			mp[a[i] * -1].pop(); 
			mp[a[i]].pop();
		}
	}
	FT ft(2 * n);
	long long ans = 0;
	for(int i = 0; i < n; i++){
		ans += ft.inv(idx[i]);
		ft.upd(idx[i]);
	}
	return ans;
}

