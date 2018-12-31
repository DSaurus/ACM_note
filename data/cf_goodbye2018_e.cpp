#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long LL;
int n;
const int maxn = 5e5 + 5;
const int LOGN = 22;
int c[maxn*4];
void Modify(int x, int s){
    for(; x <= n; x += x&(-x)) c[x] += s;
}
int Query(int y){
    if(y <= 0) return 0;
    int ans = 0;
    for(int x = y; x; x -= x&(-x)) ans += c[x];
    return ans;
}
int findl(int v)
{
	int sum = 0;
	int pos = 0;
	for(int i=LOGN; i>=0; i--)
	{
		if(pos + (1 << i) <= n && sum + c[pos + (1 << i)] < v)
		{
			sum += c[pos + (1 << i)];
			pos += (1 << i);
		}
	}

	return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
}
int findr(int v)
{
	int sum = 0;
	int pos = 0;
	for(int i=LOGN; i>=0; i--)
	{
		if(pos + (1 << i) <= n && sum + c[pos + (1 << i)] <= v)
		{
			sum += c[pos + (1 << i)];
			pos += (1 << i);
		}
	}

	return pos; // +1 because 'pos' will have position of largest value less than 'v'
}
int query(int x, int y) { return x <= y ? Query(y) - Query(x-1) : 0; }

int a[maxn], b[maxn], l, r, tt[maxn];

int main()
{
    cin>>n;
    int maxans = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if(a[i] > 0) maxans++;
    }
    sort(a+1, a+1+n);
    for(int i = 1; i <= n; i++) tt[i] = a[i];
    for(int i = 1; i <= n; i++) b[i] = a[i] - a[i-1], Modify(i, b[i]);
    memset(a, 0, sizeof(a));
    int l = 1;
    int ans = 0, ansr = 0, ca = 0;
    for(int i = n; i >= 1; i--){
        int now = Query(i);
        if(now == 0) { l = i; break; }
        int to = max(findr(0)+1, i-now);
        if(to == i){
            if(now >= 2){
                if(now-1 > ca){
                    cout<<-1<<endl;
                    return 0;
                } else {
                    ansr -= (now-1);
                    ans += (now-1);
                    ca -= (now-1);
                }
            }
            a[i] = 1;
            l = i;
            break;
        }
        int toval = Query(to);
        l = findl(toval);
        r = min(findr(toval), i-1);
        Modify(r+1, -1);
        Modify(i, 1);
        Modify(l, -1);
        Modify(l+r-to+1, 1);
        a[i] = now-(i-to);
        if(a[i] >= 2) {
            if(a[i]-1 > ca){
                cout<<-1<<endl;
                return 0;
            } else {
                ansr -= (a[i]-1);
                ans += (a[i]-1);
                ca -= (a[i]-1);
                a[i] = 1;
            }
        }
        if(a[i] == 0 && tt[i] != 0) ca++;
    }
    for(int i = 1; i <= n; i++){
        if(a[i] == 1) ans++;
    }
    for(int i = l+1; i <= n; i++){
        if(a[i] == 0 && tt[i] != 0) ansr++;
    }
    int t = ansr;
    for(int i = ans, j = 0; j <= t && i + j*2 <= maxans; j++) printf("%d ", i+j*2);
    return 0;
}
