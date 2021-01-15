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

//submask == all i such that mask&i == i || mask&i == mask (all i such that all 0 in mask are fixed and the 1's change)
//sos dp memory optimized
for (int i = 0; i < (1 << N); ++i) F[i] = A[i];
for (int i = 0; i < N; ++i) {
  for (int mask = 0; mask < (1 << N); ++mask) {
    if (mask & (1 << i)) F[mask] += F[mask ^ (1 << i)]; /// doing -= can work like inclusion-exclusion on unset bits
  }
}

//sos iterative
for (int mask = 0; mask < (1 << N); ++mask) {
  dp[mask][-1] = A[mask]; //handle base case separately (leaf states)
  for (int i = 0; i < N; ++i) {
    if (mask & (1 << i))
      dp[mask][i] = dp[mask][i - 1] + dp[mask ^ (1 << i)][i - 1];
    else
      dp[mask][i] = dp[mask][i - 1];
  }
  F[mask] = dp[mask][N - 1];
}

// iterate over all the masks
for (int mask = 0; mask < (1 << n); mask++) {
  F[mask] = A[0];
  // iterate over all the subsets of the mask
  for (int i = mask; i > 0; i = (i - 1) & mask) {
    F[mask] += A[i];
  }
}

int arr[MAX];
int main() {

  fastio;

}