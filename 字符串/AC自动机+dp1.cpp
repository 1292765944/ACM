#include<cstdio>
#include<string.h>
#include<math.h>
#include<queue>
#include<algorithm>
#define N 1500
using namespace std;
int ok[200];
char s[110];
int n,m;
int next[N][4],fail[N],flag[N],val[20],pos;
int newnode(){
    int i=0;
    for(;i<4;i++)next[pos][i]=0;
    fail[pos]=flag[pos]=val[pos]=0;
    return pos++;
}
int insert(int id){
    int i,p=0;
    for(i=0;s[i];i++){
        int k=ok[s[i]],&x=next[p][k];
        p=x?x:x=newnode();
    }
    flag[p]=1<<id;
}
void makenext(){
    int i;
    queue<int>q;
    q.push(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(i=0;i<4;i++){
            int v=next[u][i];
            if(v==0)next[u][i]=next[fail[u]][i];
            else q.push(v);
            if(u && v){
                fail[v]=next[fail[u]][i];
                flag[v]|=flag[fail[v]];
            }
        }
    }
}
int dp[2][1500][1200];
int dps(){
    int full=(1<<n),cur=0,i,j,k,p,q;
    for(i=0;i<pos;i++)
        for(j=0;j<full;j++)
            dp[cur][i][j]=0;
    dp[0][0][0]=1;
    for(i=0;i<m;i++){
        cur^=1;
        for(j=0;j<pos;j++)
            for(k=0;k<full;k++)
                dp[cur][j][k]=0;
        for(j=0;j<pos;j++)
            for(k=0;k<full;k++){
                if(dp[cur^1][j][k]==0)continue;
                for(p=0;p<4;p++){
                    int v=next[j][p];
                    dp[cur][v][flag[v]|k]=1;
                    /*int v=next[j][p],sum=0;
                    for(q=0;q<n;q++)
                        if((flag[v]&(1<<q))&&(k&(1<<q))==0)
                            sum+=val[q];
                    dp[cur][v][flag[v]|k]=max(dp[cur][v][flag[v]|k],dp[cur^1][j][k]+sum);*/
                }
            }
    }
    int ans=-1;
    for(i=0;i<pos;i++)
        for(j=0;j<full;j++){
            if(dp[cur][i][j]==0)continue;
            int sum=0;
            for(q=0;q<n;q++)
                if(j&(1<<q))sum+=val[q];
            ans=max(ans,sum);
        }
    return ans;
}
int main(){
    int i,w;
    ok['A']=0,ok['C']=1,ok['G']=2,ok['T']=3;
    while(scanf("%d %d",&n,&m)==2){
        pos=0,newnode();
        for(i=1;i<=n;i++){
            scanf("%s %d",s,&val[i-1]);
            insert(i-1);
        }
        makenext();
        int ans=dps();
        if(ans>=0)
            printf("%d\n",ans);
        else
            printf("No Rabbit after 2012!\n");
    }
}

