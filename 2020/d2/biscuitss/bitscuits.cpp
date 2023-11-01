#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int can(ll x, ll y, vector<long long> a){
	for(int i = 0; i < a.size(); i++){
		if(y & (1LL << i)){
			if(a[i] < x) return 0;
			a[i] -= x;
		}
		if(i + 1 < a.size()){
			a[i + 1] += a[i] / 2;
		}
	}
	return 1;
}

long long count_tastiness(long long x, std::vector<long long> a){
	int ans = 0;
	while(a.size() < 60) a.push_back(0);
	for(int i = 0; i <= 100000; i++){
		ans += can(x, i, a);
	}
	return ans;
}




ABA

AAB
BAA
BAB
AAA




A B A B A


A BBB A

A AAB A

A ABA A

A B A B A
_ _ _ _ _

B A A A B
_   _   _


A B A A A B B



A_A
 A AB - 1
 B AA - 2
 B BB - 3
 B AB - 3
 B BA - 4

A_A_A_
 B A B
 B B B
 B A A