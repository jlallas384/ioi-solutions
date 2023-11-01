#include <bits/stdc++.h>
#include "messy.h"
using namespace std;

std::vector<int> restore_permutation(int n, int w, int r){
	for(int i = 1; i <= n; i++){
		string a = string(i, '0') + string(n - i, '1');
		add_element(a);
	}
	compile_set();
	vector<int> ans(n);
	string nw(n, '1');
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) if(nw[j] == '1'){
			nw[j] = '0';
			if(check_element(nw)){
				ans[j] = i;
				break;
			}
			nw[j] = '1';
		}
	}
	return ans;
}
