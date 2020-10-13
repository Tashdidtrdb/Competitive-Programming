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
#define eps 1e-11
#define DEBUG(x) cerr << #x << " = " << x << endl
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int MAX = 1e5 + 5, MOD = 1e9 + 7  , MAXLG = log2(MAX)+1;
const ll inf = 1e18 + 5;

/*
    2-Sat Note: Assign true or false values to n variables in order to satisfy
    a system of constraints on pairs of variables.
    E.g: (x1 or !x2) and (x2 or x3) and (!x3 or !x3)

    x1 = true
    x2 = true
    x3 = false
    is a solution to make the above formula true.
    MAX must be equal to the maximum number of variables.
    n passed in init() is the number of variables.
    O(V+E)

    !a is represented as neg(a).
    example xor:
    |a|b|
    |0|0| x or(a,b)
    |0|1|
    |1|0|
    |1|1| x or(!a, !b)
    do OR of negation of values of variables for each undesired situation 
    to make it impossible.
*/

struct two_sat{
    int n, id;
    vector<int> g[2*MAX], rg[2*MAX], order, st;
    bool state[2*MAX], vis[2*MAX];
    int scc[2*MAX];

    void init(int _n){
        n = _n;
        for(int i=0; i<=2*n; i++){
            g[i].clear(), rg[i].clear();
            state[i] = vis[i] = false;
            scc[i] = -1;
        }
        st.clear(), order.clear();
    }

    void add_edge(int u, int v){
        g[u].pb(v);
        rg[v].pb(u);
    }

    void OR(int u, int v){
        add_edge(neg(u), v);
        add_edge(neg(v), u);
    }

    void XOR(int u, int v){
        OR(u,v);
        OR(neg(u), neg(v));
    }

    void ForceTrue(int u){
        add_edge(neg(u), u);
    }

    void ForceFalse(int u){
        add_edge(u, neg(u));
    }

    void imply(int u, int v){
        OR(neg(u), v);
    }

    int neg(int u){
        if(u <= n) return u + n;
        return u - n;
    }

    void dfs(int u, vii g[], bool topsort){
        vis[u] = true;
        for(int v: g[u]){
            if(!vis[v]) dfs(v, g, topsort);
        }
        if(topsort) st.pb(u);
        else scc[u] = id, order.pb(u);
    }

    void build_scc(){
        for(int i = 1; i <= 2*n; i++){
            if(!vis[i]) dfs(i, g, true);
        }
        reverse(st.begin(), st.end());
        fill(vis, vis + 2*n + 1, false);
        for(int u: st){
            if(!vis[u]) id++, dfs(u, rg, false);
        }
    }

    bool solve(){
        build_scc();
        for(int i = 1; i <= n; i++){
            if(scc[i] == scc[i + n]) return false;
        }
        for(int i = (int)order.size() - 1; i >= 0; i--){
            int u = order[i];
            if(state[neg(u)] == false) state[u] = true;
        }
        return true;
    }
} solver;

int main(){

    fastio;
    
}