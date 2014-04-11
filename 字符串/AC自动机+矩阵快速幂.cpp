#include <string.h>
#include <stdio.h>
#include <queue>
#define MAXN 110
#define MOD 100000
typedef long long LL;
LL dmat[MAXN][MAXN];
struct matrix{
    LL mz[MAXN][MAXN];int n;
    #define FOR(i) for(int i=1;i<=n;i++)
    //初始化矩阵,空矩阵,单位矩阵和dmat矩阵
    matrix(int nn,int type):n(nn){
        if(type==0)FOR(i)FOR(j)mz[i][j]=0;
        else if(type==1)FOR(i)FOR(j)mz[i][j]=(i==j)?1:0;
        else FOR(i)FOR(j)mz[i][j]=dmat[i][j];
    }
    //重载矩阵乘法,10^5*10^5*100不会超longlong的,最后一次性模就可以了,模是很费时的
    matrix operator *(const matrix& b)const{
        matrix ans(n,0);
        FOR(i)FOR(j)if(mz[i][j])
            FOR(k)ans.mz[i][k]+=mz[i][j]*b.mz[j][k];
        FOR(i)FOR(j)if(ans.mz[i][j]>MOD)ans.mz[i][j]%=MOD;
        return ans;
    }
    //二分矩阵乘法
    matrix binMat(int x){
        matrix ans(n,1),tmp(n,2);
        for(;x;tmp=tmp*tmp,x>>=1){
            if(x&1)ans=ans*tmp;
        }
        return ans;
    }
};
int n,m;
char s[12];
int next[MAXN][4],fail[MAXN],flag[MAXN],id[MAXN],ids,pos;
int trans(char c){
    if(c=='A')return 0;
    if(c=='C')return 1;
    if(c=='T')return 2;
    return 3;
}
int newnode(){
    for(int i=0;i<4;i++)next[pos][i]=0;
    fail[pos]=flag[pos]=id[pos]=0;
    return pos++;
}
void insert(char *s){
    int p=0,len=strlen(s);
    for(int i=0;i<len;i++){
        int &x=next[p][trans(s[i])];
        p=x?x:x=newnode();
    }
    flag[p]=1;
}
int q[MAXN],front,rear;
void makenext(){
    q[front=rear=0]=0,rear++;
    while(front<rear){
        int u=q[front++];
        for(int i=0;i<4;i++){
            int v=next[u][i];
            if(flag[v])continue;
            if(v==0)next[u][i]=next[fail[u]][i];
            else q[rear++]=v;
            if(v&&u){//这里u为0时fail[u]=0;而执行下面的语句fail[u]=1;
                fail[v]=next[fail[u]][i];
                //如果指向一个非法节点,那这个节点也是一个非法节点(比如cg和acgt这样的串,第二个串中的g也是非法的)
                if(flag[fail[v]])flag[v]=1;
            }
        }
    }
}
int main(){
    while(scanf("%d%d",&m,&n)!=EOF){
        pos=ids=0;newnode();
        memset(dmat,0,sizeof dmat);
        for(int i=0;i<m;i++){
            scanf("%s",s);
            insert(s);
        }
        makenext();
        //建立矩阵,从每个合法节点到另一个节点转移的方案数,类似于邻接矩阵
        for(int u=0;u<pos;u++){
            if(flag[u])continue;
            for(int i=0;i<4;i++){
                int v=next[u][i];
                if(flag[v])continue;
                if(id[u+1]==0)id[u+1]=++ids;
                if(id[v+1]==0)id[v+1]=++ids;
                dmat[id[u+1]][id[v+1]]++;
            }
        }
        matrix mt=matrix(ids,2).binMat(n);

        LL ans=0;
        for(int i=1;i<=mt.n;i++)
            ans+=mt.mz[1][i];
        ans%=MOD;
        printf("%lld\n",ans);
    }
    return 0;
}

