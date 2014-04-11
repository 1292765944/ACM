#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#define N 1010
using namespace std;
int x[N],y[N],p[N],vis[N];
double dis[N][N],d[N],mx[N][N];
int main(){
    int t,T,i,j,n;
    double A,B,ans;
    scanf("%d",&T);
    for(t=1;t<=T;t++){
        scanf("%d",&n);
        for(i=1;i<=n;i++)
            scanf("%d %d %d",&x[i],&y[i],&p[i]);
        memset(dis,0,sizeof(dis));
        for(i=1;i<=n;i++)
            for(j=i+1;j<=n;j++)
                dis[i][j]=dis[j][i]=sqrt((double)(x[j]-x[i])*(x[j]-x[i])+(double)(y[j]-y[i])*(y[j]-y[i]));
        for(i=2;i<=n;i++)
            d[i]=dis[1][i];
        for(i=2;i<=n;i++)
            vis[i]=1;
        vis[1]=0;
        B=0;
        for(i=1;i<n;i++){
            double Min=100000000;
            int whi;
            for(j=2;j<=n;j++)
                if(vis[j])
                    if(d[j]<Min){
                        Min=d[j];
                        whi=j;
                    }
            B+=d[whi];
            mx[vis[whi]][whi]=mx[whi][vis[whi]]=Min;
            int pre=vis[whi];
            for(j=1;j<=n;j++){
                if(vis[j]==0 && j!=whi){
                    mx[j][whi]=mx[whi][j]=max(mx[j][pre],mx[pre][whi]);   //这里矩阵mx[i][j]维护最小生成树中i和j之间的最长边
                }
            }
            vis[whi]=0;
            for(j=2;j<=n;j++)
                if(vis[j] && dis[whi][j]<d[j]){
                    d[j]=dis[whi][j];
                    vis[j]=whi;
                }
        }
        ans=0;
        for(i=1;i<=n;i++)
            for(j=i+1;j<=n;j++){
                A=p[i]+p[j];
                double tem=B-mx[i][j];
                if(A/tem>ans)
                    ans=A/tem;
            }
        printf("%.2lf\n",ans);
    }
}
