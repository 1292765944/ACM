#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 3010
using namespace std;
typedef long long ll;
struct Edge{
    int u,v,len,next;
}edge[N];
struct heap{
    int dis,id,pre;
    bool operator < (const heap &a)const{
        return dis > a.dis;
    }
};
int head[N],cnt,dis[N],n,m,l;
bool used[N],hash[N];
ll ans[N],sum[N][N];
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(hash,0,sizeof(hash));
    memset(ans,0,sizeof(ans));
}
void addedge(int u,int v,int len){
    edge[cnt].u=u;edge[cnt].v=v;
    edge[cnt].len=len;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
ll dijkstra(int s,int f1,int f2){
    priority_queue<heap>Q;
    memset(used,0,sizeof(used));
    for(int i=1;i<=n;i++)dis[i]=l;
    heap p;
    p.dis=0,p.id=s,p.pre=-1;
    dis[s]=0;
    Q.push(p);
    while(!Q.empty()){
        p=Q.top();Q.pop();
        if(used[p.id])continue;
        used[p.id]=1;
        if(f1==cnt&&f2==cnt&&p.id!=s)
            hash[p.pre]=hash[p.pre^1]=1;
        for(int k=head[p.id];k!=-1;k=edge[k].next){
            if(k==f1||k==f2)continue;
            int u=edge[k].u,v=edge[k].v,len=edge[k].len;
            if(dis[v]>dis[u]+len){
                dis[v]=dis[u]+len;
                heap q;
                q.id=v,q.dis=dis[v],q.pre=k;
                Q.push(q);
            }
        }
    }
    ll sum=0;
    for(int i=1;i<=n;i++)
        sum+=dis[i];
    return sum;
}

int main(){
    while(~scanf("%d%d%d",&n,&m,&l)){
        init();
        for(int i=0;i<m;i++){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            addedge(a,b,c);
            addedge(b,a,c);
        }
        for(int i=1;i<=n;i++){
            memset(hash,0,sizeof(hash));
            sum[i][cnt]=dijkstra(i,cnt,cnt);
            for(int j=0;j<cnt;j+=2){
                if(hash[j]==0)sum[i][j]=sum[i][cnt];
                else sum[i][j]=dijkstra(i,j,j^1);
            }
        }
        ll ans1=0,ans2=0;
        for(int j=0;j<cnt;j+=2){
            ll all=0;
            for(int i=1;i<=n;i++)
                all+=sum[i][j];
            ans2=max(ans2,all);
        }
        for(int i=1;i<=n;i++){
            ans1+=sum[i][cnt];
        }
        printf("%lld %lld\n",ans1,ans2);
    }
    return 0;
}

