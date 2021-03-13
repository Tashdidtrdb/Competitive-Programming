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

int lg[MAX];
int dp[MAX][35];

void init(int n, int arr[]) {
  for (int i = 0; i <= n + 5; i++) lg[i] = lg[i / 2] + 1;
  for (int i = 1; i <= n + 1; i++) dp[i][0] = arr[i];
  for (int j = 1; j < 25; j++) {
    for (int i = 1; i + (1 << j) <= n + 1; i++) {
      dp[i][j] = __gcd(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }
  }
}

int get_min(int L, int R) {
  int len = R - L + 1;
  int p = lg[len];
  return min(dp[L][p], dp[R - (1 << p) + 1][p]);
}

int get_sum(int L, int R) {
  int sum = 0;
  for (int j = 25; j >= 0; j--) {
    if ((1 << j) <= R - L + 1) {
      sum += dp[L][j];
      L += (1 << j);
    }
  }
  return sum;
}

int arr[MAX];
int main() {

  fastio;

}