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

//dp(find number of permutations given string s where ith number > (i+1)th number if s[i] == '>' and vise versa)
ll dp[2][3005];
ll sum[2][3005];
int dir[3005];

int main(){

    fastio;
    int n;
    string s;
    cin>>n>>s;

    s = '#' + s;
    s.pb('<'); ///last element less than the element placed after it

    sum[1][0] = 1;
    int cur = 0;
    for(int baki = 1; baki <= n; baki++){
        if(s[baki] == '<') dp[cur][0] = 0;
        else dp[cur][0] = sum[cur ^ 1][baki - 1];

        for(int small = 1; small <= baki; small++){
            if(s[baki] == '<') dp[cur][small] = sum[cur ^ 1][small - 1];
            else{
                int big = baki - small;
                dp[cur][small] = sum[cur ^ 1][small + big - 1];
                dp[cur][small] -= sum[cur ^ 1][small - 1];
                if(dp[cur][small] < 0) dp[cur][small] += MOD;
            }
        }

        sum[cur][0] = dp[cur][0];
        for(int small = 1; small <= baki; small++){
            sum[cur][small] = (sum[cur][small - 1] + dp[cur][small]);
            if(sum[cur][small] >= MOD) sum[cur][small] -= MOD;
        }
        cur ^= 1;
    }

    ll ans = dp[cur ^ 1][n];
    cout<<ans<<"\n";
}