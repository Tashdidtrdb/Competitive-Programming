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

//Delete pashapashi equal elements from list (delete korar por dui pash theke abar pashapashi equal hoile oigulao delete) O(n)
list<int>::iterator porer,ager;
porer=ager=l.begin();
porer++;
while(porer!=l.end()){
    if(*porer==*ager){
        if(l.size()==2) cout<<"sob element equal chhilo"
        if(ager==l.begin()){
            porer++;
            l.erase(ager,porer);
            ager=porer;
            porer++;
        }
        else{
            porer++;
            l.erase(ager,porer);
            if(porer==l.end()) break;
            ager=porer;
            ager--;
        }
    }
    else{
        porer++;
        ager++;
    }
}