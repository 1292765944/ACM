1.HDU 4396
n个点，m条双向边。给你起点s，终点t，以及k。问你从s到t至少得到k分的最短路。边有自环，且边可以重复走。边每走一次获得10分。
#include<cstdio>
#include<queue>
#include<cstring>
#define M 100100
#define N 5010
#define inf 100000000
using namespace std;
typedef long long ll;
int n,m,cnt;
int s,t,ts;
struct Edge{
    int v,c,next;
}edge[M*2];
int head[N];
int dp[N][52];
bool vis[N][52];
struct Point{
    int v,bian;
};
void addedge(int u,int v,int len){
    edge[cnt].v=v;
    edge[cnt].c=len;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].v=u;
    edge[cnt].c=len;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=51;j++)
            dp[i][j]=inf;
}

void bfs(){
    int i,j;
    queue<struct Point>q;
    struct Point tem,tt;
    tem.v=s;
    tem.bian=0;
    q.push(tem);
    dp[s][0]=0;
    for(i=1;i<=n;i++)
        for(j=0;j<=51;j++)
            vis[i][j]=0;
    vis[s][0]=1;
    while(!q.empty()){
        tem=q.front();
        q.pop();
        vis[tem.v][tem.bian]=0;
        int u=tem.v;
        for(i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            tt.v=v;
            if(tem.bian==ts)
                tt.bian=tem.bian;
            else
                tt.bian=tem.bian+1;
            if(dp[v][tt.bian]>dp[u][tem.bian]+edge[i].c){
                dp[v][tt.bian]=dp[u][tem.bian]+edge[i].c;
                if(!vis[v][tt.bian]){
                    vis[v][tt.bian]=1;
                    q.push(tt);
                }
            }
        }
    }
}
int main(){
    int u,v,w;
    int i;
    while(scanf("%d %d",&n,&m)==2){
        init();
        for(i=1;i<=m;i++){
            scanf("%d %d %d",&u,&v,&w);
            addedge(u,v,w);
        }
        scanf("%d %d %d",&s,&t,&ts);
        if(ts%10==0)
            ts=ts/10;
        else
            ts=ts/10+1;
        bfs();
        if(dp[t][ts]==inf)
            printf("-1\n");
        else
            printf("%d\n",dp[t][ts]);
    }
}

2.HDU 4360
题目大意是给一个n个点m条边的无向图。每条边有权值和一个字母标号，字母标号有四种 'L' 'O' 'V' 'E',现在要从1点到n点去

找求找到一条路径，路径按顺序构成了若干个LOVE 注意必须是完整的LOVE

然后要求有LOVE的的条件下路径最短，如果有多条最短路，找LOVE最多的那条

思路就是拆点

将每个点分为四个，代表L，LO，LOV, LOVE四种状态

然后跑spfa即可

注意1个点时候的trick 需要进行一些特殊的处理


#include<queue>
#include<cstring>
#include<cstdio>
#define N 1400
#define M 14000
const long long inf=(~(0ULL)>>1);
using namespace std;
typedef long long ll;
int n,m;
int flag[120];
int head[N],cnt;
struct Edge{
    int v,next,id;
    ll l;
}edge[M*2];
ll len[N][4];
int num[N][4];
bool vis[N][4];
struct Point{
    int u,last;
};
void addedge(int u,int v,int length,int id){
    edge[cnt].v=v;
    edge[cnt].l=length;
    edge[cnt].id=id;
    edge[cnt].next=head[u];
    head[u]=cnt++;

    edge[cnt].v=u;
    edge[cnt].l=length;
    edge[cnt].id=id;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        for(int j=0;j<=3;j++){
            len[i][j]=inf;
            num[i][j]=0;
            vis[i][j]=0;
        }
}
void SPFA(){
    int now;
    ll nowl;
    queue<struct Point>q;
    struct Point tem,temp;
    tem.u=1,tem.last=3;
    len[1][3]=0;
    num[1][3]=0;
    vis[1][3]=1;
    q.push(tem);
    while(!q.empty()){
        tem=q.front();
        q.pop();
        int u=tem.u;
        vis[u][tem.last]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            if((tem.last+1)%4!=edge[i].id)continue;
            temp.last=edge[i].id;
            temp.u=v;
            if(temp.last==3)
                now=num[u][tem.last]+1;
            else
                now=num[u][tem.last];
            nowl=len[u][tem.last]+edge[i].l;
            if(nowl<len[v][temp.last] || len[v][temp.last]==0){  //len[v][temp.last]==0是防止n==1的情况
                len[v][temp.last]=nowl;
                num[v][temp.last]=now;
                if(!vis[v][temp.last]){
                    vis[v][temp.last]=1;
                    q.push(temp);
                }
            }
            else if(nowl==len[v][temp.last] && now>num[v][temp.last]){
                num[v][temp.last]=now;
                if(!vis[v][temp.last]){
                    vis[v][temp.last]=1;
                    q.push(temp);
                }
            }
        }
    }
}
int main(){
    int t,T;
    char id;
    int u,v,l;
    scanf("%d",&T);
    flag['L']=0;
    flag['O']=1;
    flag['V']=2;
    flag['E']=3;
    for(t=1;t<=T;t++){
        scanf("%d %d",&n,&m);
        init();
        for(int i=1;i<=m;i++){
            scanf("%d %d %d %c",&u,&v,&l,&id);
            addedge(u,v,l,flag[id]);
        }
        SPFA();
        if(num[n][3]==0)
            printf("Case %d: Binbin you disappoint Sangsang again, damn it!\n",t);
        else
            printf("Case %d: Cute Sangsang, Binbin will come with a donkey after travelling %I64d meters and finding %d LOVE strings at last.\n",t,len[n][3],num[n][3]);
    }
    return 0;
}


