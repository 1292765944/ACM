#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f
#define MAXN 60005
char s[1002];
int n,m;
int next[MAXN][2],fail[MAXN],flag[MAXN],pos;
int newnode(){
    next[pos][0]=next[pos][1]=0;
    fail[pos]=flag[pos]=0;
    return pos++;
}
void insert(char *s,int id){
    int p=0;
    for(int i=0;s[i];i++){
        int k=s[i]-'0',&x=next[p][k];
        p=x?x:x=newnode();
    }
    if(id==-1)flag[p]=-1;
    else flag[p]|=(1<<id);
}
int q[MAXN],front,rear;
void makenext(){
    q[front=rear=0]=0,rear++;
    while(front<rear){
        int u=q[front++];
        for(int i=0;i<2;i++){
            int v=next[u][i];
            if(v==0)next[u][i]=next[fail[u]][i];
            else q[rear++]=v;
            if(v&&u){
                fail[v]=next[fail[u]][i];
                if(flag[fail[v]]==-1)flag[v]=-1;
                else flag[v]|=flag[fail[v]];
            }
        }
    }
}
#define MAXM 1025
int d[MAXN][MAXM],pnt[MAXM],ps,map[MAXM][MAXM],dis[MAXN];
inline int min(int x,int y){return x<y?x:y;}
void bfs(int p){
    for(int i=0;i<pos;i++)dis[i]=INF;
    q[front=rear=0]=pnt[p],rear++;
    dis[pnt[p]]=0;
    while(front<rear){
        int u=q[front++];
        for(int i=0;i<2;i++){
            int v=next[u][i];
            if(flag[v]<0||dis[v]!=INF)continue;
            dis[v]=dis[u]+1;
            q[rear++]=v;
        }
    }
    for(int i=0;i<ps;i++)map[p][i]=dis[pnt[i]];
}
int dp(){
    for(int i=0;i<(1<<n);i++)for(int u=0;u<ps;u++)d[i][u]=INF;
    d[0][0]=0;
    for(int i=0;i<(1<<n);i++){
        for(int u=0;u<ps;u++){
            if(d[i][u]==INF)continue;
            for(int v=0;v<ps;v++)
                d[i|flag[pnt[v]]][v]=min(d[i|flag[pnt[v]]][v],d[i][u]+map[u][v]);
        }
    }
    int ans=INF;
    for(int i=0;i<ps;i++)
        ans=min(ans,d[(1<<n)-1][i]);
    return ans;
}
int main(){
    while(scanf("%d%d",&n,&m),n||m){
        pos=0;newnode();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            insert(s,i);
        }
        for(int i=0;i<m;i++){
            scanf("%s",s);
            insert(s,-1);
        }
        makenext();
        ps=0;
        for(int i=0;i<pos;i++)
            if(i==0||flag[i]>0)pnt[ps++]=i;
        for(int i=0;i<ps;i++)
            bfs(i);
        printf("%d\n",dp());
    }
    return 0;
}

