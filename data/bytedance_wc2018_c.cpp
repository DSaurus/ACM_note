#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int maxn = 1e6 + 100;
int dp[maxn];
vector<pair<int, int> > G[maxn];
vector<int> V;
void dfs(int x, int fa){
    dp[x] = 0;
    //cout<<"*"<<x<<endl;
    for(auto to : G[x]){
        if(to.fi == fa) continue;
        dfs(to.fi, x);
    }
    for(auto to : G[x]){
        if(to.fi == fa) continue;
        //cout<<"?"<<x<<" "<<to.fi<<" "<<to.se<<endl;
        if(to.se != 1 && (to.se % 2 == 1)) dp[x] ^= (dp[to.fi] ^ 1);
        else if(to.se % 2 == 0) dp[x] ^= dp[to.fi];
        else dp[x] ^= (dp[to.fi] + 1);
    }
}

void dfs2(int x, int fa, int ans){
    if(ans < 0) return;
    for(auto to : G[x]){
        if(to.fi == fa) continue;
        if(to.se != 1 && (to.se % 2 == 1)){
            if( (dp[x]^(dp[to.fi]^1)^dp[to.fi]) == ans) V.push_back(to.fi);
            dfs2(to.fi, x, (dp[x]^dp[to.fi]^ans) );
        } else
        if(to.se % 2 == 0){
            if(to.se == 2){
                if( (dp[x]^dp[to.fi]^(dp[to.fi]+1)) == ans) V.push_back(to.fi);
            } else
                if( (dp[x]^dp[to.fi]^(dp[to.fi]^1)) == ans) V.push_back(to.fi);
            dfs2(to.fi, x, dp[to.fi]^dp[x]^ans);
        } else {
            if( ((dp[x]^(dp[to.fi]+1)) == ans)) V.push_back(to.fi);
            dfs2(to.fi, x, ((dp[to.fi]+1)^dp[x]^ans) - 1);
        }

    }
}

int n, T, x, y;

int main()
{
    //freopen("a.txt", "r", stdin);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i = 1; i <= n; i++) G[i].clear(), dp[i] = 0;
        V.clear();
        for(int i = 2; i <= n; i++){
            scanf("%d %d", &x, &y);
            G[x].push_back(mp(i, y));
            G[i].push_back(mp(x, y));
        }
        dfs(1, 1);
        dfs2(1, 1, 0);
        //cout<<"#";
        //for(int i = 1; i <= n; i++) cout<<dp[i]<<" "; cout<<endl;
        cout<<V.size()<<endl;
        sort(V.begin(), V.end());
        for(auto x : V) printf("%d ", x); printf("\n");
    }
    return 0;
}
