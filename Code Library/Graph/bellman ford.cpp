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

//bellman ford
int b[MAX], dis[MAX];
int n, m;
vii u, v, cost;

bool bellman() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      if (dis[v[j]] > dis[u[j]] + cost[j]) {
        dis[v[j]] = dis[u[j]] + cost[j];
      }
    }
  }
  for (int j = 0; j < m; j++) {
    if (dis[v[j]] > dis[u[j]] + cost[j]) {
      return false;
    }
  }

  return true;
}

void initialize() {
  for (int i = 0; i < MAX; i++) {
    dis[i] = 100000000;
    b[i] = 0;
  }
  dis[1] = 0;
  u.clear();
  v.clear();
  cost.clear();
}

int arr[MAX];
int main() {

  int t, caseno = 0;
  scanf("%d", &t);
  while (t--) {
    initialize();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
      int c, d;
      scanf("%d %d", &c, &d);
      int w = (b[d] - b[c]);
      u.push_back(c);
      v.push_back(d);
      cost.push_back(w * w * w);
    }

    int q;
    scanf("%d", &q);
    printf("Case %d:\n", ++caseno);
    bellman();
  }
}