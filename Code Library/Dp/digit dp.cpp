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

//digit dp(find minimum number S so that A <= S <= B and binary(P) is a subtstring of binary(S))
ll dp[55][55][2][2];
int vis[55][55][2][2];

ll solve(int pos, int matched, bool boro, bool choto){
    if(pos >= n){
        if(matched >= pBin.size()) return toDec(res);
        return inf;
    }
    if(vis[pos][matched][boro][choto] == cs) return dp[pos][matched][boro][choto];
    vis[pos][matched][boro][choto] = cs;

    int st = boro ? 0 : aBin[pos]; ///boro == true if value is already greater than A
    int ed = choto ? 1 : bBin[pos]; ///choto == true if value is already less that B

    ll ret = inf;
    for(int i=st; i <= ed; i++){
        res.pb(i);
        int curMatch = matched;
        if(curMatch < pBin.size()){
            if(pBin[curMatch] == i) curMatch++;
            else curMatch = 0;
        }
        else curMatch++;

        ret = min(ret, solve(pos+1, curMatch, boro | (i > aBin[pos]), choto | (i < bBin[pos])) );
        ret = min(ret, solve(pos+1, 0, boro | (i > aBin[pos]), choto | (i < bBin[pos])) );
        res.pop_back();
    }
    return dp[pos][matched][boro][choto] = ret;
}