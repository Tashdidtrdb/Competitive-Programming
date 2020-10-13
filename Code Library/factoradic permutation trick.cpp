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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
                                            tree_order_statistics_node_update>;

vector<int> to_factoradic(ll n, int sz = 0){
    vector<int> ret;
    int base = 1;
    while(n){
        ret.pb(n % base);
        n /= base;
        base++;
    }
    while((int)ret.size() < sz) ret.pb(0);
    reverse(ret.begin(), ret.end());
    return ret;
}

ll to_decimal(vector<int> &v){
    int n = (int)v.size();
    ll ret = 0, base = n;
    for(int i=0; i<n; i++, base--){
        ret = ( ( (ret * base) % MOD ) + v[i] ) % MOD;
    }
    return ret;
}

// returns permutation of size n from given factoradic number 
vector<int> to_permutation(vector<int> &v){
    vector<int> ret;
    ordered_set<int> st;
    int n = (int)v.size();
    for(int i=0; i<n; i++) st.insert(i);
    for(int x: v){
        int val = *st.find_by_order(x);
        st.erase(val);
        ret.pb(val);
    }
    return ret;
}

// returns lexicographical index of permutation in factoradic system
vector<int> order_of_permutation(vector<int> &p){
    vector<int> ret;
    ordered_set<int> st;
    int n = (int)p.size();
    for(int i=0; i<n; i++) st.insert(i);
    for(int x: p){
        int idx = st.order_of_key(x);
        st.erase(x);
        ret.pb(idx);
    }
    return ret;
}

// returns sum of indices a and b in factoradic system
vector<int> add_order(vector<int> &a, vector<int> &b){
    int n = (int)a.size();
    vector<int> ret(n);
    int carry = 0;
    for(int i=n-1, base = 1; i>=0; i--, base++){
        ret[i] = a[i] + b[i] + carry;
        carry = ret[i] / (base);
        ret[i] %= base;
    }
    return ret;
}

// returns kth lexicographically smallest permutation of size n
// 0th permutation is 0 1 2 ... n-1
vector<int> kth_permutation(int k, int n){
    // need to handle k >= n! if necessary
    vector<int> k_factoradic = to_factoradic(k,n);
    return to_permutation(k_factoradic);
}

int main(){

    fastio;
    
}