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

//topsort lexicographical order
bool flag;
stack<char>st;
map<char,vector<char> >graph;
set<char>track;
map<char,int>vis,indg;

struct comp{
    bool operator()(const char &a, const char &b) const{
        return a>b;
    }
};

priority_queue<char,vector<char>,comp>q;
void cycle(char source){
    if(vis[source]==1){
        flag=true;
        return;
    }
    if(vis[source]==2) return;
    vis[source]=1;
    for(int i=0;i<graph[source].size();i++) cycle(graph[source][i]);
    vis[source]=2;
}

void topsort(char source){
    vis[source]=1;
    for(int i=0;i<graph[source].size();i++){
        if(!vis[graph[source][i]]){
            indg[graph[source][i]]--;
            if(!indg[graph[source][i]]) q.push(graph[source][i]);
        }
    }
    while(!q.empty()){
        char temp=q.top();
        q.pop();
        topsort(temp);
    }
    st.push(source);
}

int main(){

    fastio;
    int t;
    cin>>t;

    while(t--){
        string s;
        cin>>s;
        graph[s[0]].push_back(s[1]);
        graph[s[1]].push_back(s[2]);
        indg[s[1]]++;
        indg[s[2]]++;
        track.insert(s[0]);
        track.insert(s[1]);
        track.insert(s[2]);
    }

    for(set<char>::iterator it=track.begin();it!=track.end();it++){
        flag=false;
        cycle(*it);
        if(flag==true){
            cout<<"SMTH WRONG\n";
            break;
        }
    }

    if(flag==false){
        vis.clear();
        for(set<char>::iterator it=track.begin();it!=track.end();it++){
            if(!vis[*it] && !indg[*it]) q.push(*it);
        }
        while(!q.empty()){
            char temp=q.top();
            q.pop();
            topsort(temp);
        }

        while(!st.empty()){
            char ans;
            ans=st.top();
            st.pop();
            cout<<ans;
        }

        cout<<"\n";
    }
}