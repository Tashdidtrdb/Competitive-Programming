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

//aho corasick
struct state{
    int len, par, link, next_lif;
    ll val;
    int next[26];
    char p_char;
    bool lif;
    state(int par = -1, char p_char = '$', int len = 0) : par(par), p_char(p_char), len(len) {
        lif = false;
        link = 0;
        next_lif = 0;
        val = 0;
        memset(next, 0, sizeof next);
    }
};
vector<state>aho;

inline void add_str(const string &s, ll val){
    int now = 0;
    for(int i=0; i<s.size(); i++){
        int c = s[i] - 'a';
        if(!aho[now].next[c]){
            aho[now].next[c] = (int)aho.size();
            aho.emplace_back(now, s[i], aho[now].len + 1);
        }
        now = aho[now].next[c];
    }
    aho[now].lif = true;
    aho[now].val = val;
}

inline void push_link(){
    queue<int>q;
    q.push(0);
    while(!q.empty()){
        int cur = q.front();
        int link = aho[cur].link;
        q.pop();

        aho[cur].next_lif = aho[link].lif ? link : aho[link].next_lif;
        for(int c=0; c<26; c++){
            if(aho[cur].next[c]){
                aho[ aho[cur].next[c] ].link = cur ? aho[link].next[c] : 0;
                q.push( aho[cur].next[c] );
            }
            else aho[cur].next[c] = aho[link].next[c];
        }
    }
}

ll dp[MAX];
///returns sum(val) of all strings ending at given position
ll get_val(int now){
    if(!now) return 0;
    if(dp[now] != -1) return dp[now];
    return dp[now] = aho[now].val + get_val(aho[now].next_lif);
}