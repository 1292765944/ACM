#include <string.h>
#include <stdio.h>
#include <queue>
#define MAXS 500010

int cas,n;
char s[55],find[1000005];
int next[MAXS][26],pos,tot[MAXS],fail[MAXS];
int newnode(){
    memset(next[pos],0,sizeof next[pos]);
    tot[pos]=fail[pos]=0;
    return pos++;
}
void insert(char *s){
    int p=0;
    for(int i=0;s[i];i++){
        int k=s[i]-'a';
        p=next[p][k]?next[p][k]:next[p][k]=newnode();
    }
    ++tot[p];
}
void makefail(){
    std::queue<int> q;
    q.push(0);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=0;i<26;i++){
            int v=next[u][i];
            if(v==0)next[u][i]=next[fail[u]][i];
            else q.push(v);
            if(v!=0&&u!=0)fail[v]=next[fail[u]][i];
        }
    }
}
int makeans(char *s){
    int ans=0;
    for(int i=0,p=0,j;s[i];i++){
        int k=s[i]-'a';
        p=next[p][k];
        for(int j=p;j&&tot[j]!=-1;j=fail[j]){
            ans+=tot[j];
            tot[j]=-1;
        }
    }
    return ans;
}
int main(){
    scanf("%d",&cas);
    for(int ca=1;ca<=cas;ca++){
        scanf("%d",&n);
        pos=0;newnode();
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            insert(s);
        }
        makefail();
        scanf("%s",find);
        int x=makeans(find);
        printf("%d\n",x);
    }
    return 0;
}
