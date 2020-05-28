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

//rooted tree hash to check isomorphism
mp["01"] = 1;
ind = 1;
int dfs(int u, int p){
    int cnt = 0;
    vector<int>vs;
    for(auto v: g1[u]){
        if(v != p){
            int got = dfs(v,u);
            vs.pb(got);
            cnt++;
        }
    }
    if(!cnt) return 1;

    sort(vs.begin(), vs.end());
    string s = "0";
    for(auto i: vs) s += to_string(i);
    vs.clear();
    s.pb('1');
    if(mp.find(s) == mp.end()) mp[s] = ++ind;
    int ret = mp[s];
    return ret;
}