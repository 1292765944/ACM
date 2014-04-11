单调队列问题
1.HDU 4362
题意：挖宝石，宝石都出现在一条直线上，每次出现n个宝石，只能挖其中一个，剩下消失。总共有m次机会。精力消耗有路程的消耗和挖宝石的时候消耗，求最小消耗。

题解：dp。维护两个最值，把问题分成从位置大于和小于目前位置两种情况讨论。dp[i][j]代表第i段时间挖第j个石头消耗最小。

　　　首先只考虑位置比目前小的情况，dp[i][j] = min{dp[i-1][k]+p[i][j]-p[i-1][k]+e[i][j]} = min{dp[i-1][k]-p[i-1][k]}+p[i][j]+e[i][j];用一点单调队列的思想。


 单调队列+DP


设dp[i][j]表示第i批龙珠中取第j个需要花费的最小体力。

dp[i][j] = min{ dp[i-1][k] + abs(pos[i-1][k]-pos[i][j]) } + cost[i][j];

如果枚举k的话总复杂度位m*n*n，会超时。

可以看出若每个状态只由上一层位置在其左边的状态的转移而来的话：  

dp[i][j]

= min { dp[i-1][k] + pos[i][j] - pos[i-1][k] } + cost[i][j]

= min { dp[i-1][k] - pos[i-1][k] } + pos[i][j] + cost[i][j]

dp[i-1][k]-pos[i-1][k]是个确定的值，就是相当于求位置在pos[i][j]左边的上一层状态中值最小的，可以用个单调队列维护。由右边转移来的类似，再处理一遍右边转移来的取最优。

因为要对同一层的点排序，所以总复杂度是m*n*logn。

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int p,e;
}ball;

const int M = 55;
const int N = 1010;
ball b[M][N];
int m,n,x;
int dp[M][N];

int cmp(const void *a, const void *b)
{
    return (*(ball *)a).p - (*(ball *)b).p;
}

int fab(int a) {return a < 0 ? -a : a;}
int min(int a, int b) {return a < b ? a : b;}

void solve()
{
    int i,j,k;
    int mm;
    for(i = 1; i < m; i++)
    {
        k = 0;
        mm = 10000000;
        for(j = 0; j < n; j++)
        {
            while(k < n && b[i][j].p >= b[i-1][k].p)
            {
                mm = min(dp[i-1][k]-b[i-1][k].p, mm);
                k++;
            }
            dp[i][j] = mm+b[i][j].p+b[i][j].e;
        }
        k = n-1;
        mm = 10000000;
        for(j = n-1; j >= 0; j--)
        {
            while(k >= 0 && b[i][j].p <= b[i-1][k].p)
            {
                mm = min(dp[i-1][k]+b[i-1][k].p, mm);
                k--;
            }
            dp[i][j] = min(dp[i][j], mm-b[i][j].p+b[i][j].e);
        }
    }
}

int main()
{
    int t;
    int i,j;
    scanf("%d", &t);
    while(t-- && scanf("%d%d%d", &m, &n, &x))
    {
        for(i = 0; i < m; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &b[i][j].p);
        for(i = 0; i < m; i++)
        {
            for(j = 0; j < n; j++)
                scanf("%d", &b[i][j].e);
            qsort(b[i], n, sizeof(b[1][1]), cmp);
        }
        for(i = 0; i < n; i++)
            dp[0][i] = fab(x-b[0][i].p)+b[0][i].e;
        solve();
        int min1 = dp[m-1][0];
        for(i = 1; i < n; i++)
            min1 = min(min1, dp[m-1][i]);
        printf("%d\n", min1);
    }
    return 0;
}

HDU 4373

手写队列版本

题目大意：一个n*m的格子，每一行只能朝一个方向走，最多走t步，问最多能得多少分。

     状态转移dp[i][j]表示第到了第i行，起点在j位置，但是还没有开始走的最大值。

      从左往右走，dp[i][j]=max(dp[i-1][k]+sum[i-1][j]-sum[i-1][k-1])  (j-k<=t)  

                                       =max(dp[i-1][k]-sum[i-1][k-1])+sum[i-1][j];

      max中是个已求的值，max外面是只与j有关的值。可以用单调队列维护。

#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10005
typedef long long LL;
const LL INF=0x7f7f7f7f7f7f7f7fLL;
using namespace std;
int g[105][N];
LL dp[105][N],sum[105][N];
int q[N];
int n,m,x,tim;
int main()
{
    freopen("in.txt","r",stdin);

    while(scanf("%d %d %d %d",&n,&m,&x,&tim)!=EOF)
    {
        for(int i=1; i<=n; i++)
        {
            sum[i][0]=0;
            for(int j=1; j<=m; j++)
            {
                scanf("%d",&g[i][j]);
                sum[i][j]=sum[i][j-1]+g[i][j];
            }
            sum[i][m+1]=0;
        }
        int front=0,rear=-1,b;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                dp[i][j]=-INF;
        dp[1][x]=0;
        for(int i=2;i<=n+1;i++)
        {
            front=0;rear=-1;
            for(int j=1;j<=m;j++)
            {
                while(rear>=front &&
                      dp[i-1][q[rear]]-sum[i-1][q[rear]-1]<=dp[i-1][j]-sum[i-1][j-1])rear--;
                q[++rear]=j;            //注意这里的-1

                while(rear>=front && j-q[front]>tim)front++;
                b=q[front];
                dp[i][j]=dp[i-1][b]+sum[i-1][j]-sum[i-1][b-1];
            }
            front=0;rear=-1;
            for(int j=m;j>=1;j--)
            {
                while(rear>=front &&
                      dp[i-1][q[rear]]+sum[i-1][q[rear]]<=dp[i-1][j]+sum[i-1][j])rear--;
                q[++rear]=j;

                while(rear>=front && q[front]-j>tim)front++;
                b=q[front];
                dp[i][j]=max(dp[i][j],dp[i-1][b]+sum[i-1][b]-sum[i-1][j-1]);
            }
        }
        LL ans=-INF;
        for(int i=1;i<=m;i++)
            ans=max(ans,dp[n+1][i]);
        printf("%I64d\n",ans);
    }
    return 0;
}


POJ 2823

这道题就是用单调队列来维护，但是用G++交TLE，用c++5000多ms
#include<stdio.h>
int a[1000009],que[1000009];
int main(){
	int n,k,i,head,tail,flag=1,f;
	scanf("%d %d",&n,&k);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	head=1;tail=0;
	f=1;
	for(i=1;i<=n;i++){
		while(tail>=head && a[i]<a[que[tail]])	//队首存放最小值
			tail--;
		que[++tail]=i;
		if(i>=k){
			if(que[head]<f)
				head++;
			if(flag){
				printf("%d",a[que[head]]);
				flag=0;
			}
			else
				printf(" %d",a[que[head]]);
			f++;
		}
	}
	printf("\n");

	head=1;tail=0;
	flag=1;
	f=1;
	for(i=1;i<=n;i++){
		while(tail>=head && a[i]>a[que[tail]])	
			tail--;
		que[++tail]=i;
		if(i>=k){
			if(que[head]<f)
				head++;
			if(flag){
				printf("%d",a[que[head]]);
				flag=0;
			}
			else
				printf(" %d",a[que[head]]);
			f++;
		}
	}
	printf("\n");
}


POJ 3162
题意：对一棵树，求出从每个结点出发能到走的最长距离（每个结点最多只能经过一次），将这些距离按排成一个数组得到d[1],d[2],d[3]……d[n] ，在数列的d中求一个最长的区间，使得区间中的最大值与最小值的差不超过m。

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 1000001
int n,m,e;
int first[N],next[N<<1],v[N<<1],w[N<<1];
int dx[N],dy[N],d[N];
int qmin[N],qmax[N];
void init()
{
    e=0;
    memset(first+1,-1,sizeof(first[0])*n);
}
void add(int a,int b,int c)
{
    v[e]=b;
    w[e]=c;
    next[e]=first[a];
    first[a]=e++;
}
void dfs(int a,int fa,int dist,int *d)
{
    int i,b;
    for(i=first[a];~i;i=next[i])
    {
        b=v[i];
        if(b^fa)    dfs(b,a,d[b]=dist+w[i],d);
    }
}
void solve()
{
    int i,j,front1,front2,rear1,rear2;
    int ans=0;
    front1=rear1=0;
    front2=rear2=0;
    for(i=1,j=1;j<=n;j++)  //i记录的是当前单调队列的开始元素，j是当前元素
    {
        while(rear1>front1 && d[qmin[rear1-1]]>=d[j]) rear1--;
        qmin[rear1++]=j;

        while(rear2>front2 && d[qmax[rear2-1]]<=d[j]) rear2--;
        qmax[rear2++]=j;

        if(d[qmax[front2]]-d[qmin[front1]]>m)
        {
            ans=max(ans,j-i);//不满足条件的时候 记录之前满足条件的长度
            while(d[qmax[front2]]-d[qmin[front1]]>m)
            {
                i=min(qmin[front1],qmax[front2])+1; //此时需要找下一个开始位置
                while(front1<rear1&&qmin[front1]<i)   front1++;
                while(front2<rear2&&qmax[front2]<i)   front2++;
            }
        }
    }
    ans=max(ans,j-i);
    printf("%d\n",ans);
}
int main()
{
    int i,a,b,c,x,y;
    while(~scanf("%d%d",&n,&m))
    {
        init();
        for(a=2;a<=n;a++)
        {
            scanf("%d%d",&b,&c);
            add(a,b,c);
            add(b,a,c);
        }
        dfs(1,0,dx[1]=0,dx);

        for(x=1,i=2;i<=n;i++)
        {
            if(dx[i]>dx[x]) x=i;
        }
        dfs(x,0,dx[x]=0,dx);
        for(y=1,i=2;i<=n;i++)
        {
            if(dx[i]>dx[y]) y=i;
        }
        dfs(y,0,dy[y]=0,dy);
        for(int i=1;i<=n;i++)   d[i]=max(dx[i],dy[i]);
        solve();
    }
    return 0;
}
这道题另一种写法

这是2011福州区域赛的题目，咋一看蛮难的，其实是个大水题，poj也有类似的题目，应该说是改编过来的吧。
好了，讲讲我是怎么做的吧
1：利用树的最长路的结论我们首先预处理出num数组
2：由于后面需要查询区间最值，所以先用RMQ预处理num【】，后面查询的时候就可以做到O(1)查询，如果用线段树的话复杂度会太大
3：对于每个询问，可以做到O(n)回答，维护两个指针l,r 如果当前区间满足条件r++,否则l++，每个点都被插入删除一次，区间最值的查询是O(1）的，所以询问的复杂度是
q*n即500*50000.
总复杂度是nlog(n)+q*n
所以就是q*n的复杂度，即500*50000，时限两秒，小轻松啊~

[cpp] 
#include<cstdio> 
#include<cstring> 
#include<algorithm> 
using namespace std; 
const int inf = ~0u>>2; 
const int maxn = 50010; 
int n,m; 
struct Edge{ 
    int v,w,next; 
}edge[2*maxn]; 
int head[maxn],E,num[maxn]; 
void add_edge(int a,int b,int w) 
{ 
    edge[E].v=b; 
    edge[E].w=w; 
    edge[E].next=head[a]; 
    head[a]=E++; 
} 
int dis1[maxn],dis2[maxn]; 
bool vis[maxn]; 
int q[maxn]; 
void bfs(int s,int &ss,int dist[])   { 
    fill(dist,dist+n+1,inf); 
    fill(vis,vis+n+1,false); 
    vis[s]=true; 
    dist[s]=0; 
    int front(0),tail(0),u,v,w; 
    q[0]=s;int Max=0; 
    while(front<=tail)    { 
        u=q[front++]; 
        for(int i=head[u];i!=-1;i=edge[i].next)    { 
            v=edge[i].v,w=edge[i].w; 
            if(vis[v]) continue; 
            vis[v]=true; 
            dist[v]=dist[u]+w; 
            if(dist[v]>Max)      { 
                Max=dist[v]; 
                ss=v; 
            } 
            q[++tail]=v; 
        } 
    } 
} 
int LOG[2*maxn]; 
int dp1[20][2*maxn]; 
int dp2[20][2*maxn]; 
inline int min(int a,int b){ 
    return a<b?a:b; 
} 
inline int max(int a,int b){ 
    return a>b?a:b; 
} 
void rmq_init(int n) 
{ 
    int i,j; 
    for(j=1;j<=n;j++)   { 
        dp1[0][j]=num[j]; 
        dp2[0][j]=num[j]; 
    } 
    for(j=1;j<=LOG[n];j++)   { 
        int limit=n+1-(1<<j); 
        for(i=1;i<=limit;i++)    { 
            int x=i+(1<<j>>1); 
            dp1[j][i]=min(dp1[j-1][x],dp1[j-1][i]); 
            dp2[j][i]=max(dp2[j-1][x],dp2[j-1][i]); 
        } 
    } 
} 
int rmq_min(int l,int r) 
{ 
    int m=LOG[r-l+1]; 
    return min(dp1[m][l],dp1[m][r-(1<<m)+1]); 
} 
int rmq_max(int l,int r) 
{ 
    int m=LOG[r-l+1]; 
    return max(dp2[m][l],dp2[m][r-(1<<m)+1]); 
} 
int main() 
{ 
    int q; 
    LOG[0]=-1; 
    for(int i=1;i<2*maxn;i++) LOG[i]=LOG[i>>1]+1; 
    while(scanf("%d%d",&n,&q),n||q) 
    { 
        E=0;fill(head,head+n+1,-1); 
        for(int i=2,a,b,w;i<=n;i++) 
        { 
            scanf("%d%d%d",&a,&b,&w); 
            add_edge(a,b,w); 
            add_edge(b,a,w); 
        } 
        int ss,tt; 
        bfs(1,ss,dis1); 
        bfs(ss,tt,dis1); 
        bfs(tt,ss,dis2); 
        for(int i=1;i<=n;i++)     num[i]=max(dis1[i],dis2[i]); 
        rmq_init(n); 
        while(q--)    { 
            scanf("%d",&m); 
            int ans=0; 
            int l=1,r=1,mx,mi; 
            while(r<=n)    { 
                mx=rmq_max(l,r);    //如果卡内存，这里可以用线段树查询
                mi=rmq_min(l,r); 
                if(mx-mi<=m)    { 
                    ans=max(ans,r-l+1); 
                    r++; 
                } 
                else l++; 
            } 
            printf("%d\n",ans); 
        } 
    } 
    return 0; 
} 
HDU 4122
题意：m个时间点有做蛋糕不同花费，某个人在某个时间上取货，如果在之前取货，要加上两个时间差，求问最小费用
一种解法是单调队列

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;

char Month[13][9]={"","Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov" , "Dec"};
__int64 days[12]={31,28,31,30,31,30,31,31,30,31,30,31};


inline __int64 leap(__int64 year)
{
    return ((year%4==0&&year%100!=0)||year%400==0);
}

struct DD
{
    __int64 year,month,day,hour;
};

__int64 data__int64(DD a)
{
    __int64 ret=0;//(a.year-2000)*365+(a.year-2000)/4-(a.year-2000)/100+(a.year-2000)/400;
    int i;
    for(i=2000;i<a.year;i++)
        ret+=365+leap(i);
    days[1]+=leap(a.year);
    for(i=0;i<a.month-1;ret+=days[i++]);
    days[1]=28;
    return (ret+a.day-1)*24+a.hour+1;
}

struct data1
{
    __int64 hour;
    __int64 v;
}need[100099];

struct data2
{
    __int64 ben;
    __int64 hour;
}qq[100999];

__int64 cmp(data1 a,data1 b)
{
    return a.hour<b.hour;
}

int main()
{
    __int64 n,m;
    while(scanf("%I64d%I64d",&n,&m))
    {
        if(n==0&&m==0)return 0;
        
        __int64 i,j,year,mon,day,time;
        
        char mm[9];
        DD temp;
        for(i=1;i<=n;i++)
        {
            scanf("%s",mm);
            for(j=1;j<=12;j++)
            {
                if(strcmp(Month[j],mm)==0){
                    temp.month=j;
                    break;
                }
            }
            scanf("%I64d%I64d%I64d",&temp.day,&temp.year,&temp.hour);
            __int64 temp1=need[i].hour=data__int64(temp);
            scanf("%I64d",&need[i].v);
        }
        
        sort(&need[1],&need[n+1],cmp);
        
        __int64 max,pri,cost;
        scanf("%I64d%I64d",&max,&pri);
        
        __int64 start,top,tail;
        top=tail=start=1;
        
        
        __int64 all=0;
        for(i=1;i<=m;i++)
        {
            scanf("%I64d",&cost);
            while(top<tail&&qq[tail-1].ben+(i-qq[tail-1].hour)*pri>=cost)tail--;
            
            qq[tail].ben=cost;qq[tail].hour=i;tail++;
            
            while(start<=n&&need[start].hour==i)
            {
                while((top<tail-1)&&(qq[top].hour+max<need[start].hour)) top++;  

                __int64 temp=need[start].hour-qq[top].hour;

                all+=(qq[top].ben+(need[start].hour-qq[top].hour)*pri)*need[start].v;
                start++;
            }
        }
        
        printf("%I64d\n",all);
    }
}
也可以线段树
先按最后一天作为要买东西的时间，对前面费用都加上到最后一天的保质期花费，建线段的；
查找当前day -----day-T的区间内的最小值，减去当前day多加的保质期费用，就是所求的最优单价
