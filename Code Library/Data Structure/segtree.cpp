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

ll sum[MAX << 2][25];
ll lazy[MAX << 2];

void build(int now, int L, int R){
    if(L == R){
        for(int i=0; i<=20; i++){
            if((1ll << i) & arr[L]) sum[now][i] = 1;
        }
        return;
    }
    int mid = (L + R) >> 1;
    int lft = now << 1, rt = lft | 1;
    build(lft, L, mid);
    build(rt, mid+1, R);
    for(int i=0; i<=20; i++) sum[now][i] = sum[lft][i] + sum[rt][i];
}

void push(int now, int L, int R){
    if(lazy[now]){
        int val = lazy[now];
        for(int i=0; i<=20; i++){
            if((1ll << i) & val) sum[now][i] = (R - L + 1) - sum[now][i];
        }
    }
    if(L != R){
        lazy[(now)<<1] ^= lazy[now];
        lazy[(now<<1) | 1] ^= lazy[now];
    }
    lazy[now] = 0;
}

void update(int now, int L, int R, int i, int j, int val){
    push(now, L, R);
    if(R < i || L > j) return;
    if(L >= i && R <= j){
        for(int i=0; i<=20; i++){
            if((1ll << i) & val) sum[now][i] = (R - L + 1) - sum[now][i];
        }
        if(L != R){
            lazy[(now)<<1] ^= val;
            lazy[(now<<1) | 1] ^= val;
        }
        return;
    }
    int mid = (L + R) >> 1;
    int lft = now << 1, rt = lft | 1;
    update(lft, L, mid, i, j, val);
    update(rt, mid+1, R, i, j, val);
    for(int i=0; i<=20; i++) sum[now][i] = sum[lft][i] + sum[rt][i];
}

ll query(int now, int L, int R, int i, int j){
    push(now, L, R);
    if(R < i || L > j) return 0;
    if(L >= i && R <= j){
        ll ret = 0;
        for(int i=0; i<=20; i++){
            ret += (sum[now][i] * (1ll << i));
        }
        return ret;
    }
    int mid = (L + R) >> 1;
    int lft = now << 1, rt = lft | 1;
    return query(lft, L, mid, i, j) + query(rt, mid+1, R, i, j);
}