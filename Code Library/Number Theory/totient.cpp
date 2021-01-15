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

//totient
vector<bool>mark(5000005, 1);
long long unsigned phi[5000005];
int totient() {
  mark[1] = 0;
  for (int i = 1; i <= 5000000; i++) {
    phi[i] = i;
  }
  for (int i = 2; i <= 5000000; i++) {
    if (mark[i]) {
      for (int j = i; j <= 5000000; j += i) {
        mark[j] = 0;
        phi[j] -= (phi[j] / i);
      }
    }
  }
}

int arr[MAX];
int main() {

  fastio;

}