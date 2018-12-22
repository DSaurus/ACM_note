#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 100;
vector<int> G[maxn];
long long dp[maxn];
int a[maxn];
long long ans = -1e18, k;
void dfs(int x, int fa){
    long long sum = 0;
    for(auto to : G[x]){
        if(to == fa) continue;
        dfs(to, x);
        sum += dp[to] > 0 ? dp[to] : 0;
    }
    dp[x] = a[x] + sum;
    ans = max(ans, dp[x]);
}

void dfs2(int x, int fa){
    long long sum = 0;
    for(auto to : G[x]){
        if(to == fa) continue;
        dfs2(to, x);
        sum += dp[to] > 0 ? dp[to] : 0;
    }
    dp[x] = a[x] + sum;
    if(dp[x] == ans) dp[x] = 0, k++;
}
int n, x, y;
int main()
{
    cin>>n;
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for(int i = 2; i <= n; i++){
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1, 1);
    dfs2(1, 1);
    cout<<ans*k<<" "<<k<<endl;
    return 0;
}
