#include<stdio.h>
#include<cstring>
#include<math.h>
#define inf 1000000000
#define min(a,b) ((a)>(b))?(b):(a)
using namespace std;
int ind[250];
int n,k,dist[250],gap[250],edgeHead[250];//双向边
struct{
    int v,cap,next,re;
}edge[3000];

void addEdge(int u,int v,int ca){
    edge[k].v=v;
    edge[k].cap=ca;
    edge[k].next=edgeHead[u];
    edge[k].re=k + 1;               //这个用来记录此边的反边
    edgeHead[u]=k ++;
    edge[k].v=u;
    edge[k].cap=0;
    edge[k].next=edgeHead[v];
    edge[k].re=k - 1;
    edgeHead[v]=k ++;
}
int dfs (int p , int limit)
{
    if(p==n)return limit;

    for(int i=edgeHead[p];i!=0;i=edge[i].next){
        int v = edge[i].v;
        if(dist[p]==(dist[v]+1) && edge[i].cap>0){
            int t=dfs(v,min(limit , edge[i].cap));
            if(t<0)return t;//没有增广路了
            if(t>0)//更新流
            {
                edge[i].cap-=t;
                edge[edge[i].re].cap+=t;
                return t;
            }
        }
    }

    int tmp=n+1;
    for(int i=edgeHead[p];i!=0;i=edge[i].next){
        int v = edge[i].v;
        if(edge[i].cap>0)
            tmp=min(tmp,dist[v]+1);
    }

    if(--gap[dist[p]]==0 || dist[0]>n)return -1;//出现断层或回流已满
    ++gap[dist[p]=tmp];
    return 0;
}

int SAP()
{
    gap[0]=n+1;
    int f = 0 , t=0;
    while (~(t=dfs(0,inf))) f+=t;
    return f;
}
int main(){
	int i,j,t,T,v,e,sum;
	scanf("%d",&T);
	for(t=1;t<=T;t++){
		scanf("%d %d",&v,&e);
		memset(ind,0,sizeof(ind));
		sum=0;
		memset(edgeHead,0,sizeof(edgeHead));
		memset(dist,0,sizeof(dist));
		memset (gap , 0 , sizeof(gap));
		k=1;
		for(i=1;i<=e;i++){
			int a,b,w;
			scanf("%d %d %d",&a,&b,&w);
			ind[a]--;
			ind[b]++;
			if(w!=1)
				addEdge(a,b,1);
		}
		for(i=1;i<=v;i++){
			if(ind[i]%2){
				break;
			}
			ind[i]/=2;
		}
		if(i<=v){
			printf("impossible\n");
			continue;
		}
		for(i=1;i<=v;i++){
			if(ind[i]<0){
				addEdge(0,i,-ind[i]);
				sum+=-ind[i];
			}
			else if(ind[i]>0)
				addEdge(i,v+1,ind[i]);
		}
		n=v+1;
		int kk=SAP();
		if(kk==sum){
			printf("possible\n");
		}
		else
			printf("impossible\n");
	}
}
