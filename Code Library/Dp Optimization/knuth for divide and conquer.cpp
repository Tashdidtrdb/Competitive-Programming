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

///knuth for divide and conquer
int solve(int group, int pos) {
  if (!pos) return dp[group][pos] = 0;
  if (!group) return dp[group][pos] = INT_MAX;

  int &ret = dp[group][pos];
  if (ret != -1) return ret;

  int L = 1, R = pos;
  if (pos - 1 > 0) {
    solve(group, pos - 1);
    L = max(L, path[group][pos - 1]);
  }
  if (group + 1 <= m) {
    solve(group + 1, pos);
    R = min(R, path[group + 1][pos]);
  }

  ret = INT_MAX;
  for (int i = L; i <= R; i++) {
    int cur = solve(group - 1, i - 1) + 1ll * (arr[pos] - arr[i]) * (arr[pos] - arr[i]);
    if (cur < ret) {
      ret = cur;
      path[group][pos] = i;
    }
  }

  return ret;
}

int arr[MAX];
int main() {

  fastio;

}