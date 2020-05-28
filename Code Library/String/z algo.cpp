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

//z algo
int z[MAX];
void calcz(string s){
    int n = s.size();
    int l,r;
    l = r = 0;
    for(int i=1; i<n; i++){
        if(i > r){
            l = r = i;
            while(r < n && s[r] == s[r-l]) r++;
            z[i] = r-l;
            r--;
        }
        else{
            int k = i-l;
            if(z[k] < r-i+1) z[i] = z[k];
            else{
                l = i;
                while(r < n && s[r] == s[r-l]) r++;
                z[i] = r-l;
                r--;
            }
        }
    }
}