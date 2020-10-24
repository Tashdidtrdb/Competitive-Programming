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

ll bigmod(ll a, ll b){
    if(!b) return 1 % MOD;
    ll x = bigmod(a, b/2);
    x = ((x % MOD) * (x % MOD)) % MOD;
    if(b & 1) x = ((x % MOD) * (a % MOD)) % MOD;
    return x % MOD;
}

ll invmod(ll a, ll b = MOD){
    return bigmod(a, b-2);
}

ll mulmod(ll a, ll b){
    ll ret = 0;
    a = a % m;
    while(b > 0){
        if(b & 1) ret = (ret + a) % m;
        a = (a * 2) % m;
        b /= 2;
    }
    return (ret % m);
}

ll bigmod ( ll a, ll p, ll m){
    ll res = 1%m;
    ll x = a%m;
    while(p){
        if(p&1) res = (res * x)%m;
        x = (x * x) % m;
        p = p >> 1;
    }
    return res;
}

//precalc fact
void precalc(){
    fact[0] = inv_fact[0] = inv_fact[1] = 1;
    for(int i=1; i<MAX; i++) fact[i] = ((fact[i-1] % MOD) * ((ll)i % MOD)) % MOD;
    for(int i=2; i<MAX; i++) inv_fact[i] = ((inv_fact[i-1] % MOD) * ( invmod((ll)i,MOD)) ) % MOD;
}

ll ncr(ll n, ll r){
    if(n < r) return 0;
    ll ret = fact[n];
    ret = (ret * inv_fact[n-r]) % MOD;
    ret = (ret * inv_fact[r]) % MOD;
    return ret;
}

ll npr(ll n, ll r){
    if(n < r) return 0;
    ll ret = fact[n];
    ret = (ret * inv_fact[n-r]) % MOD;
    return ret;
}