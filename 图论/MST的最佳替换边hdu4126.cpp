MST的最佳替换边O(n^2)算法
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 3010
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;

int n,m;
int dis[N][N];

int d[N];
int vis[N];
bool mp[N][N];
ll ans;

struct Edge{
    int v,next;
}edge[N*2];
int head[N],cnt;

int dp[N][N];

void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}

void addedge(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].v=u;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}

void prim(){
    for(int i=0;i<n;i++){
        vis[i]=0;
        d[i]=dis[0][i];
    }
    vis[0]=-1;
    ans=0;
    memset(mp,0,sizeof(mp));
    for(int i=1;i<n;i++){
        int Min=INF;
        int node=-1;
        for(int j=0;j<n;j++){
            if(vis[j]!=-1 && d[j]<Min){
                node=j;
                Min=d[j];
            }
        }

        ans+=Min;
        mp[vis[node]][node]=mp[node][vis[node]]=1;
        addedge(vis[node],node);
        vis[node]=-1;

        for(int j=0;j<n;j++){
            if(vis[j]!=-1 && d[j]>dis[node][j]){
                vis[j]=node;
                d[j]=dis[node][j];
            }
        }
    }
}

int dfs(int cur,int u,int fa){
    int res=INF;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        int tmp=dfs(cur,v,u);
        dp[u][v]=dp[v][u]=min(tmp,dp[u][v]);
        res=min(res,tmp);
    }
    if(fa!=cur){
        res=min(res,dis[cur][u]);
    }
    return res;
}

int main(){
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int u,v,w;
    while(scanf("%d %d",&n,&m)){
        if(n==0 && m==0)break;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++) dis[i][j]=INF;
        for(int i=0;i<m;i++){
            scanf("%d %d %d",&u,&v,&w);
            dis[u][v]=dis[v][u]=w;
        }
        init();
        prim();
        for(int i=0;i<n;i++)
            for(int j=i;j<n;j++)
                dp[i][j]=dp[j][i]=INF;
        for(int j=0;j<n;j++)
            dfs(j,j,-1);
        ll ANS=0;
        //printf("%lf\n",ans);
        int q;
        scanf("%d",&q);
        for(int i=0;i<q;i++){
            scanf("%d %d %d",&u,&v,&w);
            if(!mp[u][v]) ANS+=ans;
            else ANS+=ans-dis[u][v]+min(w,dp[u][v]);
        }
        printf("%.4lf\n",(double)ANS/q);
    }
    return 0;
}
