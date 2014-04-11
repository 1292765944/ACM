1.分两次树形DP，第一次记录的有根树顶点向下所能到达的最长距离和次长距离，并保存最长距离经过的第一个儿子节点。

第二次记录有根树的顶点向上所能达到的最大距离

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int head[10010],cnt;
int dp1[10010],dp2[10010],whe[10010];
struct Edge{
    int v,c,next;
}edge[20010];
void addedge(int u,int v,int c){
	edge[cnt].v=v;
	edge[cnt].c=c;
	edge[cnt].next=head[u];
	head[u]=cnt++;

	edge[cnt].v=u;
	edge[cnt].c=c;
	edge[cnt].next=head[v];
	head[v]=cnt++;
}
void init(int n){
	cnt=0;
	memset(head,-1,sizeof(head));
	memset(dp1,0,sizeof(dp1));
	memset(dp2,0,sizeof(dp2));
}
void dfs1(int s,int father){
	int i;
	bool flag=1;
	for(i=head[s];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v!=father){
			dfs1(v,s);
			flag=0;
		}
	}
	if(flag){
		dp1[s]=dp2[s]=0;
		return ;
	}
	for(i=head[s];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v!=father){
			if(dp1[v]+edge[i].c>dp1[s]){
				dp2[s]=dp1[s];
				dp1[s]=dp1[v]+edge[i].c;
				whe[s]=v;
			}
			else if(dp1[v]+edge[i].c>dp2[s])
				dp2[s]=dp1[v]+edge[i].c;
		}
	}
}
void dfs2(int s,int father){
	int i;
	for(i=head[s];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v!=father){
			if(whe[s]!=v){
				if(dp1[s]+edge[i].c>dp1[v]){
					dp2[v]=dp1[v];
					dp1[v]=dp1[s]+edge[i].c;
					whe[v]=s;
				}
				else if(dp1[s]+edge[i].c>dp2[v])
					dp2[v]=dp1[s]+edge[i].c;
			}
			else{
				if(dp2[s]+edge[i].c>dp1[v]){
					dp2[v]=dp1[v];
					dp1[v]=dp2[s]+edge[i].c;
					whe[v]=s;
				}
				else if(dp2[s]+edge[i].c>dp2[v])
					dp2[v]=dp2[s]+edge[i].c;
			}
			dfs2(v,s);
		}
	}
}
int main(){
    int n,i;
    int v,c;
    while(scanf("%d",&n)==1){
		init(n);
		for(i=2;i<=n;i++){
		    scanf("%d %d",&v,&c);
			addedge(i,v,c);
		}
		dfs1(1,0);
		dfs2(1,0);
		for(i=1;i<=n;i++)
			printf("%d\n",dp1[i]);
	}
}
