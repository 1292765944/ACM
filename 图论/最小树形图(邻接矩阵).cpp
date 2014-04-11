#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define maxn 120
int n,m;
struct node
{
    int x,y;
}a[maxn];
inline double get_dis(node a,node b)
{
    return sqrt((double)(a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y));
}
double map[maxn][maxn];
bool flag[maxn];
int pre[maxn];
void dfs(int x)
{
    flag[x]=true;
    for(int i=1; i<=n; i++)
        if(!flag[i] && fabs(map[x][i]+1)>1e-8)
            dfs(i);
}
bool check()//检查联通
{
    memset(flag,0,sizeof(flag));
    dfs(1);
    for(int i=1; i<=n; i++)
        if(!flag[i])return false;
    return true;
}
double solve()
{
    memset(flag,0,sizeof(flag));//flag是true的点是被去掉的点
    int i,j,k;
    double ans=0;
    while(1)
    {
        for(i=2; i<=n; i++)
            if(!flag[i])
            {
                pre[i]=i;
		map[i][i]=-1;
                for(j=1; j<=n; j++)
                if(!flag[j] && fabs(map[j][i]+1)>1e-8)
                    {
                        if(fabs(map[pre[i]][i]+1)<1e-8 || map[pre[i]][i]-map[j][i]>1e-8)
                            pre[i]=j;
                    }
            }
        for(i=2; i<=n; i++)
            if(!flag[i])
            {
                bool mark[maxn];
                memset(mark,0,sizeof(mark));
                for(j=i; j!=1&&!mark[j]; mark[j]=true,j=pre[j]);//寻找环，返回在环内的一点（注意从i出发能找到换不代表n在环内）
                if(j==1)continue;
                i=j;
                ans+=map[pre[i]][i];
                for(j=pre[i]; j!=i; j=pre[j])
                {
                    ans+=map[pre[j]][j];
                    flag[j]=true;
                }
                for(j=1; j<=n; j++)if(!flag[j] && fabs(map[j][i]+1)>1e-8)
                        map[j][i]-=map[pre[i]][i];
                for(j=pre[i]; j!=i; j=pre[j])
                {
                    for(k=1; k<=n; k++)if(!flag[k] && fabs(map[j][k]+1)>1e-8 && (fabs(map[i][k]+1)<1e-8 || map[i][k]-map[j][k]>1e-8))
                            map[i][k]=map[j][k];
                    for(k=1; k<=n; k++)if(!flag[k] && fabs(map[k][j]+1)>1e-8 && (fabs(map[k][i]+1)<1e-8 || map[k][i]-map[k][j]+map[pre[j]][j]>1e-8))
                            map[k][i]=map[k][j]-map[pre[j]][j];
                }
                break;
            }
        if(i>n)//说明没有环了。
        {
            for(j=2; j<=n; j++)if(!flag[j])
                    ans+=map[pre[j]][j];
            return ans;
        }
    }
}
int main()
{
    int i,j,x,y;
    while(scanf("%d%d",&n,&m)==2)
    {
        for(i=1; i<=n; i++)
            scanf("%d%d",&a[i].x,&a[i].y);
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                map[i][j]=-1;
        for(i=1; i<=m; i++)
        {
            scanf("%d%d",&x,&y);
            if(x==y)continue;//消除自环
            map[x][y]=get_dis(a[x],a[y]);
        }
        if(!check())//检查有向图是否联通
        {
            printf("poor snoopy\n");
        }
        else
        {
            printf("%.2f\n",solve());
        }
    }
}
