#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int g,b,s;
int bag[25][10];
int now[10];
int dps[1<<21][2];

int dfs(int sta,int who){
	int tmp=0,cha=0;
	for(int i=0;i<g;i++) tmp+=now[i]/s,now[i]=now[i]%s;
	if(who) cha-=tmp;else cha+=tmp;
	if(!tmp) who=!who;
	if(dps[sta][who]!=-10000) return cha+dps[sta][who];
	if(who){
		if(sta==(1<<b)-1) return cha;
		int ans=10000;
		int dp[10];
		for(int i=0;i<g;i++) dp[i]=now[i];
		for(int i=0;i<b;i++){
			if(!(sta&(1<<i))){
				for(int j=0;j<g;j++) now[j]=dp[j]+bag[i][j];
				ans=min(ans,dfs(sta|(1<<i),who));
			}
		}
		dps[sta][who]=ans;
		return ans+cha;
	}
	else{
		if(sta==(1<<b)-1) return cha;
		int ans=-10000;
		int dp[10];
		for(int i=0;i<g;i++) dp[i]=now[i];
		for(int i=0;i<b;i++){
			if(!(sta&(1<<i))){
				for(int j=0;j<g;j++) now[j]=dp[j]+bag[i][j];
				ans=max(ans,dfs(sta|(1<<i),who));
			}
		}
		dps[sta][who]=ans;
		return ans+cha;
	}
}

int main(){
	freopen("a.txt","r",stdin);
	freopen("c.txt","w",stdout);
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
		for(int i=0;i<(1<<21);i++) dps[i][0]=dps[i][1]=-10000;
		memset(now,0,sizeof(now));
		dfs(0,1);
		printf("%d\n",dps[0][0]);
	}
    return 0;
}

