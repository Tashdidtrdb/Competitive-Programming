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

//divide and conquer dp optimization
ll cost[8005];
ll dp[2][8005];

inline ll getCost(int L, int R) {
  return ( 1ll * (cost[R] - cost[L - 1]) * (R - L + 1) );
}

inline void compute(int cur, int L, int R, int best_L, int best_R) {
  if (L > R) return;
  int mid = (L + R) >> 1;
  pair<ll, int>best = {inf, -1};

  for (int k = best_L; k <= min(best_R, mid); k++) {
    best = min(best, {dp[cur ^ 1][k - 1] + getCost(k, mid), k});
  }

  dp[cur][mid] = best.ff;
  int best_id = best.ss;

  compute(cur, L, mid - 1, best_L, best_id);
  compute(cur, mid + 1, R, best_id, best_R);
}

int arr[MAX];
int main() {

  fastio;
  int n, g;
  cin >> n >> g;
  for (int i = 1; i <= n; i++) cin >> cost[i];
  for (int i = 1; i <= n; i++) cost[i] += cost[i - 1];

  int cur = 0;
  for (int i = 1; i <= n; i++) dp[1][i] = inf;

  for (int guard = 1; guard <= g; guard++) {
    compute(cur, 1, n, 1, n);
    cur ^= 1;
  }

  ll ans = dp[cur ^ 1][n];
  cout << ans << "\n";
}