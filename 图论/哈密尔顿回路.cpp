/*HDU 3681 题意是已知一幅矩阵迷宫，給起点，开始时充满电，要求是遍历给定的点，每移动一次花费1，迷宫中有若干充电池可充满电（每个充电池只能用一次），求原始电量最少是多少*/

/*首先抽象出起点、终点、充电池，建立他们的最短路径图，二分枚举原始电量 从而转化为 哈密尔顿回路的状态DP问题 。这样建图原理是：对于原图当前用不用充电池 在新图中 我们可以用两种不同的边来表示*/
#include"iostream"
#include<stdio.h>
#include<queue>
#include<memory.h>
using namespace std;
const int INF=10000000;
int c[20][2];
char map[20][20];
int dis[20][20];
int id[20][20];
int ok[20][20];
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int n,m,s,cnt;
int dp[1<<16][16];
struct Node
{
    int x,y,d;
};
void bfs(int x,int y)
{
    Node p,q;
    memset(ok,0,sizeof(ok));
    ok[x][y]=1;
    p.x=x;
    p.y=y;
    p.d=0;
    queue<Node> Q;
    Q.push(p);
    int i,j,k;
    while(!Q.empty())
    {
        p=Q.front();
        Q.pop();
        if(id[p.x][p.y]!=-1)
            dis[id[x][y]][id[p.x][p.y]]=p.d;
        for(i=0;i<4;i++)
        {
            q.x=p.x+dir[i][0];
            q.y=p.y+dir[i][1];
            q.d=p.d+1;
            if(q.x>=0&&q.x<n&&q.y>=0&&q.y<m&&!ok[q.x][q.y]&&map[q.x][q.y]!='D')
            {
                ok[q.x][q.y]=1;
                Q.push(q);
            }
        }
    }
}
bool solve(int mid)
{
    int i,j,k;
    for(i=0;i<(1<<cnt);i++)
        for(j=0;j<=cnt;j++)
            dp[i][j]=-1;
    dp[0][0]=mid;
    for(i=0;i<(1<<cnt);i++)
        for(j=0;j<=cnt;j++){
            if((i&s)==s&&dp[i][j]!=-1)
                return true;
            if(dp[i][j]!=-1)
            {
                for(k=1;k<=cnt;k++)
                {
                    if(!(i&(1<<(k-1)))&&dp[i][j]>=dis[j][k])
                    {
                        if(dp[i|(1<<(k-1))][k]==-1||dp[i|(1<<(k-1))][k]<dp[i][j]-dis[j][k])
                        dp[i|(1<<(k-1))][k]=dp[i][j]-dis[j][k];
                        if(map[c[k][0]][c[k][1]]=='G')
                            dp[i|(1<<(k-1))][k]=mid;
                    }
                }
            }
        }
    return false;
}
int main()
{
    int i,j,k;
    while(scanf("%d%d",&n,&m),n||m)
    {
        s=0;
        cnt=0;
        for(i=0;i<n;i++)
            scanf("%s",map[i]);
        memset(id,-1,sizeof(id));
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                if(map[i][j]=='G'){
                    id[i][j]=++cnt;
                    c[cnt][0]=i;
                    c[cnt][1]=j;
                }
                else if(map[i][j]=='Y'){
                    id[i][j]=++cnt;
                    c[cnt][0]=i;
                    c[cnt][1]=j;
                    s|=(1<<(cnt-1));
                }
                else if(map[i][j]=='F'){
                    id[i][j]=0;
                    c[0][0]=i;
                    c[0][1]=j;
                }
            }
        for(i=0;i<20;i++)
            for(j=0;j<20;j++)
                dis[i][j]=INF;
        for(i=0;i<=cnt;i++)
            bfs(c[i][0],c[i][1]);
        int left=0,right=n*m*cnt,re=-1;
        while(left<=right)
        {
            int mid=(left+right)/2;
            if(solve(mid))
            {
                re=mid;
                right=mid-1;
            }
            else
                left=mid+1;
        }
        printf("%d\n",re);
    }
    return 0;
}

/*HDU 4284 一道类似的哈密尔顿回路的状态DP问题，常见做法有BFS转移和直接循环装移，另外如果只是判断是否有解DFS更快，而求最值用BFS*/

#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1<<15
using namespace std;
typedef unsigned short us;
int m,n,mon,Q;
int map[103][103];
int dp[15][N];
int num[20],c[20],d[20];
bool vis[15][N];
struct Point{
    us pos,id;
}q[15*N];
int head,tail;
void bfs(){
    int i;
    while(head!=tail){
        us pos=q[head].pos,sta=q[head].id;
        head=(head+1)%(15*N);
        vis[pos][sta]=0;
        for(i=0;i<Q;i++){
            if((sta&(1<<i))!=0)continue;
            if(dp[pos][sta]-map[num[pos]][num[i]]<d[i])continue;
            if(dp[pos][sta]-map[num[pos]][num[i]]-d[i]+c[i]>dp[i][(sta|(1<<i))]){
                dp[i][(sta|(1<<i))]=dp[pos][sta]-map[num[pos]][num[i]]-d[i]+c[i];
                if(!vis[i][(sta|(1<<i))]){
                    vis[i][(sta|(1<<i))]=1;
                    q[tail].id=(sta|(1<<i));
                    q[tail].pos=i;
                    tail=(tail+1)%(15*N);
                }
            }
        }
    }
}
int main(){
    int t,T,u,v,w,i,j,k;
    scanf("%d",&T);
    for(t=1;t<=T;t++){
        scanf("%d %d %d",&n,&m,&mon);
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++)
                map[i][j]=1e9;
            map[i][i]=0;
        }
        for(i=1;i<=m;i++){
            scanf("%d %d %d",&u,&v,&w);
            map[u][v]=map[v][u]=min(map[u][v],w);
        }
        for(k=1;k<=n;k++)
            for(i=1;i<=n;i++)
                for(j=1;j<=n;j++)
                    map[j][i]=map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
        scanf("%d",&Q);
        memset(vis,0,sizeof(vis));
        memset(dp,-1,sizeof(dp));
        head=tail=0;
        for(i=0;i<Q;i++){
            scanf("%d %d %d",&num[i],&c[i],&d[i]);
            if(mon>=map[1][num[i]]+d[i]){
                q[tail].id=1<<i;
                q[tail].pos=i;
                tail+=1;
                vis[i][1<<i]=1;
                dp[i][1<<i]=mon-map[1][num[i]]-d[i]+c[i];
            }
        }
        bfs();
        int flag=0;
        for(i=0;i<Q;i++)
            if(dp[i][(1<<Q)-1]>=map[num[i]][1]){
                flag=1;
                break;
            }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
}

/*上一道题的直接转移版本*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 101;

int id[MAXN], id2[MAXN];
int C[MAXN], D[MAXN];
int g[MAXN][MAXN];
int f[1<<15][15];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, money;
		scanf("%d%d%d", &n, &m, &money);
		memset(g, -1, sizeof(g));
		for (int i = 0; i <= n; ++i) g[i][i] = 0;
		for (int i = 0, u, v, w; i < m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			--u, --v;
			if (g[u][v] == -1 || g[u][v] > w) g[u][v] = g[v][u] = w;
		}
		int h;
		scanf("%d", &h);
		for (int i = 0; i < h; ++i) {
			int num, c, d;
			scanf("%d%d%d", &num, &c, &d);
			--num;
			id[num] = i;
			id2[i] = num;
			C[i] = c;
			D[i] = d;
		}

		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) 
				for (int j = 0; j < n; ++j) {
					if (g[i][k] != -1 && g[k][j] != -1) {
						int t = g[i][k] + g[k][j];
						if (g[i][j] == -1 || g[i][j] > t) g[i][j] = t;
					}
				}
		}
		memset(f, -1, sizeof(f));
		for (int i = 0; i < h; ++i) {
			if (money >= g[0][ id2[i] ] + D[i] && g[0][ id2[i] ] != -1) {
				f[1<<i][i] = money - g[0][ id2[i] ] - D[i] + C[i];
			}
		}
		int all = (1<<h) - 1;
		for (int os = 1; os <= all; ++os) {
			for (int oi = 0; oi < h; ++oi) {
				if (!(os & (1<<oi)) || f[os][oi] < 0) continue;
				for (int i = 0; i < h; ++i) {
					if (os & (1<<i)) continue;
					int s = os | (1<<i);
					int fm = f[os][oi];
					if (fm >= g[ id2[oi] ][ id2[i] ] + D[i]) {
						int t = fm - g[ id2[oi] ][ id2[i] ] - D[i] + C[i];
						if (t >= 0 && (f[s][i] < 0 || f[s][i] < t)) {
							f[s][i] = t;
						}
					}
				}
			}
		}
		int ans = -1;
		for (int i = 0; i < h; ++i) {
			if (f[all][i] < 0) continue;
			if (f[all][i] >= g[ id2[i] ][ 0 ]) {
				ans = 1;
				break;
			}
		}
		if (ans < 0) puts("NO");
		else puts("YES");
	}
	return 0;
}





