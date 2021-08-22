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

bool ap[MAX];
int id[MAX], koyta[MAX];
int d[MAX], low[MAX];
bool vis[MAX];
vector<int> g[MAX], tree[MAX];
int d_t; stack<int>st;
vector<vector<int>>comp;
// vector<pii> bridges;

void articulation(int u, int p) {
  vis[u] = true;
  d[u] = low[u] = ++d_t;
  int child = 0; st.push(u);
  for (int v : g[u]) {
    if (v == p) continue;
    if (!vis[v]) {
      child++; articulation(v, u);
      low[u] = min(low[u], low[v]);
      if (p == -1 && child > 1) ap[u] = true;
      if (low[v] >= d[u]) { /// > for bridge
        // bridges.pb({u,v});
        if (p != -1) ap[u] = true;
        comp.pb({u}); int top;
        do {
          top = st.top(); st.pop();
          comp.back().pb(top);
        } while (top != v);
      }
    } else low[u] = min(low[u], d[v]);
  }
  /// for bridge component
  // if (p == -1) {
  //   comp.pb({});
  //   while (!st.empty()) {
  //     comp.back().pb(st.top());
  //     st.pop();
  //   }
  // }
}

// block cut tree
int node = 0;
void make_tree(int n) {
  for (int i = 1; i <= n; i++) {
    if (ap[i]) id[i] = ++node;
  }
  for (int i = 0; i < comp.size(); i++) {
    ++node;
    int cnt = 0;
    for (int u : comp[i]) {
      if (ap[u]) tree[node].pb(id[u]), tree[id[u]].pb(node), koyta[id[u]] = 1;
      else id[u] = node, cnt++;
    }
    koyta[node] = cnt;
  }
}

// bridge tree
int node = 0;
void make_tree() {
  for (int i = 0; i < comp.size(); i++) {
    ++node;
    for (int u : comp[i]) id[u] = node;
  }
  for (pii p : bridges) {
    int u = p.ff, v = p.ss;
    if (id[u] != id[v]) {
      tree[id[u]].pb(id[v]);
      tree[id[v]].pb(id[u]);
    }
  }
}

int arr[MAX];
int main() {

  fastio;

}