#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define P 1000000007
using namespace std;
typedef unsigned long long ull;
char str[400100];
int d,len;
ull p[400100];
ull r[400100],l[400100];
char ans[400100];
bool dfs(int pos,int doing){
    if(pos==len)return 1;
    char s;
    if(doing)s=str[pos];
    else s='a';
    for(;s<='z';s++){
        r[pos+1]=P*r[pos]+s;
        l[pos+1]=l[pos]+p[pos]*s;
        ans[pos]=s;
        if(pos+1>=d){
            if(((r[pos+1]-r[pos+1-d]*p[d])*p[pos+1-d])==(l[pos+1]-l[pos+1-d]))  //
                continue;
        }
        if(pos+1>=d+1){
            if(((r[pos+1]-r[pos-d]*p[d+1])*p[pos-d])==(l[pos+1]-l[pos-d]))   //这两处公式一定要对
                continue;
        }
        bool flag=0;
        if(doing && s==str[pos])  //注意这里是str[pos]
            flag=dfs(pos+1,1);
        else
            flag=dfs(pos+1,0);
        if(flag)
            return 1 ;
    }
    return 0;
}
int main(){
    int i;
    scanf("%d%s",&d,str);
    len=strlen(str);
    for(i=len-1;i>=0&&str[i]=='z';i--) str[i]='a';
    if(i<0) return puts("Impossible"),0;
    str[i]++;   //注意要找到它的下一个字符串
    p[0]=1;	
    for(i=1;i<400100;i++) //注意小于号
        p[i]=p[i-1]*P;
    r[0]=l[0]=0;
    if(dfs(0,1)){
        ans[len]='\0';
        printf("%s\n",ans);
    }
    else
        printf("Impossible\n");
    return 0;
}


