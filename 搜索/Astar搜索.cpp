题目大意:给定一个n*m，矩阵上每个点都有一个数字,数字范围是1到k，某个数字相同的连通块如果块数大于3，那么我们就可以选择消掉这个连通块，分数是块数的平方，问最优策略下消的最高分数是多少？n,m <= 8

#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
int n,m,k;
int g[10][10];
int best;
int total;
int h[8]={1,-1,0,0,1,1,-1,-1};
int gg[8]={0,0,1,-1,1,-1,1,-1};

int maxsum(){//计算此状态的最大获利（是一个剪枝）
	int res[10]={0},i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(g[i][j])
				res[g[i][j]]++;
	int s=0;
	for(i=1;i<=k;i++)
		s+=res[i]*res[i];
	return s;
}

void calsum(int u,int v,bool visit[10][10],int s){//DFS搜与某一点相邻的所有点
	int xx,yy,i;
	visit[u][v]=true;
	g[u][v]=0;
	total++;
	for(i=0;i<8;i++){
		xx=u+h[i];
        yy=v+gg[i];
        if(xx<=0 || xx>n || yy<=0 || yy>m)
            continue;
        if(!g[xx][yy] || visit[xx][yy])
            continue;
        if(g[xx][yy]!=s)
            continue;
		calsum(xx,yy,visit,s);
	}
}

void change(){//根据题目要求需要没消一次方块就下移左移
    int k=n,i,j;
    bool flag[10]={0};

    for(i=1;i<=m;i++){
        k=n;
        for(j=n;j>=1;j--){
            g[k][i]=g[j][i];
            if(j<k)
                g[j][i]=0;
            if(g[k][i]){
                k--;
                flag[i]=true;
            }
        }
    }

    k=1;
    for(i=1;i<=m;i++){
        if(flag[i]){
            if(i>k){
                for(j=1;j<=n;j++){
                    g[j][k]=g[j][i];
                    g[j][i]=0;
                }
            }
            k++;
        }
    }
}

void dfs(int now){//主搜函数
    bool visit[10][10];
    int i,j,p,q;
    int tem[10][10];

	if(maxsum()+now<=best)
		return;

    memcpy(tem,g,sizeof(tem));

    if(best<now)
        best=now;

    memset(visit,0,sizeof(visit));
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){

            memcpy(g,tem,sizeof(g));
            total=0;
            if(g[i][j] && !visit[i][j]){                
				calsum(i,j,visit,g[i][j]);
            }
            if(total<3)
                continue;
            change();
            dfs(now+total*total);
        }
}

int main(){
    int i,j;
    while(scanf("%d %d %d",&n,&m,&k)==3){
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++){
                scanf("%d",&g[i][j]);
            }
        best=0;
        dfs(0);
        printf("%d\n",best);
    }
}
