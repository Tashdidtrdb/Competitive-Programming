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

vector<bool>mark(MAX,1);
vector<int>prime;
int siv(){
    int total=0;
    mark[1]=0;
    prime.pb(2);
    total++;
    for(ll i=4; i<MAX; i+=2) mark[i]=0;
    for(ll i=3; i<MAX; i+=2){
        if(mark[i]){
            prime.pb(i);
            total++;
            if(i*i < MAX){
                for(ll j = i*i; j < MAX; j += 2*i){
                    mark[j] = 0;
                }
            }
        }
    }
    return total;
}