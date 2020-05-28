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

//Li Chao Tree
struct line{
    ll m, c;
    line(ll m = 0, ll c = 0) : m(m), c(c){}
};

ll calc(line L, ll x){
    return 1ll * L.m * x + L.c;
}

struct node{
    ll m,c;
    line L;
    node *lft, *rt;
    node(ll m = 0, ll c = 0, node *lft = NULL, node *rt = NULL) : L(line(m,c)), lft(lft), rt(rt){}
};

struct LiChao{
    node *root;
    LiChao(){
        root = new node();
    }

    void update(node *now, int L, int R, line newline){
        int mid = L + (R - L)/2;
        line lo = now->L, hi = newline;

        if(calc(lo, L) > calc(hi, L)) swap(lo, hi);
        if(calc(lo, R) <= calc(hi, R)){
            now->L = hi;
            return;
        }

        if(calc(lo, mid) < calc(hi, mid)){
            now->L = hi;
            if(now->rt == NULL) now->rt = new node();
            update(now->rt, mid+1, R, lo);
        }
        else{
            now->L = lo;
            if(now->lft == NULL) now->lft = new node();
            update(now->lft, L, mid, hi);
        }
    }

    ll query(node *now, int L, int R, ll x){
        if(now == NULL) return -inf;
        int mid = L + (R - L)/2;

        if(x <= mid) return max( calc(now->L, x), query(now->lft, L, mid, x) );
        else return max( calc(now->L, x), query(now->rt, mid+1, R, x) );
    }
};