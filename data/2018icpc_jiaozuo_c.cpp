#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
const int maxn = 3e5 + 5;
int x[maxn], y[maxn];
ll cl[maxn], cr[maxn], cu[maxn], cd[maxn];
ll ox[maxn], oy[maxn];
int x0, y0, l, r, u, d;
int n, m;
ll sum;
void Move(char c, int t){
    if(c == 'L'){
        while(t--){
            if(l > y0){
                t++;
                int iii = min(t, l - y0);
                y0 += iii;
                t -= iii;
                continue;
            }
            if(l == r)return;
            int a = oy[l + 1];
            if(l+1 == r){
                for(int i = u + 1; i <= d - 1; i++){
                    if(cr[i] != 0)
                        cl[i]++;
                    cr[i] = cl[i];
                }
            }
            else if(a > u && a < d)
                cl[a]++;
            sum += cu[l] * cu[l + 1];
            cu[l + 1] += cu[l];
            cl[u] = cu[l + 1];
            if(u != d){
                sum += cd[l] * cd[l + 1];
                cd[l + 1] += cd[l];
                cl[d] = cd[l + 1];
            }
            y0++;l++;
            r = max(r, l);
            if(l == r){
                cr[u] = cl[u];
                cr[d] = cl[d];
            }
        }
    }else if(c == 'R'){
        while(t--){
            if(r < y0 + n - 1){
                t++;
                int iii = min(t, y0 + n - 1 - r);
                y0 -= iii;
//                cout<<iii<<endl;
                t -= iii;
                continue;
            }
            if(l == r)return;
            int a = oy[r - 1];
            if(l + 1 == r){
                for(int i = u + 1; i <= d - 1; i++){
                    if(cl[i] != 0)
                        cr[i]++;
                    cl[i] = cr[i];
                }
            }
            else if (a > u && a < d)
                cr[a]++;
            sum += cu[r] * cu[r - 1];
            cu[r - 1] += cu[r];
            cr[u] = cu[r - 1];
            if(u != d){
                sum += cd[r] * cd[r - 1];
                cd[r - 1] += cd[r];
                cr[d] = cd[r - 1];
            }
            y0--;r--;
            l = min(r, l);
            if(l == r){
                cl[u] = cr[u];
                cl[d] = cr[d];
            }
        }
    }else if(c == 'U'){
        while(t--){
            if(u > x0){
                t++;
                int iii = min(t, u - x0);
                x0 += iii;
                t -= iii;
                continue;
            }
            if(u == d)return;
            int a = ox[u + 1];
            if(u + 1 == d){
                for(int i = l + 1; i <= r - 1; i++){
                    if(cd[i] != 0)
                        cu[i]++;
                    cd[i] = cu[i];
                }
            }
            else if (a > l && a < r)
                cu[a]++;
            sum += cl[u] * cl[u + 1];
            cl[u + 1] += cl[u];
            cu[l] = cl[u + 1];
            if(l != r){
                sum += cr[u] * cr[u + 1];
                cr[u + 1] += cr[u];
                cu[r] = cr[u + 1];
            }
            x0++;u++;
            d = max(d, u);
            if(u == d){
                cd[l] = cu[l];
                cd[r] = cu[r];
            }
        }
    }else{
        while(t--){
            if(d < x0 + n - 1){
                t++;
                int iii = min(t, x0 + n - 1 - d);
                x0 -= iii;
                t -= iii;
                continue;
            }
            if(u == d)return;
            int a = ox[d - 1];
            if(u + 1 == d){
                for(int i = l + 1; i <= r - 1; i++){
                    if(cu[i] != 0)
                        cd[i]++;
                    cu[i] = cd[i];
                }
            }
            else if (a > l && a < r)
                cd[a]++;
            sum += cl[d] * cl[d - 1];
            cl[d - 1] += cl[d];
            cd[l] = cl[d - 1];
            if(l != r){
                sum += cr[d] * cr[d - 1];
                cr[d - 1] += cr[d];
                cd[r] = cr[d - 1];
            }
            x0--;d--;
            u = min(d, u);
            if(u == d){
                cu[l] = cd[l];
                cu[r] = cd[r];
            }
        }
    }
}
void input(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)ox[i] = oy[i] = cu[i] = cd[i] = cl[i] = cr[i] = 0;
    for(int i = 1; i <= n; i++){
        scanf("%d%d", &x[i], &y[i]);
        ox[x[i]] = y[i];
        oy[y[i]] = x[i];
        if(x[i] == 1)cu[y[i]] = 1;
        if(x[i] == n)cd[y[i]] = 1;
        if(y[i] == 1)cl[x[i]] = 1;
        if(y[i] == n)cr[x[i]] = 1;
    }
    sum = 0;
    l = u = 1, r = d = n;
    x0 = y0 = 1;
}
void query(int idx, int &a, int &b){
    a = x[idx], b = y[idx];
    a = max(u, a), b = max(l, b);
    a = min(d, a), b = min(r, b);
    a = a-x0 + 1, b = b-y0+1;
}
void query(int idx){
    int a = x[idx], b = y[idx];
    a = max(u, a), b = max(l, b);
    a = min(d, a), b = min(r, b);
    printf("%d %d\n", a - x0 + 1, b - y0 + 1);
}
char p[20][20];
void draw(){
    for(int i = l; i <= r; i++){
        cout<<cu[i]<<' ';
    }
    cout<<endl;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++)p[i][j] = '.';
    }
    for(int i = 1; i <= n; i++){
        int a, b;
        query(i, a, b);
        p[a][b] = i + '0';
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)cout<<p[i][j];
        cout<<endl;
    }
    cout<<"--------------\n";
}
void make_data(){
    freopen("c", "w", stdout);
    printf("1\n");
    printf("300000 6\n");
    for(int i = 1; i <= 300000; i++)
        printf("%d %d\n", i, i);
    printf("U 300000\n");
    printf("!\n");
    printf("L 149999\n");
    printf("!\n");
    printf("R 500000\n");
    printf("!\n");
}
int main()
{
//    make_data();
//    return 0;
//    freopen("c", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--){
        input();
//        draw();
        for(int i = 0; i < m; i++){
            char c;
            int idx;
            scanf("\n%c", &c);
            if(c == '!')printf("%lld\n", sum);
            else if(c == '?'){
                scanf("%d", &idx);
                query(idx);
            }else{
                scanf("%d", &idx);
                Move(c, idx);
//                cout<<"sum:"<<sum<<endl;
//                cout<<l<<' '<<r<<' '<<u<<' '<<d<<endl;
//                cout<<x0<<' '<<y0<<endl;
            }
//            draw();
        }
    }
    return 0;
}
