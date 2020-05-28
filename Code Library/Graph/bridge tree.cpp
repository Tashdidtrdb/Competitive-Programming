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

//bridge tree
vii tree[MAX];
bool vis[MAX];
int d[MAX], low[MAX];
int id[MAX];
int d_t;

struct edge{
    int v, rev;
    edge(){}
    edge(int v, int rev) : v(v), rev(rev){}
};
vector<edge>g[MAX];
vector<bool>is_bridge[MAX];
queue<int>q[MAX];
int comp = 1;

void add_edge(int u, int v){
    edge _u = edge(v,g[v].size());
    edge _v = edge(u,g[u].size());
    g[u].pb(_u);
    g[v].pb(_v);
    is_bridge[u].pb(false);
    is_bridge[v].pb(false);
}

void bridge(int u, int p){
    vis[u] = true;
    d[u] = low[u] = ++d_t;

    for(int i=0;i<g[u].size();i++){
        edge e = g[u][i];
        int v = e.v;
        if(v == p) continue;
        if(!vis[v]){
            bridge(v,u);
            low[u] = min(low[v],low[u]);
            if(low[v] > d[u]){
                is_bridge[u][i] = true;
                is_bridge[v][e.rev] = true;
            }
        }
        else low[u] = min(low[u],d[v]);
    }
}

void make_tree(int node){
    int cur = comp;
    id[node] = cur;
    q[cur].push(node);
    vis[node] = true;
    id[node] = cur;
    while(!q[cur].empty()){
        int u = q[cur].front();
        q[cur].pop();
        for(int i=0; i<g[u].size(); i++){
            edge e = g[u][i];
            int v = e.v;
            if(vis[v]) continue;
            if(is_bridge[u][i]){
                comp++;
                tree[cur].pb(comp);
                tree[comp].pb(cur);
                make_tree(v);
            }
            else{
                q[cur].push(v);
                vis[v] = true;
                id[v] = cur;
            }
        }
    }
}