#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#define MAXN 410
#define inf 100000000
using namespace std;
struct Edge{
    int v,id,next;
}edge[MAXN*2];
int e,head[MAXN];

int n,m,c[MAXN];

int N,mat[MAXN],lx[MAXN],ly[MAXN],slack[MAXN],w[MAXN][MAXN];
bool flag[MAXN],flagx[MAXN],flagy[MAXN];
void init()
{
    e=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int id)
{
    edge[e].v=v;
    edge[e].id=id;
    edge[e].next=head[u];
    head[u]=e++;
}

bool find(int s,int t,int id)
{
    if(s==t)
        return true;
    flag[s]=true;
    for(int i=head[s];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(flag[v])
            continue;
        if(find(v,t,id)){
            if(c[edge[i].id]>c[id])
                w[edge[i].id][id-n+1]=c[edge[i].id]-c[id];
            return true;
        }
    }
    return false;
}

bool dfs(int u)
{
    flagx[u]=true;
    for(int i=1;i<=N;i++){
        if(flagy[i])
            continue;
        if(lx[u]+ly[i]==w[u][i]){
            flagy[i]=true;
            if(mat[i]==-1||!flagx[mat[i]]&&dfs(mat[i])){
                mat[i]=u;
                return true;
            }
        }
        else
            slack[i]=min(slack[i],lx[u]+ly[i]-w[u][i]);
    }
    return false;
}
void km()
{
    for(int i=1;i<=N;i++){
        lx[i]=ly[i]=0;
        mat[i]=-1;
        for(int j=1;j<=N;j++)
            lx[i]=max(lx[i],w[i][j]);
    }
    for(int i=1;i<=N;i++){
        while(1){
            for(int j=1;j<=N;j++){
                flagx[j]=flagy[j]=false;
                slack[j]=inf;
            }
            if(dfs(i))
                break;
            int d=inf;
            for(int j=1;j<=N;j++)
                if(!flagy[j])
                    d=min(d,slack[j]);
            for(int j=1;j<=N;j++){
                if(flagx[j])
                    lx[j]-=d;
                if(flagy[j])
                    ly[j]+=d;
            }
        }
    }
}
    
int main()
{
    int t,u,v;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,c+i);
            addedge(u,v,i);
            addedge(v,u,i);
        }
        memset(w,0,sizeof(w));
        for(int i=n;i<=m;i++){
            scanf("%d%d%d",&u,&v,c+i);
            memset(flag,false,sizeof(flag));
            find(u,v,i);
        }
        N=max(n-1,m-n+1);
        km();
        for(int i=1;i<=m;i++)
            printf("%d\n",i<n?c[i]-lx[i]:c[i]+ly[i-n+1]);
    }
    return 0;
}
