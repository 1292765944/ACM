#include <cstdio>
#include <cstring>
#define N 10100
#define M 100100
using namespace std;

int head[N],cou,vis[N],q[N];
struct Edge{
    int v,next;
}edge[M];
int r,ans[N];      //记录路径

void addedge(int u,int v){
    edge[cou].v=v;
    edge[cou].next=head[u];
    head[u]=cou++;
    edge[cou].v=u;
    edge[cou].next=head[v];
    head[v]=cou++;
}

void init(){
    memset(head,-1,sizeof(head));
    cou=0;
}

void euler(int k){
    memset(vis,0,sizeof(vis));
    q[1]=k;
    //vis[k]=1;
    int l=1,now,x,y;
    r=1;
    while(l>0){
        now=q[l];
        x=head[now];
        while(x>=0){
            y=edge[x].v;
            if(vis[x]==0){
                vis[x]=vis[x^1]=1;    //此处处理无向边，若为有向边，应写成vis[x]=1;
                q[++l]=y;
                break;
            }
            head[now]=x=edge[x].next;
        }
        if(x==-1){         //这里把路径记录下来，从1到r-1
            ans[r++]=now;
            l--;
        }
    }
}

int main(){
    int n,m,i,j,u,v;
    while(scanf("%d %d",&n,&m)==2){
        init();
        for(i=1;i<=m;i++){
            scanf("%d %d",&u,&v);
            addedge(u,v);
        }
        euler(1);   //给定欧拉路径的起点1
        for(i=1;i<r;i++){
            printf("%d ",ans[i]);
        }
    }
    return 0;
}

