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

//trie(find number of a[i] in trie such that present a[i] xor p < l)
int trie[30*100000 + 5][2];
int mark[30*100000 + 5];

int node = 1;
void add(int n){
    int now = 1;
    for(int i=27; i>=0; i--){
        int d = (bool)(n & (1<<i));
        if(!trie[now][d]) trie[now][d] = ++node;
        now = trie[now][d];
        mark[now]++;
    }
}

void del(int n){
    int now = 1;
    deque<int>v;
    for(int i=27; i>=0; i--){
        int d = (bool)(n & (1<<i));
        if(trie[now][d]){
            v.push_front(now);
            now = trie[now][d];
            mark[now]--;
        }
    }
    v.push_front(now);
    for(int i=1; i<v.size(); i++){
        if(!mark[v[i-1]]){
            if(trie[v[i]][0] == v[i-1]) trie[v[i]][0] = 0;
            if(trie[v[i]][1] == v[i-1]) trie[v[i]][1] = 0;
        }
    }
}

int solve(int now, int pos, int p, int l){
    if(pos<0) return 0;
    int p_b=(bool)(p & (1<<pos));
    int l_b=(bool)(l & (1<<pos));
    int ret=0;
    if(!p_b && l_b){
        ret+=mark[trie[now][0]];
        if(trie[now][1]) ret+=solve(trie[now][1],pos-1,p,l);
    }
    if(p_b && l_b){
        ret+=mark[trie[now][1]];
        if(trie[now][0]) ret+=solve(trie[now][0],pos-1,p,l);
    }
    if(!p_b && !l_b) if(trie[now][0]) ret+=solve(trie[now][0],pos-1,p,l);
    if(p_b && !l_b) if(trie[now][1]) ret+=solve(trie[now][1],pos-1,p,l);
    return ret;
}