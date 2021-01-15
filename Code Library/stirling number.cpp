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

//stirling number 2nd kind variation(number of ways to place n marbles in k boxes so that each box has at least x marbles)
ll solve(int marble, int box) {
  if (marble < 1ll * box * x) return 0;
  if (box == 1 && marble >= x) return 1;
  if (vis[marble][box] == cs) return dp[marble][box];
  vis[marble][box] = cs;

  ll a = ( 1ll * box * solve(marble - 1, box) ) % MOD;
  ll b = ( 1ll * box * ncr(marble - 1, x - 1) ) % MOD;
  b = (b * solve(marble - x, box - 1)) % MOD;
  ll ret = (a + b) % MOD;
  return dp[marble][box] = ret;
}

//number of ways to place n marbles in k boxes so that no box is empty
ll stir(ll n, ll k) {
  ll ret = 0;
  for (int i = 0; i <= k; i++) {
    ll v = ncr(k, i) * bigmod(i, n) % MOD;
    if ( (k - i) % 2 == 0 ) ret = (ret + v) % MOD;
    else ret = (ret - v + MOD) % MOD;
  }
  return ret;
}

int arr[MAX];
int main() {

  fastio;

}