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

//lcs
int lcs(string a, string b){

    int n=a.size();
    int m=b.size();
    int dp[n+1][m+1];

    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i==0 || j==0) dp[i][j]=0;
            else if(a[i-1]==b[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }

    return dp[n][m];

}

//count number of palindromic subsequence
ll dp[105][105];
ll cnt_palindrome(string s){

    int n=s.size();
    memset(dp,0,sizeof dp);
    for(int len=1;len<=n;len++){
        for(int i=0;i<n;i++){
            int j=i+len-1;
            if(j>=n) break;
            if(i==j) dp[i][j]=1;
            if(s[i]==s[j]) dp[i][j]=1+dp[i][j-1]+dp[i+1][j];
            else dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
        }
    }

    return dp[0][n-1];

}

//longest palindromic subsequence
int dp[1005][1005];
int longest_palindrome(string s){

    int n=s.size();
    memset(dp,0,sizeof dp);

    for(int len=1;len<=n;len++){
        for(int i=0;i<n;i++){
            int j=i+len-1;
            if(j>=n) break;

            if(i==j) dp[i][j]=1;
            else if(s[i]==s[j]) dp[i][j]=2+dp[i+1][j-1];
            else dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
        }
    }

    return dp[0][n-1];

}

//LIS
int LongestIncreasingSubsequenceLength(std::vector<int>& v){
    if (v.size() == 0)
        return 0;

    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail

    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] > tail[length - 1])
            tail[length++] = v[i];
        else {
            // TO check whether the element is not present before hand
            auto it = find(tail.begin(), tail.begin() + length, v[i]);
            if (it != tail.begin() + length) {
                continue;
            }
            // If not present change the tail element to v[i]
            it = upper_bound(tail.begin(), tail.begin() + length, v[i]);
            *it = v[i];
        }
    }

    return length;
}
