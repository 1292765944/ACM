#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
#define MAX 100010
#define INF 0x5fffffff

using namespace std;

struct A{
    int x, dis;
     A(){}
     A(int a, int b){x = a, dis = b;}
};
typedef struct A node;

bool done[MAX * 3];
int d[MAX * 3];
vector<node> map[MAX * 3];
int n, m, c;

bool operator < (node a, node b){
    return a.dis > b.dis;
}

int numNum(int a , int b){
    return a < b ? a : b;
}

void addedge(int x, int y, int w){
    map[x].push_back(node(y, w));
}

void dijkstra(){
    int i, j, k;
    node s, tem;
    priority_queue<node> que;
    d[1] = 0;
    que.push(node(1, 0));
    while(!que.empty()){
        s = que.top();
        que.pop();
        int st = s.x;
        if(done[st]){
            continue;
        }
        done[st] = true;
        for(i = 0; i < map[st].size(); i++){
            tem = map[st][i];
            if(d[tem.x] > d[st] + tem.dis){
                d[tem.x] = d[st] + tem.dis;
                que.push(node(tem.x, d[tem.x]));
            }
        }
    }
}

int main(){
    int i, j, k, t, x, y, w, tem, tot = 1;
    scanf("%d", &t);
    while(t--){
        for(i = 0; i < MAX * 3; i++){
            map[i].clear();
            d[i] = INF;
            done[i] = false;
        }
        scanf("%d%d%d", &n, &m, &c);
        for(i = 1; i <= n; i++){
            scanf("%d", &tem);
            addedge(n + 2 * tem - 1, i, 0);
            addedge(i, n + 2 * tem, 0);
        }
        for(i = 0; i < m; i++){
            scanf("%d%d%d", &x, &y, &w);
            addedge(x, y, w);
            addedge(y, x, w);
        }
        for(i = 1; i < n; i++){
            addedge(n + 2 * i, n + 2 * (i + 1) - 1, c);
            addedge(n + 2 * (i + 1), n + 2 * i - 1, c);
        }
        dijkstra();
        if(d[n] == INF){
            printf("Case #%d: -1\n", tot++);
        }
        else{
            printf("Case #%d: %d\n", tot++, d[n]);
        }
        
    }
    return 0;
}