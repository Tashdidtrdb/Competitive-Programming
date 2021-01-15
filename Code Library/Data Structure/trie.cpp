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

//trie(find number of a[i] in trie such that present a[i] xor p < l)
int trie[30 * 100000 + 5][2];
int mark[30 * 100000 + 5];

int node = 1;
void add(int n) {
  int now = 1;
  for (int i = 27; i >= 0; i--) {
    int d = (bool)(n & (1 << i));
    if (!trie[now][d]) trie[now][d] = ++node;
    now = trie[now][d];
    mark[now]++;
  }
}

void del(int n) {
  int now = 1;
  deque<int>v;
  for (int i = 27; i >= 0; i--) {
    int d = (bool)(n & (1 << i));
    if (trie[now][d]) {
      v.push_front(now);
      now = trie[now][d];
      mark[now]--;
    }
  }
  v.push_front(now);
  for (int i = 1; i < v.size(); i++) {
    if (!mark[v[i - 1]]) {
      if (trie[v[i]][0] == v[i - 1]) trie[v[i]][0] = 0;
      if (trie[v[i]][1] == v[i - 1]) trie[v[i]][1] = 0;
    }
  }
}

int solve(int now, int pos, int p, int l) {
  if (pos < 0) return 0;
  int p_b = (bool)(p & (1 << pos));
  int l_b = (bool)(l & (1 << pos));
  int ret = 0;
  if (!p_b && l_b) {
    ret += mark[trie[now][0]];
    if (trie[now][1]) ret += solve(trie[now][1], pos - 1, p, l);
  }
  if (p_b && l_b) {
    ret += mark[trie[now][1]];
    if (trie[now][0]) ret += solve(trie[now][0], pos - 1, p, l);
  }
  if (!p_b && !l_b) if (trie[now][0]) ret += solve(trie[now][0], pos - 1, p, l);
  if (p_b && !l_b) if (trie[now][1]) ret += solve(trie[now][1], pos - 1, p, l);
  return ret;
}

// get lexicographically smallest string with given prefix
struct node {
  int next[26];
  int lft, mn;
  int lif;
  node() {
    memset(next, 0, sizeof next);
    lft = 100, mn = -1;
    lif = -1;
  }
};

vector<node> trie;
vector<string> dict;

void add(string &s) {
  int now = 0;
  vector<pii> v;
  for (int i = 0; i < s.size(); i++) {
    int c = s[i] - 'a';
    if (!trie[now].next[c]) {
      trie[now].next[c] = (int)trie.size();
      trie.emplace_back();
    }
    v.pb({now, c});
    now = trie[now].next[c];
  }
  v.pb({now, -1});

  if (trie[now].lif != -1) return;
  trie[now].lif = (int)dict.size();
  dict.pb(s);

  for (int i = (int)v.size() - 1; i >= 0; i--) {
    int cur = v[i].ff, c = v[i].ss;
    if (trie[cur].lif != -1) now = cur, c = -1;
    else if (trie[cur].lft < c) break;
    trie[cur].lft = c;
    trie[cur].mn = now;
  }
}

int query(string &s) {
  int now = 0;
  for (int i = 0; i < s.size(); i++) {
    int c = s[i] - 'a';
    if (!trie[now].next[c]) return -1;
    now = trie[now].next[c];
  }
  return trie[now].mn;
}

int arr[MAX];
int main() {

  fastio;

}