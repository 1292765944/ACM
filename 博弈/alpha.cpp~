#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int g,b,s;
int bag[25][10];
int dps[1<<21][2];
int sum[1<<21];

int dfs(int sta,int last,int who,int alpha,int beta){
    int tmp=0,cha=0;
    tmp=sum[sta]-sum[last];
    if(who) cha-=tmp;else cha+=tmp;
    if(!tmp) who=!who;
    if(dps[sta][who]!=-10000) return cha+dps[sta][who];
    if(who){
        if(sta==(1<<b)-1) return cha;
        int newbeta=10000;
        bool flag=1;
        for(int i=0;i<b;i++) if(!(sta&(1<<i))){
        	newbeta=min(newbeta,dfs(sta|(1<<i),sta,who,-10000,newbeta));
			if(newbeta<=alpha){
				flag=0;break;
			}
        }
        if(flag)dps[sta][who]=newbeta;
        return newbeta+cha;
    }
    else{
        if(sta==(1<<b)-1) return cha;
        int newalpha=-10000;
        bool flag=1;
        for(int i=0;i<b;i++) if(!(sta&(1<<i))){
        	newalpha=max(newalpha,dfs(sta|(1<<i),sta,who,newalpha,10000));
			if(beta<=newalpha){
				flag=0;break;
			}
        }
        if(flag)dps[sta][who]=newalpha;
        return newalpha+cha;
    }
}

int main(){
    while(scanf("%d %d %d",&g,&b,&s)){
        if(g==0 && b==0 && s==0) break;
        memset(bag,0,sizeof(bag));
        for(int i=0;i<b;i++){
            int n;
            scanf("%d",&n);
            for(int j=0;j<n;j++){
                int tmp;
                scanf("%d",&tmp);
                tmp--;
                bag[i][tmp]++;
            }
        }
        int tmp[10];
        for(int i=0;i<(1<<b);i++){
            for(int j=0;j<g;j++) tmp[j]=0;
            sum[i]=0;
            for(int j=0;j<b;j++) if(i&(1<<j)){
                for(int k=0;k<g;k++) tmp[k]+=bag[j][k];
            }
            for(int k=0;k<g;k++) sum[i]+=tmp[k]/s;
        }
        for(int i=0;i<(1<<b);i++) dps[i][0]=dps[i][1]=-10000;
        dfs(0,0,1,-10000,10000);
        printf("%d\n",dps[0][0]);
    }
    return 0;
}

