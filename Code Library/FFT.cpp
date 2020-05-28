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
struct complx{
    long double real, img;

    inline complx(){
        real = img = 0.0;
    }

    inline complx(long double x){
        real = x, img = 0.0;
    }

    inline complx(long double x, long double y){
        real = x, img = y;
    }

    inline void operator += (complx &other){
        real += other.real, img += other.img;
    }

    inline void operator -= (complx &other){
        real -= other.real, img -= other.img;
    }

    inline complx operator + (complx &other){
        return complx(real + other.real, img + other.img);
    }

    inline complx operator - (complx &other){
        return complx(real - other.real, img - other.img);
    }

    inline complx operator * (complx& other){
        return complx((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
    }
};


void FFT(vector <complx> &ar, int n, int inv){
    int i, j, l, len, len2;
    const long double p = 4.0 * inv * acos(0.0);

    for (i = 1, j = 0; i < n; i++){
        for (l = n >> 1; j >= l; l >>= 1) j -= l;
        j += l;
        if (i < j) swap(ar[i], ar[j]);
    }

    for(len = 2; len <= n; len <<= 1) {
        long double ang = 2 * PI / len * inv;
        complx wlen(cos(ang), sin(ang));
        for(i = 0; i < n; i += len) {
            complx w(1);
            for(j = 0; j < len / 2; j++) {
                complx u = ar[i + j];
                complx v = ar[i + j + len / 2] * w;
                ar[i + j] = u + v;
                ar[i + j + len / 2] = u - v;
                w = w * wlen;
            }
        }
    }

    if (inv == -1){
        long double tmp = 1.0 / n;
        for (i = 0; i < n; i++) ar[i].real *= tmp;
    }
}


vector <complx> Mul(const vector <complx> &x, const vector <complx> &y) {
    int n = 1;
    while(n <= x.size() + y.size()) n = n * 2;
    vector <complx> A(n), B(n);
    for(int i=0; i<x.size(); i++) A[i] = x[i];
    for(int i=0; i<y.size(); i++) B[i] = y[i];
    FFT(A, n, 1);
    FFT(B, n, 1);
    for(int i=0; i<n; i++) A[i] = A[i] * B[i]; 
    FFT(A, n, -1);
    return A;
}

void multiply(string a, string b){
    vector<complx>v1,v2;

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
        v1.push_back(complx(d));
    }
    for(int i = 0;i < b.size();i++){
        int d = b[i] - '0';
        v2.push_back(complx(d));
    }

    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());

    vector<complx>v = Mul(v1,v2);

    int carry = 0;
    vector<int>answer;
    for(int i = 0;i < v.size();i++){
        int temp = round(v[i].real);
        temp += carry;
        answer.push_back(temp % 10);
        carry = temp/10;
    }
    while(answer.size() > 1 and answer.back() == 0) answer.pop_back();
    reverse(ans.begin(), ans.end());
}