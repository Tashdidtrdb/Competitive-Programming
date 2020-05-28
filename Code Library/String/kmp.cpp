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

//KMP
int failure[MAX];
void make_failure(string pattern){
    int i = 0,j = -1;
    failure[0] = -1;
    int lens = pattern.size();
    while(i < lens){
        while(j >= 0 && pattern[i] != pattern[j]) j = failure[j];
        i++;
        j++;
        failure[i] = j;
    }
}

int kmp(string s, string pattern){
    int i = 0, j = 0, cnt = 0, start = 0;
    int lens = s.size();
    int lenp = pattern.size();
    while(i < lens){
        while(j >= 0 && s[i] != pattern[j]) j = failure[j];
        i++;
        j++;
        if(j == lenp){
            cnt++;
            j = failure[j];
        }
    }
    return cnt;
}


int main(){

    fastio;
    int n,k;
    cin>>n>>k;
    while(n--){
        string a,b;
        cin>>a>>b;
        if(k>a.size() || k>b.size()){
            cout<<"No\n";
            continue;
        }
        if(a.size()<b.size()){
            bool flag=false;
            for(int i=0;i+k<=a.size();i++){
                string temp=a.substr(i,k);
                make_failure(temp);
                if(kmp(b,temp)){
                    cout<<"Yes\n";
                    flag=true;
                    break;
                }
            }
            if(!flag) cout<<"No\n";
        }
        else{
            bool flag=false;
            for(int i=0;i+k<=b.size();i++){
                string temp=b.substr(i,k);
                make_failure(temp);
                if(kmp(a,temp)){
                    cout<<"Yes\n";
                    flag=true;
                    break;
                }
            }
            if(!flag) cout<<"No\n";
        }
    }
}