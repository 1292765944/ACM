#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#define N 10010
#define M 100100
#define Q 1010
using namespace std;

struct Edge{
	int v,next;
}edge[M*2 + N*4];
int head[N],cnt;
int dfn[N],low[N],color[N],depth,b,c;
int cut[N];
int num[N];
vector<int>dpt[N];
vector<int>node_bcc[N];
stack<int>ss;

int head2[N*2];
int mark[N*2];

int sum[N*2];
int f[N*2],flag[N*2];
bool ok[N*2];
struct Query{
	int v,id,next;
}query[Q*2];
int head3[N*2],cnt3;
int ans[Q];

void init(){
	memset(head,-1,sizeof(head));
	memset(head2,-1,sizeof(head2));
	memset(head3,-1,sizeof(head3));
	memset(dfn,0,sizeof(dfn));
	memset(cut,0,sizeof(cut));
	memset(color,0,sizeof(color));
	memset(sum,0,sizeof(sum));
	memset(flag,0,sizeof(flag));
	cnt=depth=c=cnt3=0;
	for(int i=0;i<N;i++) dpt[i].clear(),node_bcc[i].clear();
}

void addedge(int u,int v,int *head){
	edge[cnt].v=v;
	edge[cnt].next=head[u];
	head[u]=cnt++;
	edge[cnt].v=u;
	edge[cnt].next=head[v];
	head[v]=cnt++;
}

void addedge3(int u,int v,int id){
	query[cnt3].v=v;
	query[cnt3].id=id;
	query[cnt3].next=head3[u];
	head3[u]=cnt3++;
	query[cnt3].v=u;
	query[cnt3].id=id;
	query[cnt3].next=head3[v];
	head3[v]=cnt3++;
}

void tarjan(int u,int fa,int cou){
	dfn[u]=low[u]=++depth;
	num[u]=cou;
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v==fa) continue;
		if(dfn[v]==0){
			ss.push(i);
			tarjan(v,u,cou);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<=low[v]){
				cut[u]++;
				c++;
				int j;
				do{
					j=ss.top();
					ss.pop();
					if(color[edge[j].v]!=c){
						color[edge[j].v]=c;
						dpt[c].push_back(edge[j].v);
						node_bcc[edge[j].v].push_back(c);
					}
					if(color[edge[j^1].v]!=c){
						color[edge[j^1].v]=c;
						dpt[c].push_back(edge[j^1].v);
						node_bcc[edge[j^1].v].push_back(c);
					}
				}while(j!=i);
			}
		}
		else{
			low[u]=min(low[u],dfn[v]);
			if(dfn[u]>dfn[v]) ss.push(i);
		}
	}
}

void dfs(int u,int fa){
	ok[u]=1;
	for(int i=head2[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v==fa) continue;
		sum[v]=sum[u]+mark[v];
		dfs(v,u);
	}
}

int find(int u){
	if(f[u]==u)return u;
	return f[u]=find(f[u]);
}

void tarjan_lca(int u,int fa){
	ok[u]=1;
	f[u]=u;
	for(int i=head2[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v==fa) continue;
		tarjan_lca(v,u);
		f[v]=u;
	}
	flag[u]=1;
	for(int i=head3[u];i!=-1;i=query[i].next){
		int v=query[i].v;
		if(!flag[v]) continue;
		int t=find(v);
		ans[query[i].id]=sum[u]+sum[v]-2*sum[t]+mark[t];
	}
}

int main(){
	int n,m,q,u,v;
	while(scanf("%d %d %d",&n,&m,&q)){
		if(n==0 && m==0 && q==0) break;
		init();
		for(int i=1;i<=m;i++){
			scanf("%d %d",&u,&v);
			addedge(u,v,head);
		}
		int cou=0;
		for(int i=1;i<=n;i++){
			if(!dfn[i]){
				tarjan(i,0,++cou);
				cut[i]--;
			}
		}

		b=c;
		for(int i=1;i<=n;i++) if(cut[i]>0) color[i]=++c; else if(cut[i]==0) color[i]=node_bcc[i][0];
		for(int i=1;i<=n;i++) if(cut[i]==-1) color[i]=++c;
		//b表示点双联通分量个数，编号1~b，然后从b+1开始编号所有的割点，最后编号所有的孤立点，color数组存放原图中的点对应新图中的编号，割点和孤立的点其值为单独的编号，剩余的点其值为对应点双联通分量编号

		for(int i=1;i<=b;i++){
			for(int j=0;j<dpt[i].size();j++){
				u=dpt[i][j];
				if(cut[u]){
					addedge(color[u],i,head2);
				}
			}
		}

		for(int i=1;i<=b;i++){
			if(dpt[i].size()>2) mark[i]=1;
			else mark[i]=0;
		}
		for(int i=b+1;i<=c;i++) mark[i]=0;
		//mark数组标记这个双联通分量中的点的个数是否大于3，如果是的话如果通过这个点，那一定会有多条简单路径，接下来就是对缩点成树就行判断，某一对点之间的路径上是否存在mark值为1的点，方法有很多，我用的是LCA，也可以把这些点删去后在原图上判断连通性
		for(int i=1;i<=q;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			if(num[a]!=num[b]) ans[i]=100;
			else addedge3(color[a],color[b],i);
		}

		memset(ok,0,sizeof(ok));
		for(int i=1;i<=c;i++){
			if(!ok[i]){
				sum[i]=mark[i];
				dfs(i,0);
			}
		}
		memset(ok,0,sizeof(ok));
		for(int i=1;i<=c;i++){
			if(!ok[i]){
				tarjan_lca(i,0);
			}
		}

		for(int i=1;i<=q;i++)
			if(ans[i])puts("N");
			else puts("Y");
		puts("-");
	}
	return 0;
}
