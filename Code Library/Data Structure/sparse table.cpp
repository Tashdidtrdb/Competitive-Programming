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

//sparse table min query
int get(int L, int R){
    int len = R-L+1;
    int j = lg[len];
    return min(mn[L][j], mn[R - (1ll << j) + 1][j]);
}

//sparse table range sum query
ll get(int L, int R){
    ll sum = 0;
    for (int j = 25; j >= 0; j--) {
        if ((1ll << j) <= R - L + 1){
            sum += st[L][j];
            L += 1 << j;
        }
    }
    return sum;
}

int main(){

    fastio;
    for(int i=2; i<MAX; i++) lg[i] = lg[i/2] + 1;
    for(int i=0; i<n; i++){
        cin>>arr[i];
        dp[i][0] = arr[i];
    }

    for(int j=1; j<25; j++){
        for(int i=0; i+(1<<j) <= n; i++){
            dp[i][j] = __gcd(dp[i][j-1], dp[ i+(1ll << (j-1)) ][j-1]);
        }
    }
}