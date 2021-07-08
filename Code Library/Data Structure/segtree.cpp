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

ll sum[MAX << 2];
ll lazy[MAX << 2];

void build(int now, int L, int R) {
  if (L == R) {
    sum[now] = arr[L];
    return;
  }
  int mid = (L + R) >> 1;
  int lft = now << 1, rt = lft | 1;
  build(lft, L, mid);
  build(rt, mid + 1, R);
  sum[now] = sum[lft] + sum[rt];
}

void push(int now, int L, int R) {
  if (lazy[now]) {
    sum[now] += (R - L + 1) * lazy[now];
    if (L != R) {
      lazy[(now) << 1] += lazy[now];
      lazy[(now << 1) | 1] += lazy[now];
    }
  }
  lazy[now] = 0;
}

void update(int now, int L, int R, int i, int j, ll val) {
  push(now, L, R);
  if (R < i || L > j) return;
  if (L >= i && R <= j) {
    lazy[now] += val;
    push(now, L, R);
    return;
  }
  int mid = (L + R) >> 1;
  int lft = now << 1, rt = lft | 1;
  update(lft, L, mid, i, j, val);
  update(rt, mid + 1, R, i, j, val);
  sum[now] = sum[lft] + sum[rt];
}

ll query(int now, int L, int R, int i, int j) {
  push(now, L, R);
  if (R < i || L > j) return 0;
  if (L >= i && R <= j) return sum[now];
  int mid = (L + R) >> 1;
  int lft = now << 1, rt = lft | 1;
  return query(lft, L, mid, i, j) + query(rt, mid + 1, R, i, j);
}

int arr[MAX];
int main() {

  fastio;

}