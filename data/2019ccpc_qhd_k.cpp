#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 100;
vector<int> G[maxn];

int in[maxn];
int n, T, win;

void dfs(int x, int d){
    if(G[x].size() == 0){
        if(d) win = 1;
        return;
    }
    if(G[x].size() > 1) d = 0;
    for(auto y : G[x]){
        dfs(y, d^1);
    }
}

int main()
{
    cin>>T;
    while(T--){
        scanf("%d", &n);
        for(int i = 0; i <= n; i++) {G[i].clear();  in[i] = 0; }
        for(int i = 1; i < n; i++){
            int x;
            scanf("%d", &x);
            G[x].push_back(i+1);
            in[x]++;
        }
        G[0].push_back(1);
        win = 0;
        dfs(0, 0);
        if(win) cout<<"Takeru"<<endl;
        else cout<<"Meiya"<<endl;
    }
    return 0;
}
