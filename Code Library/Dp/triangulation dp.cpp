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

//triangulation dp(number of ways of triangulation)
struct point{
    ll x, y;
    point(){}
    point(ll x, ll y) : x(x), y(y){}
    point operator - (const point &p) const {
        return point(x - p.x, y - p.y);
    }
};

ll dot(point p, point q){ /// p.q = |p|.|q|.cost(theta)
    return ( (p.x * q.x) + (p.y * q.y) );
}

ll cross(point p, point q){ /// p x q = |p|.|q|.sin(theta)
    ll ret = ( (p.x * q.y) - (p.y * q.x) );
    if(ret < 0) return -1;
    return ( ret > 0 ? 1 : 0);
}

ll dist(point p, point q){
    return dot(p-q, p-q);
}

ll triangleArea(point a, point b, point c){
    ll ret = ( (a.x * b.y) + (b.x * c.y) + (c.x * a.y) ) - ( (a.x * c.y) + (c.x * b.y) + (b.x * a.y) );
    return abs(ret); ///divide by 2 afterwards
}

ll polygonArea(vector<point>&P){
    ll ret = 0;
    int n = (int)P.size();
    for(int i=0; i<n; i++){
        ret += ( (P[i].x * P[(i+1) % n].y) - (P[(i+1) % n].x * P[i].y) );
    }
    return abs(ret);
}

bool pointsCollinear(point a, point b, point c){
    ll triangle = triangleArea(a, b, c);
    if(triangle) return false;
    if(a.x >= min(b.x, c.x) && a.x <= max(b.x, c.x) && a.y >= min(b.y, c.y) && a.y <= max(b.y, c.y)) return true;
    return false;
}

bool linesParallel(point a, point b, point c, point d){
    return abs(cross(b-a, c-d)) == 0;
}

bool linesCollinear(point a, point b, point c, point d){
    return linesParallel(a, b, c, d) && abs(cross(a-b, a-c)) == 0 && abs(cross(c-d, c-a)) == 0;
}

bool linesIntersect(point a, point b, point c, point d){
    if(linesCollinear(a, b, c, d)){
        if( !dist(a,c) || !dist(a,d) || !dist(b,c) || !dist(b,d) ) return true;
        if( dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0) return false;
        return true;
    }

    if(cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
    if(cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
    return true;
}

vector<point>P;
int n;
ll area;

bool possible(int L, int R){
    for(int i=0; i<n; i++){
        if(i == L || i == R) continue;
        if(pointsCollinear(P[i], P[L], P[R])) return false;
    }

    for(int i=0; i<n; i++){
        if(i == L || i == R || (i+1) % n == L || (i+1) % n == R) continue;
        if(linesIntersect(P[L], P[R], P[i], P[(i+1) % n])) return false;
    }

    vector<point>v;
    for(int i=L; i<=R; i++) v.pb(P[i]);
    ll got = polygonArea(v);

    v.clear();
    for(int i=R; v.empty() || i != (L+1) % n ; i = (i+1) % n) v.pb(P[i]);
    got += polygonArea(v);

    return (got == area);
}

bool valid[205][205];
ll dp[205][205];

ll solve(int L, int R){
    if(L + 1 == R) return 1;
    if(dp[L][R] != -1) return dp[L][R];

    ll ret = 0;
    for(int mid=L+1; mid<R; mid++){
        if(valid[L][mid] && valid[mid][R]){
            ///selecting triangle(P[L], P[mid], P[R])
            ll temp = ( solve(L, mid) * solve(mid, R) ) % MOD;
            ret = (ret + temp) % MOD;
        }
    }
    return dp[L][R] = ret;
}

int main(){

    fastio;
    cin>>n;
    for(int i=0; i<n; i++){
        int x,y;
        cin>>x>>y;
        P.pb(point(x,y));
    }

    area = polygonArea(P);
    ///valid if line LR doesn't intersect with any side of the polygon and is not outside the polygon
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(possible(i,j)) valid[i][j] = valid[j][i] = true;
        }
    }

    memset(dp, -1, sizeof dp);
    ll ans = solve(0, n-1);
    cout<<ans<<"\n";
}