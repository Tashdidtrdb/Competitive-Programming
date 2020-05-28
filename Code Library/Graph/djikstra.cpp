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

//djikstra
void djikstra(int s){
    for(int i=0; i<MAX; i++) dis[i] = INT_MAX;
    priority_queue< pii, vector<pii>, greater<pii> > q;

    dis[s] = 0;
    q.push(pii(dis[s],s));
    while(!q.empty()){
        pii u = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int i=0; i<g[u.ss].size(); i++){
            int v = g[u.ss][i].ff;
            int cost = g[u.ss][i].ss;
            if(dis[v] > dis[u.ss] + cost){
                dis[v] = dis[u.ss] + cost;
                q.push(pii(dis[v], v));
            }
        }
    }
}

//second shortest path
bool vis[MAX];
int dis_1[MAX], dis_n[MAX];
vector<pii>graph[MAX];

int main(){

    int t,caseno=0;
    scanf("%d",&t);
    while(t--){
        for(int i=0;i<MAX;i++) graph[i].clear();
        int n,r;
        scanf("%d %d",&n,&r);
        while(r--){
            int u,v,cost;
            scanf("%d %d %d",&u,&v,&cost);
            graph[u].push_back(pii(v,cost));
            graph[v].push_back(pii(u,cost));
        }

        djikstra(1,dis_1);
        int shortest=dis_1[n],second_shortest=INT_MAX;
        djikstra(n,dis_n);

        for(int i=1;i<=n;i++){
            for(int j=0;j<graph[i].size();j++){
                int node=graph[i][j].ff;
                int cost=graph[i][j].ss;
                int a=dis_1[i]+dis_n[node]+cost;
                int b=dis_1[i]+dis_n[i]+2*cost;
                if(a>shortest) second_shortest=min(a,second_shortest);
                if(b>shortest) second_shortest=min(b,second_shortest);
            }
        }

        printf("Case %d: %lli\n",++caseno,second_shortest);
    }
}