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

//link cut tree
struct Node{
    int L, R, P;
    int PP;
};
Node LCT[MAX_N];
inline void make_tree(int v){
    if (v == -1) return;
    LCT[v].L = LCT[v].R = LCT[v].P = LCT[v].PP = -1;
}

inline void rotate(int v){
    if (v == -1) return;
    if (LCT[v].P == -1) return;
    int p = LCT[v].P;
    int g = LCT[p].P;
    if (LCT[p].L == v){
        LCT[p].L = LCT[v].R;
        if (LCT[v].R != -1){
            LCT[LCT[v].R].P = p;
        }
        LCT[v].R = p;
        LCT[p].P = v;
    }
    else{
        LCT[p].R = LCT[v].L;
        if (LCT[v].L != -1){
            LCT[LCT[v].L].P = p;
        }
        LCT[v].L = p;
        LCT[p].P = v;
    }
    LCT[v].P = g;
    if (g != -1){
        if (LCT[g].L == p){
            LCT[g].L = v;
        }
        else{
            LCT[g].R = v;
        }
    }
    // must preserve path-pointer!
    // (this only has an effect when g is -1)
    LCT[v].PP = LCT[p].PP;
    LCT[p].PP = -1;
}
inline void splay(int v){
    if (v == -1) return;
    while (LCT[v].P != -1){
        int p = LCT[v].P;
        int g = LCT[p].P;
        if (g == -1){ // zig
            rotate(v);
        }
        else if ((LCT[p].L == v) == (LCT[g].L == p)){ // zig-zig
            rotate(p);
            rotate(v);
        }
        else // zig-zag{
            rotate(v);
            rotate(v);
        }
    }
}
inline void expose(int v){
    if (v == -1) return;
    splay(v); // now v is root of its aux. tree
    if (LCT[v].R != -1){
        LCT[LCT[v].R].PP = v;
        LCT[LCT[v].R].P = -1;
        LCT[v].R = -1;
    }
    while (LCT[v].PP != -1){
        int w = LCT[v].PP;
        splay(w);
        if (LCT[w].R != -1){
            LCT[LCT[w].R].PP = w;
            LCT[LCT[w].R].P = -1;
        }
        LCT[w].R = v;
        LCT[v].P = w;
        splay(v);
    }
}

inline int find_root(int v){
    if (v == -1) return -1;
    expose(v);
    int ret = v;
    while (LCT[ret].L != -1) ret = LCT[ret].L;
    expose(ret);
    return ret;
}

inline void link(int v, int w) // attach v's root to w
{
    if (v == -1 || w == -1) return;
    expose(w);
    LCT[v].L = w; // the root can only have right children in its splay tree, so no need to check
    LCT[w].P = v;
    LCT[w].PP = -1;
}
inline void cut(int v){
    if (v == -1) return;
    expose(v);
    if (LCT[v].L != -1){
        LCT[LCT[v].L].P = -1;
        LCT[LCT[v].L].PP = -1;
        LCT[v].L = -1;
    }
}
inline int LCA(int p, int q){
    expose(p);
    splay(q);
    if (LCT[q].R != -1){
        LCT[LCT[q].R].PP = q;
        LCT[LCT[q].R].P = -1;
        LCT[q].R = -1;
    }
    int ret = q, t = q;
    while (LCT[t].PP != -1){
        int w = LCT[t].PP;
        splay(w);
        if (LCT[w].PP == -1) ret = w;
        if (LCT[w].R != -1){
            LCT[LCT[w].R].PP = w;
            LCT[LCT[w].R].P = -1;
        }
        LCT[w].R = t;
        LCT[t].P = w;
        LCT[t].PP = -1;
        t = w;
    }
    splay(q);
    return ret;
}