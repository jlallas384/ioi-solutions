#include <bits/stdc++.h>
#include "mushrooms.h"
using namespace std;

int count_mushrooms(int n){
	if(n <= 100){
		int ans = 1;
		vector<int> a;
		for(int i = 1; i < n; i++){
			a.push_back(i);
		}
		while(a.size() >= 2){
			int x = a.back(); a.pop_back();
			int y = a.back(); a.pop_back();
			int res = use_machine({x, 0, y});
			ans += 2 - res;
		}
		while(a.size()){
			int x = a.back(); a.pop_back();
			ans += !use_machine({0, x});
		}
		return ans;
	}
	vector<int> al, a, b;
	for(int i = n - 1; i >= 1; i--){
		al.push_back(i);
	}
	while(al.size() && max(a.size(), b.size()) < 100){
		int x = al.back(); al.pop_back();
		if(!use_machine({0, x})) a.push_back(x);
		else b.push_back(x);
	}
	int ans = 1 + a.size();
	int swp = 0;
	if(b.size() > a.size()){
		swap(a, b);
		swp = 1;
	}
	int sz = min(100, (int) a.size());
	while(al.size()){
		vector<int> ths;
		sz = min((int) al.size() + 1, sz);
		for(int i = 0; i < sz - 1; i++){
			ths.push_back(al.back()); al.pop_back();
		}
		int pt1 = 0, pt2 = 0;
		vector<int> res;
		for(int i = 0; i < sz * 2 - 1; i++){
			if(i % 2 == 0) res.push_back(a[pt1++]);
			else res.push_back(ths[pt2++]);
		}
		int ress = use_machine(res);
		if(!swp){
			ans += (sz - 1) - (ress / 2);
		}else{
			ans += ress / 2;
		}
	}
	while(al.size() >= 2){
		int x = al.back(); al.pop_back();
		int y = al.back(); al.pop_back();
		int res = use_machine({x, 0, y});
		ans += 2 - res;
	}
	while(al.size()){
		int x = al.back(); al.pop_back();
		ans += !use_machine({0, x});
	}
	return ans;
}


