#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define vii vector<int>
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pdd pair<double,double>
#define pldld pair<long long double, long long double>
#define ff first
#define ss second
#define pb push_back
#define read freopen("alu.txt","r",stdin);
#define write freopen("vorta.txt","w",stdout);
#define fastio ios::sync_with_stdio(false); cin.tie(NULL);
#define PI 2*acos(0.0)
#define DEBUG(x) cerr << #x << " = " << x << endl
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int MAX = 1e5 + 5, MOD = 1e9 + 7  , MAXLG = log2(MAX)+1;
const ll inf = 1e18 + 5;

//hld
int arr[MAX];
int n;
vector<int> parent, depth, heavy, head, pos;
int cur_pos, sub[MAX];
int tree[4*MAX];
vii g[MAX];

void update(int now, int L, int R, int idx, int val){
    if(L == R){
        tree[now] = val;
        return;
    }
    int mid = (L + R)/2;
    if(idx <= mid) update(now<<1, L, mid, idx, val);
    else update( (now<<1) | 1, mid+1, R, idx, val);
    tree[now] = tree[now<<1] + tree[(now<<1) | 1];
}

ll segtree_query(int now, int L, int R, int i, int j){
    if(R < i || L > j) return 0;
    if(L >= i && R <= j) return tree[now];
    int mid = (L + R)/2;
    return segtree_query(now<<1, L, mid, i, j) + segtree_query( (now<<1) | 1, mid+1, R, i, j);
}

int dfs(int u) {
    sub[u] = 1;
    int mx_size = 0;
    for (int v : g[u]) {
        if (v != parent[u]) {
            parent[v] = u, depth[v] = depth[u] + 1;
            int v_size = dfs(v);
            sub[u] += v_size;
            if (v_size > mx_size){
                mx_size = v_size;
                heavy[u] = v;
            }
        }
    }
    return sub[u];
}

void decompose(int u, int h) {
    head[u] = h, pos[u] = cur_pos++;
    if (heavy[u] != -1) decompose(heavy[u], h);
    for (int v : g[u]) {
        if (v != parent[u] && v != heavy[u]) decompose(v, v);
    }
}

void init(int n) {
    parent = vector<int>(n, -1);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    cur_pos = 1;

    dfs(1);
    decompose(1, 1);
}

ll query(int a, int b) {
    ll res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) swap(a, b);
        ll cur_heavy_path_res = segtree_query(1, 1, n, pos[head[b]], pos[b]);
        res += cur_heavy_path_res;
    }
    if (depth[a] > depth[b]) swap(a, b);
    ll last_heavy_path_res = segtree_query(1, 1, n, pos[a], pos[b]);
    res += last_heavy_path_res;
    return res;
}