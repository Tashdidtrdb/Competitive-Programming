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

ostream& operator << (ostream& os, pll hash) {
  return os << "(" << hash.ff << ", " << hash.ss << ")";
}

pll operator + (pll a, ll x)     {return pll(a.ff + x, a.ss + x);}
pll operator - (pll a, ll x)     {return pll(a.ff - x, a.ss - x);}
pll operator * (pll a, ll x)     {return pll(a.ff * x, a.ss * x);}
pll operator + (pll a, pll x)    {return pll(a.ff + x.ff, a.ss + x.ss);}
pll operator - (pll a, pll x)    {return pll(a.ff - x.ff, a.ss - x.ss);}
pll operator * (pll a, pll x)    {return pll(a.ff * x.ff, a.ss * x.ss);}
pll operator % (pll a, pll m)    {return pll(a.ff % m.ff, a.ss % m.ss);}

pll base(1949313259, 1997293877);
pll mod(2091573227, 2117566807);

pll power (pll a, ll p) {
  if (!p) return pll(1, 1);
  pll ans = power(a, p / 2);
  ans = (ans * ans) % mod;
  if (p % 2) ans = (ans * a) % mod;
  return ans;
}

pll inverse(pll a) {
  return power(a, (mod.ff - 1) * (mod.ss - 1) - 1);
}

pll inv_base = inverse(base);

pll val;
vector<pll> P;

void hash_init(int n) {
  P.resize(n + 1);
  P[0] = pll(1, 1);
  for (int i = 1; i <= n; i++) P[i] = (P[i - 1] * base) % mod;
}

///appends c to string
pll append(pll cur, char c) {
  return (cur * base + c) % mod;
}

///prepends c to string with size k
pll prepend(pll cur, int k, char c) {
  return (P[k] * c + cur) % mod;
}

///replaces the i-th (0-indexed) character from right from a to b;
pll replace(pll cur, int i, char a, char b) {
  cur = (cur + P[i] * (b - a)) % mod;
  return (cur + mod) % mod;
}

///Erases c from the back of the string
pll pop_back(pll hash, char c) {
  return (((hash - c) * inv_base) % mod + mod) % mod;
}

///Erases c from front of the string with size len
pll pop_front(pll hash, int len, char c) {
  return ((hash - P[len - 1] * c) % mod + mod) % mod;
}

///concatenates two strings where length of the right is k
pll concat(pll left, pll right, int k) {
  return (left * P[k] + right) % mod;
}

///Calculates hash of string with size len repeated cnt times
///This is O(log n). For O(1), pre-calculate inverses
pll repeat(pll hash, int len, ll cnt) {
  pll mul = (P[len * cnt] - 1) * inverse(P[len] - 1);
  mul = (mul % mod + mod) % mod;
  pll ret = (hash * mul) % mod;

  if (P[len].ff == 1) ret.ff = hash.ff * cnt;
  if (P[len].ss == 1) ret.ss = hash.ss * cnt;
  return ret;
}

ll get(pll hash) {
  return ( (hash.ff << 32) ^ hash.ss );
}

struct hashlist {
  int len;
  vector<pll> H, R;

  hashlist() {}
  hashlist(string &s) {
    len = (int)s.size();
    hash_init(len);
    H.resize(len + 1, pll(0, 0)), R.resize(len + 2, pll(0, 0));
    for (int i = 1; i <= len; i++) H[i] = (H[i - 1] * base + s[i - 1] + 1007) % mod;
    for (int i = len; i >= 1; i--) R[i] = (R[i + 1] * base + s[i - 1] + 1007) % mod;
  }

  pll range_hash(int l, int r) {
    int len = r - l + 1;
    return ((H[r] - H[l - 1] * P[len]) % mod + mod) % mod;
  }

  pll reverse_hash(int l, int r) {
    int len = r - l + 1;
    return ((R[l] - R[r + 1] * P[len]) % mod + mod) % mod;
  }

  pll concat_range_hash(int l1, int r1, int l2, int r2) {
    int len_2 = r2 - l2 + 1;
    return concat(range_hash(l1, r1), range_hash(l2, r2), len_2);
  }

  pll concat_reverse_hash(int l1, int r1, int l2, int r2) {
    int len_1 = r1 - l1 + 1;
    return concat(reverse_hash(l2, r2), reverse_hash(l1, r1), len_1);
  }
};

int arr[MAX];
int main() {

  fastio;

}