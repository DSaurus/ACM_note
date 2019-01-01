#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
typedef __float128 ft;
typedef __int128 fuck;
const int maxn = 105, maxt = 105;
const fuck inf = (fuck)1<<125;
fuck two_pw[maxn];
fuck dis[maxn][maxn];
fuck dp[maxn][maxn];
int p[maxn];
int n, m, k;
void floyd(){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}
int main()
{
//    freopen("in.txt", "r", stdin);
    int T;
    two_pw[0] = 1;
    for(int i = 1; i < 127; i++){
        two_pw[i] = two_pw[i - 1] * 2;
    }
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                dis[i][j] = inf;
            }
        }
        dis[1][1] = 0;
        for(int i = 0; i < m; i++){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            fuck w0 = w;
            dis[u][v] = min(dis[u][v], w0 * two_pw[maxn - 1]);
            dis[v][u] = min(dis[v][u], w0 * two_pw[maxn - 1]);
//            dis[u][v] = dis[v][u] = w;
        }
        int add = 0;
        for(int i = 1; i <= k; i++){
            scanf("%d", &p[i]);
            if(p[i] == n){
//                i--;k--;
                add++;
            }
        }
        floyd();
        fuck ans = inf;
        int s = 0;
        for(int i = 1; i <= n; i++){
            dp[0][i] = dis[1][i];
        }
//        dp[0][n] = dis[1][n];
//        ans = dp[0][n];
        for(int t = 1; t <= 103; t++){
            for(int i = 1; i <= n; i++)dp[t][i] = inf;
            if(dp[t-1][n] <= ans)s = t-1, ans = dp[t-1][n];
            for(int ii = 1; ii <= k; ii++){
                int i = p[ii];
                if(dp[t - 1][i] >= ans)continue;
                for(int j = 1; j <= n; j++){
                    if(i == j)continue;
                    fuck q = dp[t-1][i] + dis[i][j] / two_pw[t];
                    (dp[t][j] > q) && (dp[t][j] = q);
                }
            }
        }
        s += add;
        if(s >= 101){
            printf("%.12f Burst!\n", double(ft(ans) / two_pw[maxn - 1]));
        }else{
            printf("%.12f %d\n", double(ft(ans) / two_pw[maxn - 1]), s);
        }
    }
    return 0;
}
