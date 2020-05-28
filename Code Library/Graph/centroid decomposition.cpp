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

//centroid decomposition (res[i] contains the sum of numbers of distinct colors in all paths from i)
set<int>g[MAX];
int col[MAX];
int child[MAX];
int used[18][MAX];
ll ans[MAX], res[MAX];
int sz = 0;
int n;
bool vis[MAX];
int uniq = 0;

void dfs(int u, int p){
    sz++;
    child[u] = 1;
    for(auto v: g[u]){
        if(v != p){
            dfs(v,u);
            child[u] += child[v];
        }
    }
}

int get_centroid(int u, int p){
    for(auto v: g[u]){
        if(v != p && child[v] > sz/2) return get_centroid(v, u);
    }
    return u;
}

void add(int u, int p, int depth, int centroid){
    bool check = false;
    child[u] = 1;
    if(!vis[col[u]]){
        uniq++;
        check = true;
        vis[col[u]] = true;
    }
    ans[centroid] += uniq;
    for(auto v: g[u]){
        if(v != p){
            add(v, u, depth, centroid);
            child[u] += child[v];
        }
    }
    if(check){
        uniq--;
        used[depth][col[u]] += child[u];
        vis[col[u]] = false;
    }
}

void del(int u, int p, int depth, int centroid){
    bool check = false;
    if(!vis[col[u]]){
        uniq++;
        used[depth][col[u]] -= child[u];
        vis[col[u]] = true;
        check = true;
    }
    ans[centroid] -= uniq;
    for(auto v: g[u]){
        if(v != p){
            del(v, u, depth, centroid);
        }
    }
    child[u] = 0;
    if(check){
        uniq--;
        vis[col[u]] = false;
    }
}

void solve(int u, int p, int depth, int centroid){
    ans[u] += (ans[p] + child[centroid] - used[depth][col[u]]);
    res[u] += ans[u];
    int temp = used[depth][col[u]];
    used[depth][col[u]] = child[centroid];
    for(auto v: g[u]){
        if(v != p) solve(v, u, depth, centroid);
    }
    ans[u] = 0;
    used[depth][col[u]] = temp;
}

void reset_col(int u, int p, int depth){
    used[depth][col[u]] = 0;
    for(auto v: g[u]){
        if(v != p) reset_col(v, u, depth);
    }
}

void decompose(int u, int depth){
    sz = 0;
    uniq = 0;
    dfs(u,-1);
    int centroid = get_centroid(u,-1);
    reset_col(centroid,-1,depth);
    add(centroid, -1, depth, centroid); ///get ans for centroid and get the number of paths where each color is used
    res[centroid] += ans[centroid];
    uniq++;
    vis[col[centroid]] = true;
    for(auto v: g[centroid]){
        child[centroid] -= child[v];

        ///remove all contribution of the subtree of v
        del(v, centroid, depth, centroid);
        used[depth][col[centroid]] = child[centroid];

        solve(v, centroid, depth, centroid);

        ///add back the contribution of the subtree of v
        add(v, centroid, depth, centroid);
        child[centroid] += child[v];
    }
    uniq--;
    vis[col[centroid]] = false;
    for(auto it = g[centroid].begin(); it != g[centroid].end(); it++){
        g[*it].erase(centroid);
        decompose(*it, depth + 1);
    }
}

int main(){

    fastio;
    cin>>n;
    for(int i=1; i<=n; i++) cin>>col[i];
    for(int i=0; i<n-1; i++){
        int u,v;
        cin>>u>>v;
        g[u].insert(v);
        g[v].insert(u);
    }
    decompose(1,0);
    for(int i=1; i<=n; i++) cout<<res[i]<<"\n";
}