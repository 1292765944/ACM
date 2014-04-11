1.POJ 3680

题意：给出一些开区间，每个区间配一个权值。
问：在区间每个点不被重叠k次能取到的最大权值。

建图很巧妙

先离散化区间端点。从0->1,1->2,~~~~~n->n+1每条边容量为k，费用为0，

对于每条线段，他的两个端点连边容量为1，费用-w

然后跑一遍最小费用流

算法正确性证明：

如果两个区间没有交集，那么代表它们的边可以出现在同一增广路上，这一点显然。否则，它们就在不同的增广路上。每一个区间对应的边的容量都是1，这样，最后的流量就是被选出的两两有交集的区间的数量。受到(0,1,k,0)这条边的容量限制，这个值刚好不大于k.区间的权都是正的，因此选取的区间多多益善，所以流量必然最大。

 （对于每次选取的增广路中总存在一个区间，在每次增广所得区间都与这个区间有交集）


2.二分图匹配

#include<stdio.h>
#include<string.h>
int g,b,m;
int map[201][201];
int cx[210],cy[210];
bool mk[210];
int path(int u){
	int i;
	for(i=1;i<=b;i++){
		if(map[u][i] && mk[i]==0){
			mk[i]=1;
			if(cy[i]==0 || path(cy[i])){
				cx[u]=i;
				cy[i]=u;
				return 1;
			}
		}
	}
	return 0;
}

int maxmatch(){
	int i,j,u,v,sum=0;
	memset(cx,0,sizeof(cx));
	memset(cy,0,sizeof(cy));
	for(i=1;i<=g;i++){
		if(cx[i]==0){
			memset(mk,0,sizeof(mk));
			sum+=path(i);
		}
	}
	return sum;
}
int main(){
	int i,j,u,v,t=1;
	while(scanf("%d %d %d",&g,&b,&m) && !(g==0 && b==0 && m==0)){
		memset(map,0,sizeof(map));
		for(i=1;i<=g;i++)
			for(j=1;j<=b;j++)
				map[i][j]=1;
		for(i=1;i<=m;i++){
			scanf("%d %d",&u,&v);
			map[u][v]=0;
		}
		printf("Case %d: %d\n",t++,g+b-maxmatch());
	}
}

3.二分图染色找奇圈
#include<cstdio>
#include<string.h>
using namespace std;
int map[210][210],col[210];
int n,m;
int cx[210],cy[210];
bool mk[210];
bool dfs(int now){
	int i;
	for(i=1;i<=n;i++)
		if(map[now][i]){
			if(col[i]==-1){
				col[i]=!col[now];
				bool tem=dfs(i);
				if(tem==0)
					return 0;                   //一开始WA这里了
			}
			else if(col[i]==col[now])
				return 0;
		}
	return 1;
}
int path(int u){
	int i;
	for(i=1;i<=n;i++){
		if(map[u][i] && mk[i]==0){
			mk[i]=1;
			if(cy[i]==0 || path(cy[i])){
				cx[u]=i;
				cy[i]=u;
				return 1;
			}
		}
	}
	return 0;
}

int maxmatch(){
	int i,j,u,v,sum=0;
	memset(cx,0,sizeof(cx));
	memset(cy,0,sizeof(cy));
	for(i=1;i<=n;i++){
		if(cx[i]==0){
			memset(mk,0,sizeof(mk));
			sum+=path(i);
		}
	}
	return sum;
}
int main(){
	int i,j,u,v;
	while(scanf("%d %d",&n,&m)==2){
		if(n==1){
			printf("No\n");
			continue;
		}

		memset(map,0,sizeof(map));
		for(i=1;i<=m;i++){
			scanf("%d %d",&u,&v);
			map[u][v]=map[v][u]=1;
		}
		memset(col,-1,sizeof(col));
		col[1]=1;
		if(dfs(1)==0){
			printf("No\n");
			continue;
		}
		printf("%d\n",maxmatch()/2);
	}
}

