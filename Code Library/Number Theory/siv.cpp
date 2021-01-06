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

const int MAX = 2e5 + 5, MOD = 1e9 + 7  , MAXLG = log2(MAX)+1;
const ll inf = 1e18 + 5;

int N;
vector<bool> mark(N, true);
vector<int> prime;
void siv(){
    prime.pb(2);
    for(int i = 4; i < N; i += 2) mark[i] = false;
    for(ll i = 3; i < N; i += 2){
        if(!mark[i]) continue;
        prime.pb(i);
        for(ll j = i*i; j < N; j += 2*i) mark[j] = false;
    }
}

// linear complexity
const int N;
int spf[N];
vector<int> pr;

void siv(){
    for(int i = 2; i < N; i++){
        if(spf[i] == 0) spf[i] = i, pr.pb(i);
        for(int j = 0; j < pr.size() && pr[j] <= spf[i] && i * pr[j] < N; j++){
            spf[i * pr[j]] = pr[j];
        }
    }
}

vector<int> factorize(int n){
    vector<int> ret;
    while(n > 1){
        int div = spf[n], cnt = 0;
        while( !(n % div) ){
            cnt++;
            n /= div;
        }
        ret.pb(cnt);
    }
    return ret;
}

int arr[MAX];
int main(){

    fastio;
            
}