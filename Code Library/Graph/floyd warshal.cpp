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

//floyd warshal
int g[105][105];
int fr[15];
void initialize(int n) {
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == j) g[i][j] = 0;
      else g[i][j] = INT_MAX;
    }
  }
}

void floyd(int n) {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (g[i][k] + g[k][j] >= 0) g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
}

int arr[MAX];
int main() {

  fastio;
  int t, caseno = 0;
  cin >> t;
  while (t--) {
    int n, m, f;
    cin >> n >> m >> f;
    initialize(n);
    while (m--) {
      int u, v, w;
      cin >> u >> v >> w;
      if (w < g[u][v]) g[u][v] = g[v][u] = w;
    }
    floyd(n);
  }
}