#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<ll, ll>
#define ff first
#define ss second
#define pb push_back
#define fastio ios::sync_with_stdio(false); cin.tie(NULL);
#define PI 2*acos(0.0)
#define eps 1e-11
#define DEBUG(x) cerr << #x << " = " << x << endl
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int MAX = 2e5 + 5, MOD = 1e9 + 7;
const ll inf = 1e18 + 5;

//implicit_treap
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef struct node* pnode;
struct node {
  int prior, sz;
  ll val;
  bool rev;
  node *lft, *rt;
  node(int val = 0, node *lft = NULL, node *rt = NULL) : lft(lft), rt(rt), prior(rnd()), sz(1), val(val), rev(false) {}
};

struct implicit_treap {
  pnode root;
  treap() {
    root = NULL;
  }

  int get_sz(pnode now) {
    return now ? now->sz : 0;
  }

  void update_sz(pnode now) {
    if (!now) return;
    now->sz = 1 + get_sz(now->lft) + get_sz(now->rt);
  }

  void push(pnode now) {
    if (!now || !now->rev) return;
    now->rev = false;
    swap(now->lft, now->rt);
    if (now->lft) now->lft->rev ^= true;
    if (now->rt) now->rt->rev ^= true;
  }

  void combine(pnode now) {

  }

  ///first pos ta elements go to left, others go to right
  void split(pnode now, pnode &lft, pnode &rt, int pos, int add = 0) {
    if (!now) return void(lft = rt = NULL);
    push(now);
    int cur = add + get_sz(now->lft);
    if (cur < pos) split(now->rt, now->rt, rt, pos, cur + 1), lft = now;
    else split(now->lft, lft, now->lft, pos, add), rt = now;
    update_sz(now);
    // combine(now);
  }

  void merge(pnode &now, pnode lft, pnode rt) {
    push(lft);
    push(rt);
    if (!lft || !rt) now = lft ? lft : rt;
    else if (lft->prior > rt->prior) merge(lft->rt, lft->rt, rt), now = lft;
    else merge(rt->lft, lft, rt->lft), now = rt;
    update_sz(now);
    // combine(now);
  }

  void insert(int pos, ll val) {
    if (!root) return void(root = new node(val));
    pnode lft, rt;
    split(root, lft, rt, pos - 1);
    pnode notun = new node(val);
    merge(root, lft, notun);
    merge(root, root, rt);
  }

  void erase(int pos) {
    pnode lft, rt, temp;
    split(root, lft, rt, pos);
    split(lft, lft, temp, pos - 1);
    merge(root, lft, rt);
    delete(temp);
  }

  void reverse(int l, int r) {
    pnode lft, rt, mid;
    split(root, lft, mid, l - 1);
    split(mid, mid, rt, r - l + 1);
    mid->rev ^= true;
    merge(root, lft, mid);
    merge(root, root, rt);
  }

  void right_shift(int l, int r) {
    pnode lft, rt, mid, last;
    split(root, lft, mid, l - 1);
    split(mid, mid, rt, r - l + 1);
    split(mid, mid, last, r - l);
    merge(mid, last, mid);
    merge(root, lft, mid);
    merge(root, root, rt);
  }

  void output(pnode now, vector<int>&v) {
    if (!now) return;
    push(now);
    output(now->lft, v);
    v.pb(now->val);
    output(now->rt, v);
  }

  vector<int>get_arr() {
    vector<int>ret;
    output(root, ret);
    return ret;
  }
};

int arr[MAX];
int main() {

  fastio;

}