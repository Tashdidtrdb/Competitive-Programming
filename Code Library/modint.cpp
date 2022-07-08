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

template <const int64_t mod>
struct modint {
  int64_t value;
  modint() = default;
  modint(int64_t value_) : value(value_) {}
  inline modint<mod> operator + (modint<mod> other) const { int64_t c = this->value + other.value; return modint<mod>(c >= mod ? c - mod : c); }
  inline modint<mod> operator - (modint<mod> other) const { int64_t c = this->value - other.value; return modint<mod>(c <    0 ? c + mod : c); }
  inline modint<mod> operator * (modint<mod> other) const { int64_t c = (int64_t)this->value * other.value % mod; return modint<mod>(c < 0 ? c + MOD : c); }
  inline modint<mod> & operator += (modint<mod> other) { this->value += other.value; if (this->value >= mod) this->value -= mod; return *this; }
  inline modint<mod> & operator -= (modint<mod> other) { this->value -= other.value; if (this->value <    0) this->value += mod; return *this; }
  inline modint<mod> & operator *= (modint<mod> other) { this->value = (int64_t)this->value * other.value % mod; if (this->value < 0) this->value += MOD; return *this; }
  inline modint<mod> operator - () const { return modint<mod>(this->value ? mod - this->value : 0); }
  modint<mod> pow(uint64_t k) const { modint<mod> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
  modint<mod> inv() const { return pow(mod - 2); }  // mod must be a prime
  inline modint<mod> operator /  (modint<mod> other) const { return *this *  other.inv(); }
  inline modint<mod> operator /= (modint<mod> other)       { return *this *= other.inv(); }
  inline bool operator == (modint<mod> other) const { return value == other.value; }
  inline bool operator != (modint<mod> other) const { return value != other.value; }
  inline bool operator < (modint<mod> other) const { return value < other.value; }
  inline bool operator > (modint<mod> other) const { return value > other.value; }
};
template <int64_t mod> modint<mod> operator * (int64_t value, modint<mod> n) { return modint<mod>(value) * n; }
template <int64_t mod> modint<mod> operator * (int32_t value, modint<mod> n) { return modint<mod>(value % mod) * n; }
template <int64_t mod> istream & operator >> (istream & in, modint<mod> &n) { return in >> n.value; }
template <int64_t mod> ostream & operator << (ostream & out, modint<mod> n) { return out << n.value; }

using mint = modint<MOD>;

int arr[MAX];
int main() {

  fastio;
  
}