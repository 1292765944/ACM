1.倍增LCA+最大生成树
题意：给出一棵节点有值的树，给出Q个询问(a,b)，问从a到b的最大盈利（即：先在最小值买入，再在最大值卖出）
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50100
#define POW 17
#define inf 1000000
using namespace std;
int val[N];
int head[N],cnt;
int p[N][POW],dep[N],mi[N][POW],mx[N][POW],dp[N][POW],dp1[N][POW],f[N];
struct relation{
    int u,v,w;
}r[N];
struct Edge{
    int v,next;
}edge[N*2];
void addedge(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].v=u;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
void init(int n){
    int i,j;
    memset(head,-1,sizeof(head));
    memset(dep,0,sizeof(dep));
    memset(p,0,sizeof(p));
    for(i=1;i<=n;i++)f[i]=i;
    for(i=1;i<=n;i++)
        for(j=0;j<POW;j++)
            mi[i][j]=inf,dp[i][j]=dp1[i][j]=mx[i][j]=0;
    cnt=0;
}
void dfs(int u,int fa){
    int i,j;
    dep[u]=dep[fa]+1;
    for(i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        p[v][0]=u;
        mi[v][0]=min(val[u],val[v]);
        mx[v][0]=max(val[u],val[v]);
        dp[v][0]=val[u]-val[v];
        dp1[v][0]=val[v]-val[u];
        for(j=1;(1<<j)<=dep[u]+1;j++){
            p[v][j]=p[p[v][j-1]][j-1];
            mi[v][j]=min(mi[v][j-1],mi[p[v][j-1]][j-1]);
            mx[v][j]=max(mx[v][j-1],mx[p[v][j-1]][j-1]);

            dp[v][j]=max(dp[v][j-1],dp[p[v][j-1]][j-1]);
            dp[v][j]=max(dp[v][j],mx[p[v][j-1]][j-1]-mi[v][j-1]);

            dp1[v][j]=max(dp1[v][j-1],dp1[p[v][j-1]][j-1]);
            dp1[v][j]=max(dp1[v][j],mx[v][j-1]-mi[p[v][j-1]][j-1]);
        }
        dfs(v,u);
    }
}
int LCA(int u,int v){
    int i;
    if(dep[u]>dep[v]) u^=v,v^=u,u^=v;
    if(dep[u]<dep[v]){
        int del=dep[v]-dep[u];
        for(i=0;i<POW;i++)
            if(del & (1<<i))
                v=p[v][i];
    }
    if(u!=v){
        for(i=POW-1;i>=0;i--)
            if(p[u][i]!=p[v][i])
                u=p[u][i],v=p[v][i];
        u=p[u][0],v=p[v][0];
    }
    return u;
}
int getmaxdp(int u,int v){
    int ans=0,i,tmp=inf; // tmp记录最小值
    int del=dep[u]-dep[v];
    for(i=POW-1;i>=0;i--)
        if(del & (1<<i)){
            ans=max(ans,dp[u][i]);
            ans=max(ans,mx[u][i]-tmp);
            tmp=min(tmp,mi[u][i]);
            u=p[u][i];
        }
    return ans;
}
int getmaxdp1(int u,int v){
    int ans=0,i,tmp=0; // tmp记录最大值
    int del=dep[u]-dep[v];
    for(i=POW-1;i>=0;i--)
        if(del & (1<<i)){
            ans=max(ans,dp1[u][i]);
            ans=max(ans,tmp-mi[u][i]);
            tmp=max(tmp,mx[u][i]);
            u=p[u][i];
        }
    return ans;
}
int getmx(int u,int v){
    int ans=0,i;
    int del=dep[u]-dep[v];
    for(i=POW-1;i>=0;i--)
        if(del & (1<<i)){
            ans=max(ans,mx[u][i]);
            u=p[u][i];
        }
    return ans;
}
int getmi(int u,int v){
    int ans=inf,i;
    int del=dep[u]-dep[v];
    for(i=POW-1;i>=0;i--)
        if(del & (1<<i)){
            ans=min(ans,mi[u][i]);
            u=p[u][i];
        }
        return ans;
}
void solve(int u,int v){
    int lca=LCA(u,v);
    int a,b,c,d;
    a=getmaxdp(u,lca);
    b=getmaxdp1(v,lca);
    c=getmi(u,lca);
    d=getmx(v,lca);
    printf("%d\n",max(max(a,b),d-c));
}
bool cmp(struct relation a,struct relation b){
    return a.w>b.w;
}
int find(int u){
    if(f[u]==u)return u;
    return f[u]=find(f[u]);
}
int main(){
    int i,u,v,n,m,q;
    while(scanf("%d",&n)==1){
        init(n);
        for(i=1;i<=n;i++)
            scanf("%d",&val[i]);
        scanf("%d",&m);
        for(i=1;i<=m;i++)
            scanf("%d %d %d",&r[i].u,&r[i].v,&r[i].w);
        sort(r+1,r+1+m,cmp);
        int w=0;
        for(i=1;i<=m;i++){
            int uu=find(r[i].u),vv=find(r[i].v);
            if(uu!=vv){
                addedge(r[i].u,r[i].v);
                w+=r[i].w;
                f[uu]=vv;
            }
        }
        printf("%d\n",w);
        dfs(1,0);
        scanf("%d",&q);
        for(i=1;i<=q;i++){
            scanf("%d %d",&u,&v);
            solve(u,v);
        }
    }
    return 0;
}

2.倍增模板
/*
2^17=131072;
2^18=262144;
*/
const int POW = 18;
void dfs(int u,int fa){
	d[u]=d[fa]+1;
    p[u][0]=fa;
	for(int i=1;i<POW;i++) p[u][i]=p[p[u][i-1]][i-1];
	int sz=edge[u].size();
	for(int i=0;i<sz;i++){
		int v=edge[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}
}
int lca( int a, int b ){
	if( d[a] > d[b] ) a ^= b, b ^= a, a ^= b;
	if( d[a] < d[b] ){
		int del = d[b] - d[a];
		for( int i = 0; i < POW; i++ ) if(del&(1<<i)) b=p[b][i];
	}
	if( a != b ){
		for( int i = POW-1; i >= 0; i-- ) 
			if( p[a][i] != p[b][i] ) 
			     a = p[a][i] , b = p[b][i];
		a = p[a][0], b = p[b][0];
	}
	return a;
}

3.题意：给你一个森林，m个询问:v,p

求有多少个点（除v外） 与 v的第p个祖先相同

这个题首先要解决找某个点的第p个祖先的问题，可以采用倍增法

记录一个二维数组p[u][i]表示u的第2^i个祖先，那么通过这个数组我们就可以知道u的上面任意深度（相对于u）祖先是谁（巧妙的利用二进制）


#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 100100
using namespace std;
vector<int>vec,vec1[N];
int head[N],cnt;
struct Edge{
    int v,next;
}edge[N];
int tim,b[N],f[N],dep[N],p[N][18];
int ans[N];
void init(){
    vec.clear();
    memset(head,-1,sizeof(head));
    memset(dep,0,sizeof(dep));
    memset(p,0,sizeof(p));
    cnt=tim=0;
}
void addedge(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void dfs(int u,int fa){
    int i;
    b[u]=++tim;
    dep[u]=dep[fa]+1;
    vec1[dep[u]].push_back(tim);
    p[u][0]=fa;
    for(i=1;i<18;i++)p[u][i]=p[p[u][i-1]][i-1];
    for(i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        dfs(v,u);
    }
    f[u]=++tim;
}
int find(int u,int num){    //返回u的第num代祖先
    for(int i=0;i<18;i++)
        if((1<<i)&num)
            u=p[u][i];
    return u;
}
int solve(int s,int t,int num){
    int h=vec1[num].size()-1,l=0,sum=0;
    while(l<=h){
        int mid=(h+l)>>1;
        if(vec1[num][mid]>t)
            h=mid-1;
        else{
            sum=mid+1;
            l=mid+1;
        }
    }
    return sum;
}
int main(){
    int i,v,n,m,num;
    init();
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&v);
        if(v==0)vec.push_back(i);
        addedge(v,i);
    }
    for(i=0;i<vec.size();i++)
        dfs(vec[i],0);
    scanf("%d",&m);
    for(i=1;i<=m;i++){
        scanf("%d %d",&v,&num);
        int u=find(v,num);
        if(!u)ans[i]=0;
        else ans[i]=solve(b[u],f[u],dep[v])-solve(1,b[u]-1,dep[v])-1;  //二分查找u的子树中dep为dep[v]的点个数减一即为所求
    }
    for(i=1;i<=m;i++)
        if(i==1)printf("%d",ans[i]);
        else printf(" %d",ans[i]);
    printf("\n");
	return 0;
}

4.LCA定义求法
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 200100
using namespace std;
int head[N],cnt,num;
int dfn[N],low[N],fa[N];
bool yes[N];
struct Edge{
    int v,next;
}edge[M*2];

void addedge(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].v=u;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
void init(){
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(yes,0,sizeof(yes));
    fa[1]=1,dfn[0]=0;
    cnt=num=0;
}
void tarjan(int u,int fat){
    int i,flag=1;
    dfn[u]=low[u]=dfn[fat]+1;
    for(i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fat && flag){
            flag=0;
            continue;
        }
        if(dfn[v]==0){
            fa[v]=u;
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                yes[v]=1;
                num++;
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}
void LCA(int u,int v){
    if(dfn[u]<dfn[v])swap(u,v);
    while(dfn[u]>dfn[v]){
        if(yes[u]){
            num--;
            yes[u]=0;
        }
        u=fa[u];
    }
    while(u!=v){
        if(yes[u]){
            num--;
            yes[u]=0;
        }
        if(yes[v]){
            num--;
            yes[v]=0;
        }
        u=fa[u],v=fa[v];
    }
}
int main(){
    int i,n,m,Q;
    int u,v;
    int cas=0;
    while(scanf("%d %d",&n,&m)){
        if(n==0 && m==0)break;
        init();
        for(i=1;i<=m;i++){
            scanf("%d %d",&u,&v);
            addedge(u,v);
        }
        tarjan(1,0);
        scanf("%d",&Q);
        printf("Case %d:\n",++cas);
        for(i=1;i<=Q;i++){
            scanf("%d %d",&u,&v);
            LCA(u,v);
            printf("%d\n",num);
        }
    }
    return 0;
}




