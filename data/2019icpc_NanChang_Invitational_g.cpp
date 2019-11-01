#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
typedef long long ll;
const int maxn = 1e7 + 5, mod = 1<<30;
int *pri, phi[maxn], mu[maxn], *m, len = 0;
int x[maxn], *t, *sum;
bool *is_pri;
void CalPri(){
    is_pri = new bool[maxn];
    for(int i = 0; i < maxn; i++)is_pri[i] = true;
    pri = new int[maxn];
    m = new int[maxn];
    phi[1] = 1, mu[1] = 1, x[1] = 1;
    for(int i = 2; i < maxn; i++){
        if(is_pri[i])pri[len++] = i, phi[i] = i-1, mu[i] = mod-1, m[i] = 1, x[i] = i-2;
        for(int j = 0; j < len && pri[j]*i < maxn; j++){
            is_pri[i*pri[j]] = false;
            phi[i*pri[j]] = phi[i] * (pri[j] - 1);
            mu[i*pri[j]] = (mod-mu[i])%mod;
            x[i*pri[j]] = ll(pri[j]-2)*x[i]%mod;
            m[i*pri[j]] = 1;
            if(i%pri[j] == 0){
                mu[i*pri[j]] = 0;
                phi[i*pri[j]] = phi[i] * pri[j];
                m[i*pri[j]] = m[i]+1;
                if(m[i*pri[j]] == 2){
                    x[i*pri[j]] = ll(x[i/pri[j]])*(ll(pri[j])*pri[j]%mod - 2*pri[j] + 1 + 2*mod)%mod;
                }else{
                    x[i*pri[j]] = ll(x[i])*pri[j]%mod;
                }
                break;
            }
        }
    }
    delete[] is_pri;
    delete[] pri;
    delete[] m;
    sum = new int[maxn];
    t = new int[maxn];
    ll a = 0, b = 0;
    for(int i = 1; i < maxn; i++){
        a = (a+i)%mod;
        b = (b + i*i)%mod;
        t[i] = (i*a%mod)*b%mod;
    }
    for(ll i = 1; i < maxn; i++){
        x[i] = (x[i]%mod + mod)%mod;
        x[i] = i*i%mod*i%mod*x[i]%mod;
        sum[i] = (sum[i-1] + x[i])%mod;
    }
}
ll solve(ll n){
    ll r = sqrt(n), ans = 0;
    for(int d = 1; d*(r+1) <= n; d++){
        ans = (ans + ll(t[n/d])*x[d])%mod;
    }
    for(int i = 1; i <=r; i++){
        ans = (ans + ll(t[i])*(sum[n/i]-sum[n/(i+1)] + mod))%mod;
    }
    return ans;
}
ll gcd(ll a, ll b){
    return a==0?b:gcd(b%a, a);
}
ll test(ll n){
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= n; k++){
                ans = (ans + phi[j*j]/phi[j]*phi[k*k*k]/phi[k]*phi[gcd(gcd(i,j),k)])%mod;
            }
        }
    }
    return ans;
}
int main()
{
    CalPri();
    int T;
    scanf("%d", &T);
    while(T--){
        ll n;
        scanf("%lld", &n);
//        cout<<test(n)<<' '<<solve(n)<<endl;
        printf("%lld\n", solve(n));
    }
    return 0;
}
