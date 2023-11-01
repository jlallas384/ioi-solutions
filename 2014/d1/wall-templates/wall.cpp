#include <bits/stdc++.h>
#include "wall.h"
using namespace std;

struct Seg{
    int l,r;
    Seg(): l(0), r(100000){}
    Seg(int l, int r): l(l), r(r){}
    void apply(Seg oth){
        if(r < oth.l){
            l = r = oth.l;
        }else if(oth.r < l){
            l = r = oth.r;
        }else{
            l = max(l, oth.l);
            r = min(r, oth.r);
        }
    }
};

struct Tree{
    Tree *lc, *rc;
    Seg val;
    int l, r;
    Tree(int l, int r): l(l), r(r){
        if(l == r) val = Seg(0, 0);
        else{
            int m = (l + r) / 2;
            lc = new Tree(l, m), rc = new Tree(m + 1, r);
        }
    }
    void push(){
        if(l != r){
            lc->val.apply(val);
            rc->val.apply(val);
        }
        val = Seg();
    }
    void upd(int i, int j, Seg x){
        if(r < i || j < l) return;
        if(i <= l && r <= j){
            val.apply(x);
        }else{
            push();
            lc->upd(i, j, x), rc->upd(i, j, x);
        }
    }
    int qry(int i){
        if(l == r) return val.l;
        else{
            push();
            if(i <= lc->r) return lc->qry(i);
            else return rc->qry(i);
        }
    }
};


void buildWall(int n, int k, int op[], int l[], int r[], int height[], int finalHeight[]){
    Tree *st = new Tree(0, n - 1);
    for(int i = 0; i < k; i++){
        if(op[i] == 1){
            st->upd(l[i], r[i], Seg(height[i], 100000));
        }else{
            st->upd(l[i], r[i], Seg(0, height[i]));
        }
    }
    for(int i = 0; i < n; i++){
        finalHeight[i] = st->qry(i);
    }
}

