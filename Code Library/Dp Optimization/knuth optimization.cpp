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

//knuth optimization
ll solve(int st, int ed) { ///recursive
  if (st == ed) {
    path[st][ed] = st;
    return 0;
  }

  ll &ret = dp[st][ed];
  if (ret != -1) return ret;

  solve(st, ed - 1);
  solve(st + 1, ed);

  int L = max(st, path[st][ed - 1]);
  int R = min(ed - 1, path[st + 1][ed]);
  ret = inf;

  for (int i = L; i <= R; i++) {
    ll cur = solve(st, i) + solve(i + 1, ed);
    cur += (arr[ed] - arr[st - 1]);
    if (cur < ret) {
      ret = cur;
      path[st][ed] = i;
    }
  }

  return ret;
}

///iterative
for (int i = 1; i <= n; i++) {
  path[i][i] = i;
  dp[i][i] = 0;
}

for (int len = 2; len <= n; len++) {
  for (int st = 1; st + len - 1 <= n; st++) {
    int ed = st + len - 1;
    int L = max(st, path[st][ed - 1]);
    int R = min(ed - 1, path[st + 1][ed]);
    dp[st][ed] = INT_MAX;
    for (int i = L; i <= R; i++) {
      int cur = dp[st][i] + dp[i + 1][ed] + arr[ed] - arr[st - 1];
      if (dp[st][ed] > cur) {
        dp[st][ed] = cur;
        path[st][ed] = i;
      }
    }
  }
}
cout << dp[1][n] << "\n";

int arr[MAX];
int main() {

  fastio;

}