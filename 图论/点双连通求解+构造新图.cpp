#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#define N 2000    //注意缩点后新建的图的顶点数可能达到2*n-1
#define M 600000  //缩点新建的图一定是树
using namespace std;

struct Edge{
    int u,v,id,next;
}edge[M*2];

int head[N],head2[N],cnt;
int dfn[N],low[N],color[N],depth,c,b;   //color数组指示每个割点或者点双连通分支的在新图的标号，割点标号均>=c
int cut[N];  //cut不为0表示是割点，分成cut+1块
stack<int>ss;
vector<int>dpt[N];          //每个点连通分支所包含的节点
vector<int>node_bcc[N];     //每个节点所属的点连通分支
int edge_belong[N];         //每条边所属的点连通分支

void addedge(int u,int v,int id,int * head){
    edge[cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].id=id;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].u=v;
    edge[cnt].v=u;
    edge[cnt].id=id;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}

void init(){
    memset(head,-1,sizeof(head));
    memset(head2,-1,sizeof(head2));
    memset(dfn,0,sizeof(dfn));
    memset(color,0,sizeof(color));
    memset(cut,0,sizeof(cut));
    depth=c=cnt=0;
    for(int i=0;i<N;i++) dpt[i].clear(),node_bcc[i].clear();
    memset(edge_belong,0,sizeof(edge_belong));
}

void tarjan(int u,int fa){
    int i,j;
    dfn[u]=low[u]=++depth;
    for(i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        if(dfn[v]==0){
            ss.push(i);
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                cut[u]++;
                c++;
                do{
                    j=ss.top();
                    //printf("%d-%d ",edge[j].u,edge[j].v);
                    ss.pop();
                    edge_belong[edge[j].id]=c;
                    if(color[edge[j].u]!=c){
                        color[edge[j].u]=c;
                        dpt[c].push_back(edge[j].u);
                        node_bcc[edge[j].u].push_back(c);
                    }
                    if(color[edge[j].v]!=c){
                        color[edge[j].v]=c;
                        dpt[c].push_back(edge[j].v);
                        node_bcc[edge[j].v].push_back(c);
                    }
                }while(j!=i);
                //puts("");
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
            if(dfn[u]>dfn[v]) ss.push(i);   //这句话必须这么写！！否则打印点双联通内部的边会出错
        }
    }
}

int main(){
    int n,m,i,j,u,v;
    scanf("%d %d",&n,&m);
    init();
    for(i=1;i<=m;i++){
        scanf("%d %d",&u,&v);
        addedge(u,v,i,head);
    }
    for(i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
            cut[i]--;   //对于树根要减1
        }
    }
    /*printf("%d\n",c);

    for(i=1;i<=c;i++){
        for(j=0;j<dpt[i].size();j++) printf("%d ",dpt[i][j]);
        puts("");
    }*/

    b=c;
    for(i=1;i<=n;i++) if(cut[i]) color[i]=++c;

    for(i=1;i<=n;i++)
        for(j=0;j<dpt[i].size();j++){
            u=dpt[i][j];
            if(cut[u]){
                addedge(color[u],i,0,head2);
            }
        }

    /*for(i=1;i<=m;i++) printf("%d:%d\n",i,edge_belong[i]);
    for(i=1;i<=n;i++){
        for(j=0;j<node_bcc[i].size();j++) printf("%d ",node_bcc[i][j]);
        puts("");
    }*/
    return 0;
}

