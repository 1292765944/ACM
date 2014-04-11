#include <cstdio>
#include <string.h>
#include <algorithm>
#include <string>
using namespace std;
const int Maxn = 120;
const int INF = 1200000000;
int a[Maxn][Maxn];
bool bi[Maxn];
int now[Maxn];
int n,m,ans;

void check(int ss){
	int sum = 0;
	for (int i=1;i<=ss;++i){
		int tmp = INF;
		for (int j=1;j<=ss;++j)
			if (i!=j) tmp=min(tmp,a[now[i]][now[j]]);
		sum+=tmp;
	}
	ans = max(ans,sum);
}

void dfs(int k,int sum){
	if (sum>1) check(sum);
	if (k>n) return;
	bool bb=true;
	for (int i=1;i<=sum;++i)
		if (a[now[i]][k]==0){
			bb=false;
			break;
		}
	if (bb){
		now[sum+1]=k;
		dfs(k+1,sum+1);
	}
	dfs(k+1,sum);
}
int main(){
	int p1,p2,p3;
	while (scanf("%d%d",&n,&m)==2){
		for (int i=1;i<=n;++i)
			memset(a,0,sizeof(a));
			for (int i=1;i<=m;++i){
				scanf("%d%d%d",&p1,&p2,&p3);
				a[p1][p2]=a[p2][p1]=p3;
			}
		ans = 0;
		memset(bi,false,sizeof(bi));
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}


