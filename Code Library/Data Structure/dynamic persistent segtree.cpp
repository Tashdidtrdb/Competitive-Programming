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

struct node{
    int val;
    int lft, rt;
    node(int val = 0, int lft = 0, int rt = 0) : val(val), lft(lft), rt(rt){}
};

node nodes[30*MAX]; ///take at least 2*n*log(n) nodes
int root[MAX];
int sz;

inline int update(int &now, int L, int R, int idx, int val){
    if(L > idx || R < idx) return now;
    if(L == R){
        ++sz;
        nodes[sz] = nodes[now];
        nodes[sz].val += val;
        return sz;
    }
    int mid = (L + R)>>1;

    int ret = ++sz;
    if(idx <= mid){
        if(!nodes[now].lft) nodes[now].lft = ++sz;
        nodes[ret].lft = update(nodes[now].lft, L, mid, idx, val);
        nodes[ret].rt = nodes[now].rt;
    }
    else{
        if(!nodes[now].rt) nodes[now].rt = ++sz;
        nodes[ret].rt = update(nodes[now].rt, mid+1, R, idx, val);
        nodes[ret].lft = nodes[now].lft;
    }

    nodes[ret].val = nodes[ nodes[ret].lft ].val + nodes[ nodes[ret].rt ].val;
    return ret;
}

inline int query(int &now, int L, int R, int i, int j){
    if(L > j || R < i) return 0;
    if(L >= i && R <= j) return nodes[now].val;
    int mid = (L + R)>>1;
    return query(nodes[now].lft, L, mid, i, j) + query(nodes[now].rt, mid+1, R, i, j);
}

///in main(make segtree for every prefix)
root[0] = 0;
for(int i=1; i<=n; i++) root[i] = update(root[i-1], 1, n, p[i], 1);