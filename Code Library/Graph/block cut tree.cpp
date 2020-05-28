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

//block cut tree
bool ap[MAX];
int id[MAX], koyta[MAX];
int d[MAX], low[MAX];
bool vis[MAX];
vii g[MAX], tree[MAX];
int d_t;
stack<int>st;
vector<vector<int>>comp;

void articulation(int u, int p){
    vis[u] = true;
    d[u] = low[u] = ++d_t;
    int child = 0;
    st.push(u);
    for(int v: g[u]){
        if(v == p) continue;
        if(!vis[v]){
            child++;
            articulation(v,u);
            low[u] = min(low[u],low[v]);
            if(p == -1 && child > 1) ap[u] = true;
            if(low[v] >= d[u]){
                if(p != -1) ap[u] = true;
                comp.pb({u});
                int top;
                do{
                    top = st.top();
                    st.pop();
                    comp.back().pb(top);
                } while(top != v);
            }
        }
        else low[u] = min(low[u],d[v]);
    }
}

int node = 0;
void make_tree(int n){
    for(int i=1; i<=n; i++){
        if(ap[i]) id[i] = ++node;
    }
    for(int i=0; i<comp.size(); i++){
        ++node;
        int cnt = 0;
        for(int u: comp[i]){
            if(ap[u]) tree[node].pb(id[u]), tree[id[u]].pb(node), koyta[id[u]] = 1;
            else id[u] = node, cnt++;
        }
        koyta[node] = cnt;
    }
}