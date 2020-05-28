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

//palindromic tree (number of palindromic substrings with len > 2 whose prefix of len ceil(len/2) is also a palindrome
struct state {
    int len, link;
    map<char, int> next;
};
state st[MAX];
int id, last;
string s;
ll ans[MAX];
void init(){
    for(int i=0; i<=id; i++){
        st[i].len = 0;
        st[i].link = 0;
        st[i].next.clear();
        ans[i] = 0;
    }
    st[1].len = -1;
    st[1].link = 1;
    st[2].len = 0;
    st[2].link = 1;
    id = 2;
    last = 2;
}

void extend(int pos){
    while(s[pos - st[last].len - 1] != s[pos]) last = st[last].link;
    int newlink = st[last].link;
    char c = s[pos];
    while(s[pos - st[newlink].len - 1] != s[pos]) newlink = st[newlink].link;
    if(!st[last].next.count(c)){
        st[last].next[c] = ++id;
        st[id].len = st[last].len + 2;
        st[id].link = (st[id].len == 1 ? 2 : st[newlink].next[c]);
        ans[id] += ans[st[id].link];
        if(st[id].len > 2){
            int l = st[id].len/2 + (st[id].len % 2 ? 1 : 0);
            if(h.range_hash(pos - st[id].len + 1, pos - st[id].len + l) == h.reverse_hash(pos - st[id].len + 1, pos - st[id].len + l)) ans[id]++;
        }
    }
    last = st[last].next[c];
}

int main(){

    fastio;
    int t,cs = 0;
    cin>>t;
    while(t--){
        int n;
        cin>>n>>s;
        s = "#" + s;
        h = stringhash(s);
        init();
        ll sum = 0;

        for(int i=1; i<=n; i++){
            extend(i);
            sum += ans[last];
        }
        cout<<"Case "<<++cs<<": "<<sum<<"\n";
    }
}