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

//implicit_segtree (update: delete x, query: get kth number not deleted ...supports range even upto 10^9)
struct node {
  int val;
  node *lft, *rt;
  node() {}
  node(int val = 0) : val(val), lft(NULL), rt(NULL) {}
};

struct implicit_segtree {
  node *root;
  implicit_segtree() {}
  implicit_segtree(int n) {
    root = new node(n);
  }

  void update(node *now, int L, int R, int idx, int val) {
    if (L == R) {
      now -> val += val;
      return;
    }

    int mid = L + (R - L) / 2;
    if (now->lft == NULL) now->lft = new node(mid - L + 1);
    if (now->rt == NULL) now->rt = new node(R - mid);

    if (idx <= mid) update(now->lft, L, mid, idx, val);
    else update(now->rt, mid + 1, R, idx, val);

    now->val = (now->lft)->val + (now->rt)->val;
  }

  int query(node *now, int L, int R, int k) {
    if (L == R) return L;

    int mid = L + (R - L) / 2;
    if (now->lft == NULL) now->lft = new node(mid - L + 1);
    if (now->rt == NULL) now->rt = new node(R - mid);

    if (k <= (now->lft)->val) return query(now->lft, L, mid, k);
    else return query(now->rt, mid + 1, R, k - (now->lft)->val);
  }
};

int arr[MAX];
implicit_segtree tree;
int main() {

  fastio;
  int n;
  cin >> n;
  tree = implicit_segtree(n);
  int m;
  cin >> m;
  while (m--) {
    char c;
    int k;
    cin >> c >> k;
    int val = tree.query(tree.root, 1, n, k);
    if (c == 'D') tree.update(tree.root, 1, n, val, -1);
    else cout << val << "\n";
  }
}