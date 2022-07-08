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

// fft
struct base {
  double x, y;
  base() { x = y = 0; }
  base(double x, double y): x(x), y(y) { }
};

inline base operator + (base a, base b) { return base(a.x + b.x, a.y + b.y); }
inline base operator - (base a, base b) { return base(a.x - b.x, a.y - b.y); }
inline base operator * (base a, base b) { return base(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline base conj(base a) { return base(a.x, -a.y); }

int lim = 1;
vector<base> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};

void ensure_base(int p) {
  if(p <= lim) return;
  rev.resize(1 << p);
  for(int i = 0; i < (1 << p); i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1)  <<  (p - 1));
  roots.resize(1 << p);
  while(lim < p) {
    double angle = 2 * PI / (1 << (lim + 1));
    for(int i = 1 << (lim - 1); i < (1 << lim); i++) {
      roots[i << 1] = roots[i];
      double angle_i = angle * (2 * i + 1 - (1 << lim));
      roots[(i << 1) + 1] = base(cos(angle_i), sin(angle_i));
    }
    lim++;
  }
}

void fft(vector<base> &a, int n = -1) {
  if(n == -1) n = a.size();
  assert((n & (n - 1)) == 0);
  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = lim - zeros;
  for(int i = 0; i < n; i++) if(i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
  for(int k = 1; k < n; k <<= 1) {
    for(int i = 0; i < n; i += 2 * k) {
      for(int j = 0; j < k; j++) {
        base z = a[i + j + k] * roots[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}

//eq = 0: 4 FFTs in total
//eq = 1: 3 FFTs in total
vector<int> multiply(vector<int> &a, vector<int> &b, int eq = 0) {
  int need = a.size() + b.size() - 1;
  int p = 0;
  while((1 << p) < need) p++;
  ensure_base(p);
  int sz = 1 << p;
  vector<base> A, B;
  if(sz > (int)A.size()) A.resize(sz);
  for(int i = 0; i < (int)a.size(); i++) {
    int x = (a[i] % MOD + MOD) % MOD;
    A[i] = base(x & ((1 << 15) - 1), x >> 15);
  }
  fill(A.begin() + a.size(), A.begin() + sz, base{0, 0});
  fft(A, sz);
  if(sz > (int)B.size()) B.resize(sz);
  if(eq) copy(A.begin(), A.begin() + sz, B.begin());
  else {
    for(int i = 0; i < (int)b.size(); i++) {
      int x = (b[i] % MOD + MOD) % MOD;
      B[i] = base(x & ((1 << 15) - 1), x >> 15);
    }
    fill(B.begin() + b.size(), B.begin() + sz, base{0, 0});
    fft(B, sz);
  }
  double ratio = 0.25 / sz;
  base r2(0,  - 1), r3(ratio, 0), r4(0,  - ratio), r5(0, 1);
  for(int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    base a1 = (A[i] + conj(A[j])), a2 = (A[i] - conj(A[j])) * r2;
    base b1 = (B[i] + conj(B[j])) * r3, b2 = (B[i] - conj(B[j])) * r4;
    if(i != j) {
      base c1 = (A[j] + conj(A[i])), c2 = (A[j] - conj(A[i])) * r2;
      base d1 = (B[j] + conj(B[i])) * r3, d2 = (B[j] - conj(B[i])) * r4;
      A[i] = c1 * d1 + c2 * d2 * r5;
      B[i] = c1 * d2 + c2 * d1;
    }
    A[j] = a1 * b1 + a2 * b2 * r5;
    B[j] = a1 * b2 + a2 * b1;
  }
  fft(A, sz); fft(B, sz);
  vector<int> res(need);
  for(int i = 0; i < need; i++) {
    long long aa = A[i].x + 0.5;
    long long bb = B[i].x + 0.5;
    long long cc = A[i].y + 0.5;
    res[i] = (aa + ((bb % MOD) << 15) + ((cc % MOD) << 30))%MOD;
  }
  return res;
}

vector<bool> fastexpo(vector<bool>v, int p) {
  vector<bool>ret({1});
  while (p > 0) {
    if (p % 2 == 1) ret = multiply(ret, v);
    p = p / 2;
    v = multiply(v, v);
  }
  return ret;
}

// multiply n polynomials using divide and conquer
vector<vector<int>> P;
vector<int> mul(int L, int R) {
  if (L == R) return P[L];
  int mid = (L + R) >> 1;
  vector<int> a = mul(L, mid);
  vector<int> b = mul(mid + 1, R);
  vector<int> ret = multiply(a, b);
  a.clear(); b.clear();
  return ret;
}

// my code for fft
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