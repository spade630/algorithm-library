#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef int ut;
const int INF = 1<<29;

struct Node {
  ut value, minum;
  //ut sum;
  int size;
  Node* lch;
  Node* rch;
  Node(ut v) : value(v), minum(v), size(1),lch(NULL), rch(NULL) {
    //sum = v;
  }
};

typedef pair<Node*, Node*> npr;

// merge/splitベースのRBST
struct RBST {
  Node* root;

  RBST(){
    srand(time(NULL));
  }

  int size(Node* t) { return !t ? NULL : t->size; }
  //int sum(Node* t) { return !t ? NULL : t->sum; }
  //int minum(Node* t) { return !t ? INF : t->minum; }

  Node* update(Node* t){
    t->size = size(t->lch) + size(t->rch) + 1;
    //t->minum = min(t->value, min(minum(t->lch), minum(t->rch)));
    //t->sum = sum(t->lch) + sum(t->rch) + t->value;
    return t;
  }

  Node* merge(Node* l, Node* r){
    if(!l || !r)
      return !l ? r : l;

    int m = l->size, n = r->size;
    if(rand() % (m + n) < m){
      l->rch = merge(l->rch, r);
      return update(l);
    }
    else{
      r->lch = merge(l, r->lch);
      return update(r);
    }
  }

  npr split(Node* t, int k){ // [0, k), [k, n)
    if(!t)
      return npr(NULL, NULL);
    if(k <= size(t->lch)){
      npr s = split(t->lch, k);
      t->lch = s.second;
      return npr(s.first, update(t));
    }
    else{
      npr s = split(t->rch, k - size(t->lch) - 1);
      t->rch = s.first;
      return npr(update(t), s.second);
    }
  }

  Node* insert(Node* t, int v) {
    return insert(t, lower_bound(t, v), v);
  }

  Node* insert(Node* t, int k, ut v){
    npr tmp = split(t, k);
    Node *p = new Node(v);
    return merge(merge(tmp.first, p), tmp.second);
  }

  Node* erase(Node* t, int k){
    npr tmp = split(t, k);
    return merge(tmp.first, split(tmp.second, 1).second);
  }

  void showtree(Node* c){
    if(!c) return;
    //printf("(");
    showtree(c->lch);
    printf(" %d ", c->value);
    showtree(c->rch);
    //printf(")");
  }

  int lower_bound(Node* t, int v){
    if(!t)
      return 0;
    if(t->value >= v)
      return lower_bound(t->lch, v);
    return lower_bound(t->rch, v) + size(t->lch) + 1;
  }

  int upper_bound(Node* t, int v){
    if(!t)
      return 0;
    if(t->value > v)
      return upper_bound(t->lch, v);
    return lower_bound(t->rch, v) + size(t->lch) + 1;
  }
};

int main() {
  RBST* rbst = new RBST();

  rbst->root = rbst->insert(rbst->root, x, v) // x番目に値vを挿入
  rbst->root = rbst->insert(rbst->root, v) // ソート列を崩さずに値vを挿入
  rbst->root = rbst->erase(rbst->root, x) // x番目を削除
  rbst->merge(a, b) // ノード(部分木)aとノードbをマージ
  rbst->split(a, k) // (部分)木aを[0, k)と[k, n)に分割
  rbst->lower_bound(rbst->root, v) // 値vで二分探索
  rbst->upper_bound(rbst->root, v) // 同上

  return 0;
}