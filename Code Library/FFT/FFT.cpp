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

//fft
typedef complex<double> base;

void fft(vector<base> & a, bool invert) {
  int n = (int)a.size();

  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1) j -= bit;
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : 1);
    base wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      base w(1);
      for (int j = 0; j < len / 2; ++j) {
        base u = a[i + j], v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if (invert) for (int i = 0; i < n; ++i) a[i] /= n;
}

vector<ll> Mul(vector<ll>& a, vector<ll>& b) {
  vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < max(a.size(), b.size()))  n <<= 1;
  n <<= 1;
  fa.resize(n), fb.resize(n);

  fft(fa, false), fft(fb, false);
  for (int i = 0; i < n; ++i) fa[i] *= fb[i];
  fft(fa, true);

  vector<ll> res;
  res.resize(n);
  for (int i = 0; i < n; ++i) res[i] = round(fa[i].real());
  return res;
}

// need to add modulo to res[i] in Mul
vector<ll> Mul_mod(vector<ll>& a, vector<ll>& b, ll mod) {
  ll sqrt_mod = (ll)sqrtl(mod);
  vector<ll> a0(a.size()), a1(a.size());
  vector<ll> b0(b.size()), b1(b.size());
  for (int i = 0; i < a.size(); i++) {
    a0[i] = a[i] % sqrt_mod;
    a1[i] = a[i] / sqrt_mod;
  }
  for (int i = 0; i < b.size(); i++) {
    b0[i] = b[i] % sqrt_mod;
    b1[i] = b[i] / sqrt_mod;
  }

  vector<ll> a01(a.size()), b01(b.size());
  for (int i = 0; i < a.size(); i++) {
    a01[i] = a0[i] + a1[i];
    if (a01[i] >= mod) a01[i] -= mod;
  }
  for (int i = 0; i < b.size(); i++) {
    b01[i] = b0[i] + b1[i];
    if (b01[i] >= mod) b01[i] -= mod;
  }

  vector<ll> mid = Mul(a01, b01);
  vector<ll> a0b0 = Mul(a0, b0);
  vector<ll> a1b1 = Mul(a1, b1);
  for (int i = 0; i < mid.size(); i++) {
    mid[i] = (mid[i] - a0b0[i] + mod) % mod;
    mid[i] = (mid[i] - a1b1[i] + mod) % mod;
  }
  vector<ll> res = a0b0;
  for (int i = 0; i < res.size(); i++) {
    res[i] += (sqrt_mod * mid[i]) % mod;
    if (res[i] >= mod) res[i] -= mod;
  }
  sqrt_mod = (sqrt_mod * sqrt_mod) % mod;
  for (int i = 0; i < res.size(); i++) {
    res[i] += (sqrt_mod * a1b1[i]) % mod;
    if (res[i] >= mod) res[i] -= mod;
  }
  return res;
}

vector<bool> fastexpo(vector<bool>v, int p) {
  vector<bool>ret({1});
  while (p > 0) {
    if (p % 2 == 1) ret = Mul(ret, v);
    p = p / 2;
    v = Mul(v, v);
  }
  return ret;
}

///multiplying with sign
vector<int> multiply(string a, string b) {
  vector<int>v1, v2;

  int sign = 0;
  if (a[0] == '-') {
    sign = 1 - sign;
    a.erase(a.begin());
  }
  if (b[0] == '-') {
    sign = 1 - sign;
    b.erase(b.begin());
  }
  for (int i = 0; i < a.size(); i++) {
    int d = a[i] - '0';
    v1.push_back(d);
  }
  for (int i = 0; i < b.size(); i++) {
    int d = b[i] - '0';
    v2.push_back(d);
  }

  reverse(v1.begin(), v1.end());
  reverse(v2.begin(), v2.end());

  vector<int>v = Mul(v1, v2);

  int carry = 0;
  vector<int>res;
  for (int i = 0; i < v.size(); i++) {
    int temp = v[i];
    temp += carry;
    res.push_back(temp % 10);
    carry = temp / 10;
  }
  while (res.size() > 1 and res.back() == 0) res.pop_back();
  reverse(ans.begin(), ans.end());
  return res;
}

int mark[1005];
int arr[MAX];
int main() {
  int n , k;
  cin >> n >> k;
  vector<bool>v;
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c;
    mark[c] = 1;
  }
  for (int i = 0; i <= 1000; i++) v.push_back(mark[i]);
  vector<bool>ret = fastexpo(v, k);
  for (int i = 0; i < ret.size(); i++) if (ret[i] > 0) cout << i << ' ';
}