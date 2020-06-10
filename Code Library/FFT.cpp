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

//fft
typedef complex<double> base;

void fft(vector<base> & a, bool invert) {
    int n = (int)a.size();

    for (int i = 1, j = 0; i<n; ++i) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)j -= bit;
        j += bit;
        if (i < j)swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i<n; i += len) {
            base w(1);
            for (int j = 0; j<len / 2; ++j) {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) for (int i = 0; i<n; ++i) a[i] /= n;
}

vector<ll> Mul(vector<ll>& a, vector<ll>& b){
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (int i = 0; i<n; ++i) fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> res;
    res.resize(n);
    for (int i = 0; i<n; ++i) res[i] = round(fa[i].real());
    return res;
}

vector<bool> fastexpo(vector<bool>v,int p){
    vector<bool>ret({1});
    while(p > 0){
        if(p % 2 == 1) ret = Mul(ret,v);
        p = p / 2;
        v = Mul(v,v);
    }
    return ret;
}

///multiplying with sign
vector<int> multiply(string a, string b){
    vector<int>v1,v2;

    int sign = 0;
    if(a[0] == '-'){
        sign = 1 - sign;
        a.erase(a.begin());
    }
    if(b[0] == '-'){
        sign = 1 - sign;
        b.erase(b.begin());
    }
    for(int i = 0;i < a.size();i++){
        int d = a[i] - '0';
        v1.push_back(d);
    }
    for(int i = 0;i < b.size();i++){
        int d = b[i] - '0';
        v2.push_back(d);
    }

    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());

    vector<int>v = Mul(v1,v2);

    int carry = 0;
    vector<int>res;
    for(int i = 0;i < v.size();i++){
        int temp = v[i];
        temp += carry;
        res.push_back(temp % 10);
        carry = temp/10;
    }
    while(res.size() > 1 and res.back() == 0) res.pop_back();
    reverse(ans.begin(), ans.end());
    return res;
}

int mark[1005];
int main(){
    int n , k;
    cin >> n >> k;
    vector<bool>v;
    for(int i = 0;i < n;i++){
        int c;
        cin >> c;
        mark[c] = 1;
    }
    for(int i = 0;i <= 1000;i++) v.push_back(mark[i]);
    vector<bool>ret = fastexpo(v,k);
    for(int i = 0;i < ret.size();i++) if(ret[i] > 0) cout << i << ' ';
}