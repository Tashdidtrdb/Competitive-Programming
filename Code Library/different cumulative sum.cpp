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

///cost = sum of (i * a[i]) where i starts from the beginning for every range
///sum[] = prefix sum of value[i]
///isum[] = prefix sum of i*value[i]
ll cost(int i, int j) {
  ll ret = isum[j];
  if (i) ret -= isum[i - 1];
  ll baad = sum[j];
  if (i) baad -= sum[i - 1];
  return ret - i * baad;
}

int arr[MAX];
int main() {

  fastio;

}