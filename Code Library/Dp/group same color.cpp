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

//group same color together in minimum adjacent swaps(m is number of colors in array...all colors have to be present from 1 to m)
int prv[21];
ll cost[21][21] ;
int m, n;

ll dp[1 << 21];
bool ok[1 << 21];

ll solve(ll mask) {
  if (mask == (1 << m) - 1) return 0ll;
  ll &ret = dp[mask];
  if (ok[mask]) return ret;
  ok[mask] = true;
  ret = inf;

  for (int i = 0; i < m; i++) {
    if (!(mask & (1 << i) )) {
      ll c = 0;
      for (int j = 0; j < m; j++) {
        if ((mask & (1 << j) ) )
          c += cost[i][j];
      }
      ret = min(ret, c + solve((mask | (1 << i))));
    }
  }
  return ret;
}

int arr[MAX];
int main() {

  fastio;
  for (int i = 0; i < n; i++) {
    int val = arr[i];
    val--;
    prv[val]++;
    for (int j = 0; j < m; j++) {
      if (val == j) continue;
      cost[val][j] += prv[j];
    }
  }
  ll ans = solve(0);
}