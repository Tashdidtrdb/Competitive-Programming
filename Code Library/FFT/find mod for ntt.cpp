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

ll mulmod(ll u, ll v, ll m) {
  return ((u * v - (ll)((long double)u / m * v + 1e-8) * m) % m + m) % m; //don't know how tf this works
}

ll bigmod (ll a, ll p, ll m) {
  ll res = 1 % m;
  ll x = a % m;
  while (p) {
    if (p & 1) res = mulmod(res, x, m);
    x = mulmod(x, x, m);
    p = p >> 1;
  }
  return res;
}

ll generator (ll p) {
  vector<ll> fact;
  ll phi = p - 1,  n = phi;
  for (ll i = 2; i * i <= n; ++i)
    if (n % i == 0) {
      fact.push_back (i);
      while (n % i == 0)
        n /= i;
    }
  if (n > 1)
    fact.push_back (n);

  for (ll res = 2; res <= p; ++res) {
    bool ok = true;
    for (size_t i = 0; i < fact.size() && ok; ++i)
      ok &= bigmod (res, phi / fact[i], p) != 1;
    if (ok)  return res;
  }
  return -1;
}

bool miller_rabin(ll n, ll b) {
  ll m = n - 1, cnt = 0;
  while (m % 2 == 0) m >>= 1, ++cnt;
  ll ret = bigmod(b, m, n);
  if (ret == 1 || ret == n - 1) return true;
  while (cnt > 0) {
    ret = mulmod(ret, ret, n);
    if (ret == n - 1) return true;
    --cnt;
  } return false;
}
bool ptest(ll n) { // miller-rabin primality test
  if (n < 2) return false;
  if (n < 4) return true;
  const int BASIC[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
  for (int i = 0; i < 12 && BASIC[i] < n; ++i)
    if (!miller_rabin(n, BASIC[i])) return false;
  return true;
}

void get_mod() {
  // need to find mod = c * 2^k + 1 where mod is a prime
  // then find a generator g of mod, then root = g^k
  ll limit = (1ll << 35); // k = 35
  ll mod = -1, k = -1;
  int times = 100000;
  for (ll i = 1; times-- ; i++) {
    ll val = (limit * i) + 1;
    if (!ptest(val)) continue;
    if (val > inf || val < 0) break;
    mod = val;
    k = i;
  }
  cout << mod << "\n";
  ll g = generator(mod);
  ll root = bigmod(g, k, mod);
  ll inv_root = bigmod(root, mod - 2, mod);
  cout << root << "\n";
  cout << inv_root << "\n";
}

void find_roots(ll mod) {
  if (!ptest(mod)) {
    cout << -1 << "\n";
    return;
  }
  ll p = 2, k = 1;
  ll root = -1, inv_root = -1;
  for ( ; p <= mod; p <<= 1, k++) {
    if ( !((mod - 1) % p) ) {
      ll c = (mod - 1) / p;
      cout << c << " * " << 2 << " ^ " << k << " = " << p << "\n";
      ll g = generator(mod);
      if (g == -1) continue;
      ll root = bigmod(g, k, mod);
      ll inv_root = bigmod(root, mod - 2, mod);
      cout << "root = " << root << "\n";
      cout << "inv_root = " << inv_root << "\n";

      cout << "\n";
    }
  }
}

int arr[MAX];
int main() {

  fastio;

}