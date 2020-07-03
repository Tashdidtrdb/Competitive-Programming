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

//number of divisors
int NOD(int N){
    int i,val,c,sum;
    val=sqrt(N)+1;
    sum=1;
    for(i=0;primes[i]<val;i++){
        if(N%primes[i]==0){
            c=0;
            while(N%primes[i]==0){
                N/=primes[i];
                c++;
            }
            sum*=(c+1);
            val=sqrt(N)+1;
        }
    }
    if(N>1) sum=sum*2;
    return sum;
}

//sum of divisors
int SOD(int N){
    int i,val,c,sum,p,s;
    val=sqrt(N)+1;
    sum=1;
    for(i=0;primes[i]<val;i++){
        if(N%primes[i]==0){
            p=1;
            while(N%primes[i]==0){
                N/=primes[i];
                p=p*primes[i];
            }
            p=p*primes[i];
            s=(p-1)/(primes[i]-1);
            sum=sum*s;
        }
    }

    if(N>1){
        p=N*N;
        s=(p-1)/(N-1);
        sum=sum*s;
    }
    return sum;
}

//Number of divisors upto N
int D[1000010];
void NOD_n(){
    int i,j,val,N,M,c;
    D[1]=1;
    for(i=2;i<=1000000;i++){
        N=M=i;
        val=sqrt(N)+1;
        for(j=0;primes[j]<val;j++){
            if(M%primes[j]==0){
                c=0;
                while(M%primes[j]==0){
                    M/=primes[j];
                    c++;
                }
                D[N]=(c+1)*D[M];
                break;
            }
        }
        if(M==N) D[N]=2;
    }
}

//Trailing zero in N! base B
seive();
int factors_in_factorial(int N,int p){
    int sum=0;
    while(N){
        sum+=N/p;
        N/=p;
    }
    return sum;
}

int Trailingzero_Base_B(int N,int B){
    int i,ans,freq,power;
    ans=1000000000;
    for(i=0;primes[i]<=B;i++){
        if(B%primes[i]==0){
            freq=0;
            while(B%primes[i]==0){
                freq++;
                B/=primes[i];
            }
            power=factors_in_factorial(N,primes[i]);
            ans=min(ans,power/freq);
        }
    }

    if(b>1){
        power=factor_in_factorial(n,b);
        ans=min(ans,power/1)
    }

    return ans;
}

//Cumulative SOD
ll CSOD(ll n){
    ll j,ans=0;
    for(ll i=2;i*i<=n;i++){
        j=n/i;
        ans+=(i+j)*(j-i+1)/2;
        ans+=i*(j-i);
    }
}

//Last non-zero digit of N!
int dig[MAX] = {1, 1, 2, 6, 4, 2, 2, 4, 2, 8};
int lastNonzeroDigit(ll n){
    if (n < 10)
        return dig[n];

    // Check whether tens (or second last) digit
    // is odd or even
    // If n = 375, So n/10 = 37 and (n/10)%10 = 7
    // Applying formula for even and odd cases.
    if (((n/10)%10)%2 == 0)
        return (6*lastNonzeroDigit(n/5)*dig[n%10]) % 10;
    else
        return (4*lastNonzeroDigit(n/5)*dig[n%10]) % 10;
}