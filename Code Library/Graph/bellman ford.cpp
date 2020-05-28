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

//bellman ford
int b[MAX],dis[MAX];
int n,m;
vii u,v,cost;

bool bellman(){
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            if(dis[v[j]] > dis[u[j]] + cost[j]){
                dis[v[j]] = dis[u[j]] + cost[j];
            }
        }
    }
    for(int j=0; j<m; j++){
        if(dis[v[j]] > dis[u[j]] + cost[j]){
            return false;
        }
    }

    return true;
}

void initialize(){
    for(int i=0;i<MAX;i++){
        dis[i]=100000000;
        b[i]=0;
    }
    dis[1]=0;
    u.clear();
    v.clear();
    cost.clear();
}

int main(){

    int t,caseno=0;
    scanf("%d",&t);
    while(t--){
       initialize();
       scanf("%d",&n);
       for(int i=1;i<=n;i++) scanf("%d",&b[i]);
       scanf("%d",&m);
       for(int i=0;i<m;i++){
            int c,d;
            scanf("%d %d",&c,&d);
            int w=(b[d]-b[c]);
            u.push_back(c);
            v.push_back(d);
            cost.push_back(w*w*w);
       }

       int q;
       scanf("%d",&q);
       printf("Case %d:\n",++caseno);
       bellman();
    }
}