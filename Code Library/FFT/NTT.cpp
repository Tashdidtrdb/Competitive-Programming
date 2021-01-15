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

// use mulmod everywhere if these large values are used
// const ll mod = 343459944726529;
// const ll root = 285149939879053;
// const ll inv_root = 73746282893527;
// const ll limit = (1ll << 35);

const ll mod = 163577857;
const ll root = 121532577;
const ll inv_root = 100122727;
const ll limit = 1 << 22;

ll mulmod(ll u, ll v, ll m) {
  return ((u * v - (ll)((long double)u / m * v + 1e-8) * m) % m + m) % m; //don't know how tf this works
}

ll bigmod (ll a, ll p, ll m) {
  ll res = 1 % m;
  ll x = a % m;
  while (p) {
    if (p & 1) res = (res * x) % m;
    x = (x * x) % m;
    p = p >> 1;
  }
  return res;
}

void ntt(vector<ll> & a, bool invert) {
  int n = (int)a.size();

  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1) j -= bit;
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    ll wlen = (invert ? inv_root : root);
    for (int i = len; i < limit; i <<= 1) wlen = (wlen * wlen) % mod;
    for (int i = 0; i < n; i += len) {
      ll w = 1;
      for (int j = 0; j < len / 2; ++j) {
        ll u = a[i + j], v = (a[i + j + len / 2] * w) % mod;
        a[i + j] = u + v < mod ? u + v : u + v - mod;
        a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
        w = (w * wlen) % mod;
      }
    }
  }
  if (invert) {
    ll inv_n = bigmod(n, mod - 2, mod);
    for (int i = 0; i < n; ++i) a[i] = (a[i] * inv_n) % mod;
  }
}

vector<ll> Mul(vector<ll>& a, vector<ll>& b) {
  vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < max(a.size(), b.size()))  n <<= 1;
  n <<= 1;
  fa.resize(n), fb.resize(n);

  ntt(fa, false), ntt(fb, false);
  for (int i = 0; i < n; ++i) fa[i] = (fa[i] * fb[i]) % mod;
  ntt(fa, true);

  vector<ll> res;
  res.resize(n);
  for (int i = 0; i < n; ++i) res[i] = fa[i];
  return res;
}

int arr[MAX];
int main() {

  fastio;

}