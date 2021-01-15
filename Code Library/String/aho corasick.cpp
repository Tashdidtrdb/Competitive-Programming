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

//aho corasick
struct state {
  int len, par, link, next_lif;
  ll val;
  int next[26];
  char p_char;
  bool lif;
  state(int par = -1, char p_char = '$', int len = 0) : par(par), p_char(p_char), len(len) {
    lif = false;
    link = 0;
    next_lif = 0;
    val = 0;
    memset(next, 0, sizeof next);
  }
};
vector<state>aho;

inline void add_str(const string &s, ll val) {
  int now = 0;
  for (int i = 0; i < s.size(); i++) {
    int c = s[i] - 'a';
    if (!aho[now].next[c]) {
      aho[now].next[c] = (int)aho.size();
      aho.emplace_back(now, s[i], aho[now].len + 1);
    }
    now = aho[now].next[c];
  }
  aho[now].lif = true;
  aho[now].val = val;
}

inline void push_link() {
  queue<int>q;
  q.push(0);
  while (!q.empty()) {
    int cur = q.front();
    int link = aho[cur].link;
    q.pop();

    aho[cur].next_lif = aho[link].lif ? link : aho[link].next_lif;
    for (int c = 0; c < 26; c++) {
      if (aho[cur].next[c]) {
        aho[ aho[cur].next[c] ].link = cur ? aho[link].next[c] : 0;
        q.push( aho[cur].next[c] );
      } else aho[cur].next[c] = aho[link].next[c];
    }
    aho[cur].val += aho[link].val;
  }
}

inline int count(string &s) {
  int now = 0, ret = 0;
  for (int i = 0; i < s.size(); i++) {
    now = aho[now].next[s[i] - 'a'];
    ret += aho[now].val;
  }
  return ret;
}

struct dynamic_aho {
  aho_corasick ac[20];
  vector<string> dict[20];
  dynamic_aho() {
    for (int i = 0; i < 20; i++) {
      ac[i].aho.clear();
      dict[i].clear();
    }
  }

  void add_str(string &s) {
    int idx = 0;
    for (; idx < 20 && !ac[idx].aho.empty(); idx++) {}

    ac[idx] = aho_corasick();
    ac[idx].add_str(s, 1), dict[idx].pb(s);
    for (int i = 0; i < idx; i++) {
      for (string x : dict[i]) {
        ac[idx].add_str(x, 1);
        dict[idx].pb(x);
      }
      ac[i].aho.clear(), dict[i].clear();
    }
    ac[idx].push_link();
  }

  inline int count(string &s) {
    int ret = 0;
    for (int i = 0; i < 20; i++) {
      if (!ac[i].aho.empty()) ret += ac[i].count(s);
    }
    return ret;
  }
};

int arr[MAX];
int main() {

  fastio;
  dynamic_aho add, del;
  int m;
  cin >> m;
  while (m--) {
    int type;
    string s;
    cin >> type >> s;
    if (type == 1) add.add_str(s);
    else if (type == 2) del.add_str(s);
    else cout << add.count(s) - del.count(s) << "\n" << flush;
  }
}