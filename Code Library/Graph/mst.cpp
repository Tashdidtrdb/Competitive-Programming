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

//minimum spanning tree
struct node{
    int u,v;
    int cost;
    bool operator<(const node &n) const{
        return cost < n.cost;
    }
    node(int _u, int _v, int _cost){
        u = _u;
        v = _v;
        cost = _cost;
    }
};

typedef struct node node;
map<string,string>par;
set<string>st;

vector<node>e;
int par[MAX];
int findpar(int r){
    if(par[r] == r) return r;
    par[r] = findpar(par[r]);
    return par[r];
}

ll mst(int n){
    for(int i=0;i<n;i++) par[i] = i;
    sort(e.begin(), e.end());
    int c = 0;
    ll sum = 0;
    for(int i=0; i<e.size(); i++){
        int u = findpar(e[i].u);
        int v = findpar(e[i].v);
        if(u != v){
            par[u] = v;
            sum += e[i].cost;
            c++;
            if(c == n-1) break;
        }
    }

    if(c != n-1) return -1;
    return sum;
}