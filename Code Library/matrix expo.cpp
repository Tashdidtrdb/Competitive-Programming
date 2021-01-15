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

struct matrix {
  vector<vector<ll>> mat;
  int n, m;
  matrix() {}
  matrix(int n, int m) : n(n), m(m), mat(n) {
    for (int i = 0; i < n; i++) mat[i] = vector<ll>(m);
  }

  void identity() { for (int i = 0; i < n; i++) mat[i][i] = 1; }
  void print() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) cout << mat[i][j] << " ";
      cout << "\n";
    }
  }
  vector<ll> &operator[](int i) {
    return mat[i];
  }
};

// make sure a.m == b.n
matrix operator * (matrix &a, matrix &b) {
  int n = a.n, m = b.m;
  matrix ret(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < a.m; k++) {
        ll val = (1ll * a[i][k] * b[k][j]) % MOD;
        ret[i][j] = (ret[i][j] + val) % MOD;
      }
    }
  }
  return ret;
}

matrix mat_exp(matrix &mat, ll p) {
  int n = mat.n, m = mat.m;
  matrix ret(n, m);
  ret.identity();
  matrix x = mat;

  while (p) {
    if (p & 1) ret = ret * x;
    x = x * x;
    p = p >> 1;
  }
  return ret;
}

int arr[MAX];
int main() {

  fastio;

}