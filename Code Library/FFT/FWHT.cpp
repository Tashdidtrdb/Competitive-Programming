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
#define eps 1e-11
#define DEBUG(x) cerr << #x << " = " << x << endl
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int MAX = 1e5 + 5, MOD = 1e9 + 7  , MAXLG = log2(MAX)+1;
const ll inf = 1e18 + 5;

/****************************
Hadamard Matrix - 
1. For XOR-Convolution - 
H = H_inverse = {{1, 1}, {1, -1}} 

2.For AND-Convolution - 
H         = {{0, 1}, {1, 1}} 
H_inverse = {{-1, 1}, {1, 0}}

3. For OR-Convolution - 
H         = {{1, 1}, {1, 0}} 
H_inverse = {{0, 1}, {1, -1}}
***************************/

ll bigmod (ll a, ll p, ll m) {
    ll res = 1 % m;
    ll x = a % m;
    while(p){
        if(p & 1) res = (res * x) % m;
        x = (x * x) % m;
        p = p >> 1;
    }
    return res;
}

void fwht(vector<ll>& p, bool invert) {
    int n = (int)p.size();
    for(ll len = 1; 2 * len <= n; len <<= 1) {
        for(ll i = 0; i < n; i += 2 * len) {
            for(ll j = 0; j < len; j++) {
                ll u = p[i + j], v = p[i + j + len];
                if(invert) {

                }
                else {

                }
            }
        }
    }
    // only for xor
    if(invert) {
        ll inv_n = bigmod(n, MOD-2, MOD);
        for(int i = 0; i < n; i++) {
            p[i] = (p[i] * inv_n) % MOD;
        }
    }
}

int main(){

    fastio;
    
}