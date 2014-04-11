#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 1<<30
#define N 20010
#define M 240100
using namespace std;
struct Edge{
    int v,cap,next;
}edge[M*2];
int n,k,dis[N],gap[N],head[N],pre[N],cur[N];  //n为总点数
void addedge(int u,int v,int c1,int c2){
    edge[k].v=v;
    edge[k].cap=c1;
    edge[k].next=head[u];
    head[u]=k++;

    edge[k].v=u;
    edge[k].cap=c2;
    edge[k].next=head[v];
    head[v]=k++;
}
void init(){
    memset(head,-1,sizeof(head));
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    k=0;
}
int sap(int s,int t){
    for(int i=0;i<n;i++)cur[i]=head[i];//用cur数组去表示当前的一条路径cur[u]为从u指出的边的编号
	int u=pre[s]=s,maxflow=0,aug=-1;
	gap[0]=n;                       //  gap表示初始时dis为0的点有n个
	while(dis[s]<n){
    	loop:	for(int &i=cur[u];i!=-1;i=edge[i].next){  //注意i要引用cur[u]的地址
			int v=edge[i].v;
			if(edge[i].cap && dis[u]==dis[v]+1){
				if(aug==-1 || aug>edge[i].cap)
               				aug=edge[i].cap;
				pre[v]=u;
				u=v;
				if(v==t){
					maxflow+=aug;
					for(u=pre[u];v!=s;v=u,u=pre[u]){
						edge[cur[u]].cap-=aug;
						edge[cur[u]^1].cap+=aug;
					}
					aug=-1;
				}
				goto loop;
			}
		}
		int mindis=n;
		for(int i=head[u];i!=-1;i=edge[i].next){
			int v=edge[i].v;
			if(edge[i].cap && mindis>dis[v]){
				cur[u]=i;
				mindis=dis[v];
			}
		}
		if((--gap[dis[u]])==0)break;
		gap[dis[u]=mindis+1]++;
		u=pre[u];
	}
	return maxflow;
}

int main(){
    int v,e,i,j,a,b,c;
    scanf("%d %d",&v,&e);
    n=v+2;
    init();
    for(i=1;i<=v;i++){
        scanf("%d %d",&a,&b);
        addedge(0,i,a,0);
        addedge(i,v+1,b,0);
    }
    for(i=1;i<=e;i++){
        scanf("%d %d %d",&a,&b,&c);
        addedge(a,b,c,c);
    }
    printf("%d\n",sap(0,v+1));
    return 0;
}

