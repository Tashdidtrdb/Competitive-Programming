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

//convex hull trick dp optimization
struct line{
    ll m,c;
    line(){}
    line(ll m, ll c) : m(m), c(c){}
};

struct convex_hull_trick{
    vector<line>lines;
    int ptr = 0;
    convex_hull_trick(){}

    bool bad(line a, line b, line c){
        return 1.0 * (c.c - a.c) * (a.m - b.m) < 1.0 * (b.c - a.c) * (a.m - c.m);
    }

    void add(line L){
        int sz = lines.size();
        while(sz >= 2 && bad(lines[sz-2], lines[sz-1], L)){
            lines.pop_back();
            sz--;
        }
        lines.pb(L);
    }

    ll get(int idx, int x){
        return (1ll * lines[idx].m * x + lines[idx].c);
    }

    ll query(int x){
        if(lines.empty()) return 0;
        if(ptr >= lines.size()) ptr = lines.size()-1;
        while(ptr < lines.size() - 1 && get(ptr, x) > get(ptr+1, x)) ptr++;
        return get(ptr, x);
    }
};

ll sum[MAX];
ll dp[MAX];
int main(){

    fastio;
    int t;
    cin>>t;
    while(t--){
        int n,a,b,c;
        cin>>n>>a>>b>>c;
        for(int i=1; i<=n; i++) cin>>sum[i];
        for(int i=1; i<=n; i++) dp[i] = 0, sum[i] += sum[i-1];

        convex_hull_trick cht;
        cht.add( line(0, 0) );

        for(int pos=1; pos<=n; pos++){
            dp[pos] = cht.query(sum[pos]) - 1ll * a * sqr(sum[pos]) - c;
            cht.add( line(2ll * a * sum[pos], dp[pos] - a * sqr(sum[pos])) );
        }
        ll ans = (-1ll * dp[n]);
        ans += (1ll * sum[n] * b);
        cout<<ans<<"\n";
    }
}