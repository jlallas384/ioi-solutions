#include <bits/stdc++.h>
#include "assistant.h"
using namespace std;
void Assist(unsigned char *A, int N, int K, int R) {
  cout << A[0];
  int pt = 0;
  int ok = 0;
  while(pt < R){
    int x = GetRequest();
    ok++;
    if(A[pt++] == '1'){
      int res = 0;
      for(int i = 0; i <= 16; i++){
        if(A[pt + i] == '1') res += (1 << i);
      }
      pt += 17;
      PutBack(res);
    }
  }
}
