1.tarjan 有重边的边双连通缩点版本
#include<cstdio>
#include<string.h>
#include<math.h>
#include<stack>
#include<algorithm>
//#include<memory.h>
//#pragma comment(linker, "/STACK:1024000000,1024000000")//预处理栈，避免栈溢出
#define N 10010
#define M 20010
using namespace std;
struct edge{
	int u,v,next;
}edge[M*4];
int n,m,num[N],sum[N],allsum;
int cnt,head[N],head2[N];
int scc,depth,dfn[N],low[N],belong[N];
stack<int>sta;
int dps[N];
int ans;
void addedge(int u,int v){
    edge[cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].u=v;
    edge[cnt].v=u;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
void addedge2(int u,int v){
    edge[cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].next=head2[u];
    head2[u]=cnt++;
}
void tarjan(int u,int father){
    int flag=1;
    dfn[u]=low[u]=++depth;
    sta.push(u);
    for(int j=head[u];j!=-1;j=edge[j].next){
        int v=edge[j].v;
        if(v==father && flag){          //加上这句话能判断重边，把之前因为father到u的边而建立的反向边排除
            flag=0;
            continue;
        }
        if(dfn[v]==0){
            tarjan(v,u);
            low[u]=min(low[v],low[u]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        scc++;
        while(1){
            int tem=sta.top();
            sta.pop();
            belong[tem]=scc;
            sum[scc]+=num[tem];
            if(tem==u)break;
        }
    }
}
void init(){
    scc=cnt=depth=allsum=0;
    memset(head,-1,sizeof(head));
    memset(head2,-1,sizeof(head2));
    memset(dfn,0,sizeof(dfn));
    memset(sum,0,sizeof(sum));
    memset(dps,0,sizeof(dps));
    ans=100000000;
}
void dp(int u,int father){
    int i;
    dps[u]=sum[u];
    for(i=head2[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==father)continue;
        dp(v,u);
        dps[u]+=dps[v];
        if(abs(allsum-2*dps[v])<ans)
            ans=abs(allsum-2*dps[v]);
    }
}
int main(){
	int i,j,u,v,q;
	while(scanf("%d %d",&n,&m)==2){
        init();
        for(i=1;i<=n;i++){
            scanf("%d",&num[i]);
            allsum+=num[i];
        }
        for(i=1;i<=m;i++){
            scanf("%d %d",&u,&v);
            u++,v++;
            addedge(u,v);
        }
        for(i=1;i<=n;i++)
            if(!dfn[i])
                tarjan(i,0);
        if(scc==1){
            printf("impossible\n");
            continue;
        }
        for(i=1;i<=n;i++)
            for(j=head[i];j!=-1;j=edge[j].next)
                if(belong[edge[j].u] != belong[edge[j].v])
                    addedge2(belong[edge[j].u],belong[edge[j].v]);
        dp(1,0);
        printf("%d\n",ans);
	}
}

2.tarjan离线LCA

#include<cstdio>
#include<string.h>
using namespace std;
int n,m,num[50100],sum[50100],ans[50100];
int head1[50100],head2[50100],cnt,f[50100],ff[50100];
bool flag[50100];
struct Edge{
    int f,v,id,next;
}edge[50100*7];
void addedge(int u,int v,int id,int *head){
    edge[cnt].f=u;
    edge[cnt].v=v;
    edge[cnt].id=id;
    edge[cnt].next=head[u];
    head[u]=cnt++;

    edge[cnt].f=v;
    edge[cnt].v=u;
    edge[cnt].id=id;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
void dfs(int u,int father){
	int i;
	for(i=head1[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v!=father){
			sum[v]=sum[u]+num[v];
            dfs(v,u);
        }
    }
}
int find(int u){
	int s;
	for(s=u;f[s]!=s;s=f[s]);
	while(s!=u){
		int tmp=f[u];
		f[u]=s;
		u=tmp;
	}
	return s;
}
void tarjan(int u,int father){
    int i;
    f[u]=u;
    for(i=head1[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v!=father){
            tarjan(v,u);
            f[v]=u;
        }
    }
    flag[u]=1;
    for(i=head2[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(flag[v]){
			int t=find(v);
			ans[edge[i].id]=sum[edge[i].f]+sum[edge[i].v]-2*sum[t]+num[t];
        }
    }
}
int main(){
    int i,j;
    while(scanf("%d %d",&n,&m)==2){
        memset(head1,-1,sizeof(head1));
        memset(head2,-1,sizeof(head2));
        memset(flag,0,sizeof(flag));
		memset(ff,0,sizeof(ff));
        memset(sum,0,sizeof(sum));
        memset(f,0,sizeof(f));
        cnt=0;
        for(i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            addedge(u,v,0,head1);
        }
        for(i=1;i<=n;i++)
            scanf("%d",&num[i]);
        for(i=1;i<=m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            addedge(u,v,i,head2);
        }
		sum[1]=num[1];
		dfs(1,0);
        tarjan(1,0);
        for(i=1;i<=m;i++)
            printf("%d\n",ans[i]);
    }
}

3.2-sat 强联通算法

#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 405
#define M 10010
using namespace std;
int a[M],b[M],c[M];
struct Edge{
    int v,next;
}edge[M*2];
int head[N],cnt,scc,top,Index;
int dfn[N],low[N],instack[N],sstack[N],belong[N];

void addedge(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void tarjan(int u){
    dfn[u]=low[u]=++Index;
    sstack[++top]=u;
    instack[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[v],low[u]);
        }
        else if(instack[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        scc++;
        while(1){
            int tmp=sstack[top--];
            instack[tmp]=0;
            belong[tmp]=scc;
            if(tmp==u)break;
        }
    }
}
void init(){
    memset(head,-1,sizeof(head));
    cnt=Index=top=scc=0;
    memset(instack,0,sizeof(instack));
    memset(dfn,0,sizeof(dfn));
}
int main(){
    int t,T;
    int i,j;
    int n,m;
    scanf("%d",&T);
    for(t=1;t<=T;t++){
        scanf("%d %d",&n,&m);
        for(i=1;i<=m;i++)
            scanf("%d %d %d",&a[i],&b[i],&c[i]);
        int l=0,h=m,ans;
        while(l<=h){
            int mid=(l+h)>>1;
            init();
            for(i=1;i<=mid;i++){
                if(c[i]==0){
                    addedge(a[i]*2+2-1,b[i]*2+2);
                    addedge(b[i]*2+2-1,a[i]*2+2);
                }
                else if(c[i]==1){
                    addedge(a[i]*2+2-1,b[i]*2-1+2);
                    addedge(a[i]*2+2,b[i]*2+2);
                    addedge(b[i]*2+2-1,a[i]*2-1+2);
                    addedge(b[i]*2+2,a[i]*2+2);
                }
                else{
                    addedge(a[i]*2+2,b[i]*2+2-1);
                    addedge(b[i]*2+2,a[i]*2+2-1);
                }
            }
            for(i=1;i<=2*n;i++){
                if(!dfn[i])
                    tarjan(i);
            }
            bool flag=1;
            for(i=1;i<=n;i++)
                if(belong[i*2-1]==belong[i*2]){
                    flag=0;
                    break;
                }
            if(flag){
                l=mid+1;
                ans=mid;
            }
            else h=mid-1;
        }
        printf("%d\n",ans);
    }
}

4.tarjan求割点

#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
#define N 200100
using namespace std;
typedef long long ll;
int head[N],cnt;
int depth,dfn[N],low[N];
bool cut[N],vis[N];
vector<int>vec;
struct Edge{
    int v,next;
}edge[N];

ll num,cutnum;
int cas,gen;

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
    dfn[0]=0;                        ///////
    memset(cut,0,sizeof(cut));
    memset(vis,0,sizeof(vis));
    cnt=depth=0;
}
void tarjan(int u,int fa){
    dfn[u]=low[u]=dfn[fa]+1;   ////// 注意这里要写dfn[fa]+1，而非++depth
    int child=0,i;
    for(i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        if(dfn[v]==0){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            child++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(u==gen){
        if(child>1) cut[u]=1;
        else cut[u]=0;
    }
    else{
        for(i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            if(dfn[v]==dfn[u]+1)         ///////
                if(low[v]>=dfn[u]){
                    cut[u]=1;
                    break;
                }
        }
    }
}
void find(int u){
    if(cut[u]){
        vec.push_back(u);
        return;
    }
    if(vis[u])return;
    vis[u]=1;
    num++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        find(v);
    }
}
void solve(int n){
    ll ans1=0,ans2=1;
    int i;
    for(i=1;i<=n;i++)
        if(!dfn[i])
            gen=i,tarjan(i,0);      //////注意这里要把根指明
    for(i=1;i<=n;i++){
        if(cut[i]==0 && vis[i]==0){
            vec.clear();
            num=0;
            find(i);
            sort(vec.begin(),vec.end());
            cutnum=unique(vec.begin(),vec.end())-vec.begin();
            if(cutnum>=2)continue;
            if(cutnum==1){
                ans1++;
                ans2*=num;
            }
            else{
                if(num==1)
                    ans1++;
                else{
                    ans1+=2;
                    ans2*=(num-1)*num/2;
                }
            }
        }
    }
    printf("Case %d: %lld %lld\n",++cas,ans1,ans2);
}
int main(){
    int k,i,n,m;
    int u,v;
    cas=0;
    while(scanf("%d",&m)){
        if(m==0)break;
        init();
        n=0;
        for(i=1;i<=m;i++){
            scanf("%d %d",&u,&v);
            n=max(n,u),n=max(n,v);
            addedge(u,v);
        }
        solve(n);
    }
}

