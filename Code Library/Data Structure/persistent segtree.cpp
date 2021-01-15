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

//persistent segtree
struct node {
  int val;
  node *lft, *rt;
  node() : val(0), lft(NULL), rt(NULL) {}
  node(int val, node *lft = NULL, node *rt = NULL) : val(val), lft(lft), rt(rt) {}
} *root[MAX];

void build(node *now, int L, int R) {
  if (L == R) return;
  int mid = (L + R) >> 1;
  now->lft = new node();
  now->rt = new node();
  build(now->lft, L, mid);
  build(now->rt, mid + 1, R);
}

node *update(node *now, int L, int R, int idx, int val) {
  if (L > idx || R < idx) return now;
  if (L == R) return new node(now->val + val, now->lft, now->rt);
  int mid = (L + R) >> 1;
  node *ret = new node();
  ret->lft = update(now->lft, L, mid, idx, val);
  ret->rt = update(now->rt, mid + 1, R, idx, val);
  ret->val = (ret->lft)->val + (ret->rt)->val;
  return ret;
}

int query(node *now, int L, int R, int i, int j) {
  if (L > j || R < i) return 0;
  if (L >= i && R <= j) return now->val;
  int mid = (L + R) >> 1;
  return query(now->lft, L, mid, i, j) + query(now->rt, mid + 1, R, i, j);
}

///in main(make segtree for every prefix)
root[0] = new node();
build(root[0], 0, n - 1);
root[0] = update(root[0], 0, n - 1, p[0], 1);
for (int i = 1; i < n; i++) root[i] = update(root[i - 1], 0, n - 1, p[i], 1);

int arr[MAX];
int main() {

  fastio;

}