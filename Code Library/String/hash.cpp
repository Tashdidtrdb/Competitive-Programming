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

//range hash and inverse hash
struct simplehash{
    int len;
    long long base, mod;
    vector <int> P, H, R;

    simplehash(){}
    simplehash(string str, long long b, long long m){
        base = b, mod = m, len = str.size();
        P.resize(len + 1, 1), H.resize(len + 1, 0), R.resize(len + 2, 0);

        for (int i = 1; i <= len; i++) P[i] = (P[i - 1] * base) % mod;
        for (int i = 1; i <= len; i++) H[i] = (H[i - 1] * base + str[i - 1] + 1007) % mod;
        for (int i = len; i >= 1; i--) R[i] = (R[i + 1] * base + str[i - 1] + 1007) % mod;
    }
    
    inline int range_hash(int l, int r){
        int hashval = H[r + 1] - ((long long)P[r - l + 1] * H[l] % mod);
        return (hashval < 0 ? hashval + mod : hashval);
    }

    inline int reverse_hash(int l, int r){;
        int hashval = R[l + 1] - ((long long)P[r - l + 1] * R[r + 2] % mod);
        return (hashval < 0 ? hashval + mod : hashval);
    }

    inline int concat_range_hash(int l1, int r1, int l2, int r2){
        int hashval1 = range_hash(l1, r1);
        int hashval2 = range_hash(l2, r2);
        int hashval = ((long long)hashval1 * P[r2 - l2 + 1] + hashval2) % mod;
        return (hashval < 0 ? hashval + mod : hashval);
    }

    inline int concat_reverse_hash(int l1, int r1, int l2, int r2){
        int hashval1 = reverse_hash(l1, r1);
        int hashval2 = reverse_hash(l2, r2);
        int hashval = ((long long)hashval2 * P[r1 - l1 + 1] + hashval1) % mod;
        return (hashval < 0 ? hashval + mod : hashval);
    }
};

struct stringhash{
    simplehash sh1, sh2;
    stringhash(){}
    stringhash(string str){
        sh1 = simplehash(str, 1949313259, 2091573227);
        sh2 = simplehash(str, 1997293877, 2117566807);
    }

    inline long long range_hash(int l, int r){ /// 0 index
        return ((long long)sh1.range_hash(l, r) << 32) ^ sh2.range_hash(l, r);
    }

    inline long long reverse_hash(int l, int r){
        return ((long long)sh1.reverse_hash(l, r) << 32) ^ sh2.reverse_hash(l, r);
    }

    inline long long concat_range_hash(int l1, int r1, int l2, int r2){
        return ((long long)sh1.concat_range_hash(l1, r1, l2, r2) << 32) ^ sh2.concat_range_hash(l1, r1, l2, r2);
    }

    inline long long concat_reverse_hash(int l1, int r1, int l2, int r2){
        return ((long long)sh1.concat_reverse_hash(l1, r1, l2, r2) << 32) ^ sh2.concat_reverse_hash(l1, r1, l2, r2);
    }
};
