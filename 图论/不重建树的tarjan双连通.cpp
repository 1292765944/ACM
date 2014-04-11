#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#include <stack>
#include <vector>
#define N 10100
#define M 20100
typedef long long ll;
using namespace std;

struct Edge{
    int v,next;
    ll w;
}edge[M*2];

int head[N],n,m,cnt;
ll val[N],mid;
int scc,depth,dfn[N],low[N],belong[N],tot[N];
bool vis[N],flag;
stack<int>sta;
vector<int>ve[N];

void init(){
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(tot,0,sizeof(tot));
    cnt=depth=scc=0;
    for(int i=1;i<=n;i++) ve[i].clear();
}

void addedge(int u,int v,ll w){
    edge[cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].v=u;
    edge[cnt].w=w;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++depth;
    sta.push(u);
    for(int j=head[u];j!=-1;j=edge[j].next){
        int v=edge[j].v;
        if(v==fa) continue;
        if(dfn[v]==0){
            tarjan(v,u);
            low[u]=min(low[v],low[u]);
        }
        else low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        scc++;
        while(1){
            int tem=sta.top();
            sta.pop();
            belong[tem]=scc;
            ve[scc].push_back(tem);
            if(tem==u)break;
        }
    }
}

int dfs(int u,int total){   // 有vis数组不需要fa变量
    int i,j,sum,tem;
    ll w;
    vis[belong[u]]=1;
    sum=ve[belong[u]].size();
    for(i=0;i<ve[belong[u]].size();i++){
        int v=ve[belong[u]][i];
        for(j=head[v];j!=-1;j=edge[j].next){
            int vv=edge[j].v;
            if(vis[belong[vv]])continue;
            if(belong[vv]==belong[v])continue;
            tem=dfs(vv,total);
            sum+=tem;
            w=edge[j].w;
            edge[j].w=edge[j^1].w=w*tem*(total-tem);
        }
    }
    return sum;
}

bool dfs_check(int u,ll dis){ // 有vis数组不需要fa变量
    int i,j;
    ll sum;
    bool ok;
    vis[belong[u]]=1;
    for(i=0;i<ve[belong[u]].size();i++){
        int v=ve[belong[u]][i];
        sum=val[v];
        for(j=head[v];j!=-1;j=edge[j].next){
            int vv=edge[j].v;
            if(vis[belong[vv]])continue;
            if(belong[vv]==belong[v])continue;
            if(dfs_check(vv,edge[j].w)==0)
                sum+=edge[j].w;
        }
        if(sum>mid) flag=0;
        if(v==u) {if(dis+sum>mid) ok=0; else ok=1;}
    }
    return ok;
}

bool check(){
    memset(vis,0,sizeof(vis));
    flag=1;
    for(int i=1;i<=n;i++){
        if(vis[belong[i]])continue;
        dfs_check(i,0);
        if(flag==0) return 0;
    }
    return 1;
}

int main(){
    int t,T;
    int u,v;
    int i,j;
    ll w;
    scanf("%d",&T);
    for(t=1;t<=T;t++){
        scanf("%d %d",&n,&m);
        for(i=1;i<=n;i++) scanf("%lld",&val[i]);
        init();
        for(i=1;i<=m;i++){
            scanf("%d %d %lld",&u,&v,&w);
            addedge(u,v,w);
        }
        for(i=1;i<=n;i++){
            if(!dfn[i]){
                depth=0;
                tarjan(i,0);
                tot[i]=depth;
            }
        }
        memset(vis,0,sizeof(vis));
        for(i=1;i<=n;i++){
            if(vis[belong[i]])continue;
            dfs(i,tot[i]);
        }
        ll l=0,r=1000000000000LL,ans;
        while(l<=r){
            mid=(l+r)>>1;
            if(check()){
                ans=mid;
                r=mid-1;
            }
            else l=mid+1;
        }
        printf("Case %d: %lld\n",t,ans);
    }
    return 0;
}
