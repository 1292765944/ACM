1.线段树+扫描线  求矩形周长
#include<cstdio>
#include<algorithm>
#define N 10010
using namespace std;

struct Tree{
    int l,r,num,len,cover;   //num表示区间【l,r】内线段条数，len表示区间【l,r】被占用的总长度 
    bool lb,rb;
}tree[3*N];

struct Line{
    int x,y1,y2,flag;
}l[N];
int y[N];

bool cmp(struct Line a,struct Line b){    //这里表示当2条线段x坐标重合时优先处理是入边的矩形的线段
    if(a.x==b.x)return a.flag>b.flag;
    return a.x<b.x;
}
void build(int s,int t,int id){
    tree[id].l=s,tree[id].r=t;
    tree[id].cover=0,tree[id].lb=0,tree[id].rb=0;
    tree[id].len=0,tree[id].num=0;
    if(s!=t-1){
        int mid=(s+t)>>1;
        build(s,mid,id<<1);
        build(mid,t,id<<1|1);
    }
}
void update(int id){
    if(tree[id].cover>0){
        tree[id].num=tree[id].lb=tree[id].rb=1;
        tree[id].len=y[tree[id].r-1]-y[tree[id].l-1];   //注意这里都要减一
    }
    else if(tree[id].l==tree[id].r-1){
        tree[id].num=tree[id].lb=tree[id].rb=tree[id].len=0;
    }
    else{
        tree[id].lb=tree[id<<1].lb;
        tree[id].rb=tree[id<<1|1].rb;
        tree[id].len=tree[id<<1].len+tree[id<<1|1].len;
        tree[id].num=tree[id<<1].num+tree[id<<1|1].num-tree[id<<1|1].lb*tree[id<<1].rb; //这里合并时要注意
    }
}
void query(int s,int t,int flag,int id){
    if(tree[id].l==s && tree[id].r==t){
        tree[id].cover+=flag;
        update(id);
        return;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(t<=mid)query(s,t,flag,id<<1);
    else if(s>=mid)query(s,t,flag,id<<1|1);
    else{
        query(s,mid,flag,id<<1);
        query(mid,t,flag,id<<1|1);
    }
    update(id);
}
int main(){
    int i,n,x1,x2,y1,y2;
    scanf("%d",&n);
    int cnt=0;
    for(i=1;i<=n;i++){
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        l[cnt].x=x1,l[cnt].y1=y1,l[cnt].y2=y2,l[cnt].flag=1,y[cnt++]=y1;
        l[cnt].x=x2,l[cnt].y1=y1,l[cnt].y2=y2,l[cnt].flag=-1,y[cnt++]=y2;
    }
    sort(y,y+cnt);
    sort(l,l+cnt,cmp);
    int t=unique(y,y+cnt)-y;
    build(1,t,1);

    int ans=0,last=0,lines=0;
    for(i=0;i<cnt;i++){
        int ll=lower_bound(y,y+t,l[i].y1)-y+1;
        int rr=lower_bound(y,y+t,l[i].y2)-y+1;
        query(ll,rr,l[i].flag,1);
        if(i)ans+=2*lines*(l[i].x-l[i-1].x);   //计算平行于x轴的长度
        ans+=abs(tree[1].len-last);            //计算平行于y轴的长度
        last=tree[1].len;
        lines=tree[1].num;
    }
    printf("%d\n",ans);
    return 0;
}

2.线段树求矩形面积并

#include<cstdio>
#include<algorithm>
#define N 20010
using namespace std;
typedef long long ll;

struct Tree{
    int l,r,cover[8];   //len表示区间【l,r】被占用的总长度
    ll len[8];
}tree[5*N];

struct Line{
    ll x,y1,y2;
    int flag,c;
}l[N];
ll y[N];

bool cmp(struct Line a,struct Line b){    //这里表示当2条线段x坐标重合时优先处理是入边的矩形的线段
    if(a.x==b.x)return a.flag>b.flag;
    return a.x<b.x;
}
void build(int s,int t,int id){
    int i;
    tree[id].l=s,tree[id].r=t;
    for(i=1;i<=7;i++)
        tree[id].cover[i]=tree[id].len[i]=0;
    if(s!=t-1){
        int mid=(s+t)>>1;
        build(s,mid,id<<1);
        build(mid,t,id<<1|1);
    }
}
void update(int id,int c){
    if(tree[id].cover[c]>0)
        tree[id].len[c]=y[tree[id].r-1]-y[tree[id].l-1];   //注意这里都要减一
    else if(tree[id].l==tree[id].r-1)
        tree[id].len[c]=0;
    else
        tree[id].len[c]=tree[id<<1].len[c]+tree[id<<1|1].len[c];
}
void query(int s,int t,int flag,int c,int id){
    if(tree[id].l==s && tree[id].r==t){
        tree[id].cover[c]+=flag;
        update(id,c);
        return;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(t<=mid)query(s,t,flag,c,id<<1);
    else if(s>=mid)query(s,t,flag,c,id<<1|1);
    else{
        query(s,mid,flag,c,id<<1);
        query(mid,t,flag,c,id<<1|1);
    }
    update(id,c);
}
int main(){
    int i,n,k;
    ll x1,x2,y1,y2;
    char str[10];
    int tt,T;
    scanf("%d",&T);
    for(tt=1;tt<=T;tt++){
        scanf("%d",&n);
        int cnt=0;
        for(i=1;i<=n;i++){
            scanf("%s %I64d %I64d %I64d %I64d",str,&x1,&y1,&x2,&y2);
            if(str[0]=='R') l[cnt].c=l[cnt+1].c=1;
            else if(str[0]=='G') l[cnt].c=l[cnt+1].c=2;
            else if(str[0]=='B') l[cnt].c=l[cnt+1].c=4;
            l[cnt].x=x1,l[cnt].y1=y1,l[cnt].y2=y2,l[cnt].flag=1,y[cnt++]=y1;
            l[cnt].x=x2,l[cnt].y1=y1,l[cnt].y2=y2,l[cnt].flag=-1,y[cnt++]=y2;
        }
        sort(y,y+cnt);
        sort(l,l+cnt,cmp);
        int t=unique(y,y+cnt)-y;
        build(1,t,1);

        ll ans[8]={0},last[8]={0};
        for(i=0;i<cnt;i++){
            int lll=lower_bound(y,y+t,l[i].y1)-y+1;
            int rr=lower_bound(y,y+t,l[i].y2)-y+1;
            for(k=1;k<8;k++){
                if((l[i].c & k)) query(lll,rr,l[i].flag,k,1);
                if(i)ans[k]+=(ll)last[k]*(l[i].x-l[i-1].x);
                last[k]=tree[1].len[k];
            }
        }
        /*for(i=0;i<cnt;i++){  //两种写法都可以
            int lll=lower_bound(y,y+t,l[i].y1)-y+1;
            int rr=lower_bound(y,y+t,l[i].y2)-y+1;
            for(k=1;k<8;k++){
                if((l[i].c & k)) query(lll,rr,l[i].flag,k,1);
                if(i+1<cnt)ans[k]+=(ll)tree[1].len[k]*(l[i+1].x-l[i].x);
            }
        }*/
        printf("Case %d:\n",tt);
        printf("%I64d\n",ans[7]-ans[6]);
        printf("%I64d\n",ans[7]-ans[5]);
        printf("%I64d\n",ans[7]-ans[3]);
        printf("%I64d\n",ans[5]+ans[6]-ans[4]-ans[7]);
        printf("%I64d\n",ans[3]+ans[6]-ans[2]-ans[7]);
        printf("%I64d\n",ans[5]+ans[3]-ans[1]-ans[7]);
        printf("%I64d\n",ans[1]+ans[2]+ans[4]-ans[3]-ans[5]-ans[6]+ans[7]);
    }
    return 0;
}

3.离线线段树（一段区间出现x个x的一共有多少个）

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define N 100100
using namespace std;
int val[N],a[N],num[N];

int head[N],cnt,tim;
struct Edge{
    int v,next;
}edge[N*2];
int dep[N],son[N];

struct Query{
    int x,y,id;
}query[N];

struct Tree{
    int l,r,val;
}tree[3*N];

vector<int>vec[N];
int ans[N];

void init(){
    memset(head,-1,sizeof(head));
    cnt=tim=0;
}
void addedge(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
    edge[cnt].v=u;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
void dfs(int u,int fa){
    int i;
    dep[u]=++tim,son[u]=1;
    num[tim]=val[u];
    for(i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        dfs(v,u);
        son[u]+=son[v];
    }
}

bool cmp(struct Query a,struct Query b){
    return a.y<b.y;
}

void build(int s,int t,int id){
    tree[id].l=s,tree[id].r=t,tree[id].val=0;
    if(s!=t){
        int mid=(s+t)>>1;
        build(s,mid,id<<1);
        build(mid+1,t,id<<1|1);
    }
}
void insert(int pos,int val,int id){
    if(tree[id].l==tree[id].r){
        tree[id].val=val;
        return ;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(mid>=pos)insert(pos,val,id<<1);
    else if(mid<pos)insert(pos,val,id<<1|1);
    tree[id].val=tree[id<<1].val+tree[id<<1|1].val;
}
int sea(int s,int t,int id){
    if(tree[id].l==tree[id].r)return tree[id].val;
    if(tree[id].l==s && tree[id].r==t)return tree[id].val;
    int mid=(tree[id].l+tree[id].r)>>1;
    if(mid>=t)return sea(s,t,id<<1);
    else if(mid<s)return sea(s,t,id<<1|1);
    else return sea(s,mid,id<<1)+sea(mid+1,t,id<<1|1);
}

int main(){
    int t,T,q;
    int n,k,kk;
    int i,j;
    int u,v;
    int tem;
    scanf("%d",&T);
    for(t=1;t<=T;t++){
        printf("Case #%d:\n",t);
        scanf("%d %d",&n,&k);
        //
        kk=0;
        for(i=1;i<=n;i++){
            scanf("%d",&val[i]);
            a[kk++]=val[i];
        }
        sort(a,a+kk);
        int nn=unique(a,a+kk)-a;
        //
        init();
        for(i=1;i<n;i++){
            scanf("%d %d",&u,&v);
            addedge(u,v);
        }
        dfs(1,0);
        //
        scanf("%d",&q);
        for(i=1;i<=q;i++){
            scanf("%d",&tem);
            query[i].x=dep[tem];
            query[i].y=dep[tem]+son[tem]-1;
            query[i].id=i;
        }
        sort(query+1,query+1+q,cmp);
        //
        build(1,tim,1);
        for(i=0;i<nn;i++)vec[i].clear();
        kk=1;
        for(i=1;i<=n;i++){
            int u=lower_bound(a,a+nn,num[i])-a;
            if(vec[u].size()<k){
                vec[u].push_back(i);
                if(vec[u].size()==k)
                    insert(vec[u][0],1,1);
            }
            else if(vec[u].size()>=k){
                vec[u].push_back(i);
                insert(vec[u][vec[u].size()-k-1],-1,1);
                insert(vec[u][vec[u].size()-k],1,1);
                if(vec[u].size()>k+1)
                    insert(vec[u][vec[u].size()-k-2],0,1);
            }
            while(kk<=q && query[kk].y==i){
                ans[query[kk].id]=sea(query[kk].x,query[kk].y,1);
                kk++;
            }
            if(kk==q+1)break;
        }
        for(i=1;i<=q;i++)printf("%d\n",ans[i]);
        if(t!=T)puts("");
    }
    return 0;
}

4.带更新的区间最长连续子段和（头和尾可连接）

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,q;
struct node{
    int l,r;
    int sum;
    int amax,amin;    //区间最大、小序列和
    int lmax,rmax;    //区间最左、右连续最大和
    int lmin,rmin;    //区间最左、右连续最小和
}tree[300000];
void build(int s,int t,int id){
    tree[id].l=s,tree[id].r=t;
    tree[id].sum=0;
    tree[id].amax=tree[id].lmax=tree[id].rmax=-1000000000;
    tree[id].amin=tree[id].lmin=tree[id].rmin= 1000000000;
    if(s!=t){
        int mid=(s+t)>>1;
        build(s,mid,id*2);
        build(mid+1,t,id*2+1);
    }
}
void updatelength(int id){
    tree[id].sum=tree[id*2].sum+tree[id*2+1].sum;
    tree[id].amax=max(max(tree[id*2].amax,tree[id*2+1].amax),tree[id*2].rmax+tree[id*2+1].lmax);
    tree[id].amin=min(min(tree[id*2].amin,tree[id*2+1].amin),tree[id*2].rmin+tree[id*2+1].lmin);
    tree[id].lmax=tree[id*2].lmax;
    tree[id].lmin=tree[id*2].lmin;
    tree[id].rmax=tree[id*2+1].rmax;
    tree[id].rmin=tree[id*2+1].rmin;

    if(tree[id*2].lmax<tree[id*2].sum+tree[id*2+1].lmax)         //注意在更新tree[id*2].lmax等这四个变量时有一些问题
        tree[id].lmax=tree[id*2].sum+tree[id*2+1].lmax;
    if(tree[id*2].lmin>tree[id*2].sum+tree[id*2+1].lmin)
        tree[id].lmin=tree[id*2].sum+tree[id*2+1].lmin;

    if(tree[id*2+1].rmax<tree[id*2+1].sum+tree[id*2].rmax)
        tree[id].rmax=tree[id*2+1].sum+tree[id*2].rmax;
    if(tree[id*2+1].rmin>tree[id*2+1].sum+tree[id*2].rmin)
        tree[id].rmin=tree[id*2+1].sum+tree[id*2].rmin;
}
void update(int s,int tem,int id){
    if(tree[id].l==tree[id].r){
        tree[id].sum=tem;
        tree[id].amax=tree[id].amin=tree[id].lmax=tree[id].lmin=tree[id].rmax=tree[id].rmin=tem;
        return ;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(mid>=s)
        update(s,tem,id*2);
    else
        update(s,tem,id*2+1);
    updatelength(id);
}
int main(){
    int i,j,pos,tem;
    scanf("%d",&n);
    build(1,n,1);
    for(i=1;i<=n;i++){
        scanf("%d",&tem);
        update(i,tem,1);
    }
    scanf("%d",&q);
    for(i=1;i<=q;i++){
        scanf("%d %d",&pos,&tem);
        update(pos,tem,1);
        if(tree[1].amax==tree[1].sum)
            printf("%d\n",tree[1].amax-tree[1].amin);
        else if(tree[1].amax>=tree[1].sum-tree[1].amin)          //考虑到环的性质，最左边的线段连接最右边的线段这种情况也可能产生最大值
            printf("%d\n",tree[1].amax);
        else if(tree[1].amax<tree[1].sum-tree[1].amin)          //但是此时最大值为环总和减去最小连续和，而不是tree[1].lmax+tree[1].rmax
            printf("%d\n",tree[1].sum-tree[1].amin);
    }
}

5.区间合并

#include <iostream>
#include <stdio.h>
using namespace std;

const int maxn = 50000 * 3;

struct Node
{
    int left, right;
    int stat;               // 0：区间全为0，1：区间全为1，2：区间有部分为0部分为1
    int lmax, rmax, amax;   // lmax：包含最左边元素最长0的长度，rmax：包含最右边元素最长0的长度
} tree[maxn];               // amax：区间中最长0的长度

void Build(int l, int r, int id)
{
    tree[id].left = l; tree[id].right = r;
    tree[id].stat = 0;
    tree[id].lmax = tree[id].rmax = tree[id].amax = r - l + 1;
    if (l == r) return;

    int m = (l + r) / 2;
    Build(l, m, id * 2);
    Build(m + 1, r, id * 2 + 1);
}

void UpdateStatus(int id)
{
    if (tree[id].stat == 2)
    {
        if (tree[id*2].stat == tree[id*2+1].stat && tree[id*2].stat != 2)
            tree[id].stat = tree[id*2].stat;
    }
}

void UpdateLength(int id)
{
    if (tree[id].stat == 0)
        tree[id].lmax = tree[id].rmax = tree[id].amax =tree[id].right - tree[id].left + 1;
    else if (tree[id].stat == 1)
        tree[id].lmax = tree[id].rmax = tree[id].amax = 0;
    else
    {
        tree[id].amax = max(max(tree[id*2].amax, tree[id*2+1].amax), tree[id*2].rmax + tree[id*2+1].lmax);
        tree[id].lmax = tree[id*2].lmax;
        tree[id].rmax = tree[id*2+1].rmax;
        if (tree[id*2].stat == 0)
            tree[id].lmax += tree[id*2+1].lmax;
        if (tree[id*2+1].stat == 0)
            tree[id].rmax += tree[id*2].rmax;
    }
}

void Update(int l, int r, int v, int id)    // v = 0：更新一段区间为0， v = 1：更新一段区间为1
{
    if (tree[id].stat == v)
        return;

    if (tree[id].left == l && tree[id].right == r)
    {
        tree[id].stat = v;
        UpdateLength(id);
        return;
    }
    if (tree[id].stat != 2)
    {
        tree[id*2].stat = tree[id*2+1].stat = tree[id].stat;
        tree[id].stat = 2;
        UpdateLength(id*2);
        UpdateLength(id*2+1);
    }
    int m = (tree[id].left + tree[id].right) / 2;
    if (r <= m)
        Update(l, r, v, id * 2);
    else if (l > m)
        Update(l , r, v, id * 2 + 1);
    else
        Update(l, m, v, id * 2), Update(m + 1, r, v, id * 2 + 1);
    UpdateStatus(id);
    UpdateLength(id);
}

int  Query(int len, int id)
{
    if (tree[id].stat == 0)
        return tree[id].left;
    if (tree[id*2].amax >= len)
        return Query(len, id * 2);
    else if (tree[id*2].rmax + tree[id*2+1].lmax >= len)
        return tree[id*2].right - tree[id*2].rmax + 1;
    else
        return Query(len, id * 2 + 1);
}

int main()
{
    int N, M;
    int cmd, len, x;

    scanf("%d %d", &N, &M);
    Build(1, N, 1);
    for (int i = 0; i < M; i++)
    {
        scanf("%d", &cmd);
        if (cmd == 1)
        {
            scanf("%d", &len);
            if (tree[1].amax < len)
                printf("0\n");
            else
            {
                x = Query(len, 1);
                Update(x, x + len - 1, 1, 1);
                printf("%d\n", x);
            }
        }
        else
        {
            scanf("%d %d", &x, &len);
            Update(x, x + len - 1, 0, 1);
        }
    }
    return 0;
}

6.优化DP
题意：1～n,每个点有点权，然后一个区间有收益，求最大收益。

dp[i]=max{dp[j]+w[j+1][i],dp[i-1]}，其中1=<i<=n,0=<j<=j-1;

dp[i]表示前i个项目的最大获利,w[j][i]表示项目j到i全部投资的获利。
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef long long ll;
int n,m;
int a[20010];
struct Item{
	int l,r;
	ll v;
}item[20010];
ll dp[20010],w[70010],p[70010];                     //用数组p[]标记需要向下压多少,数组w[]存最大值
int cmp(const void * a,const void * b){
	struct Item * aa=(struct Item * )a;
	struct Item * bb=(struct Item * )b;
	return aa->r-bb->r;
}
int max(int a,int b){
	return a>b?a:b;
}
void insert(int c,int l,int r,int a,int b,ll val){
	int mid;
	if(a==l && b==r){
		w[c]+=val;
		p[c]+=val;
		return;
	}
	if(p[c]!=0){
		w[2*c+1]+=p[c];
		p[2*c+1]+=p[c];
		w[2*c]+=p[c];
		p[2*c]+=p[c];
		p[c]=0;
	}
	mid=(l+r)>>1;
	if(a>mid)
		insert(c*2+1,mid+1,r,a,b,val);
	else if(b<=mid)
		insert(c*2,l,mid,a,b,val);
	else{
		insert(c*2,l,mid,a,mid,val);
		insert(c*2+1,mid+1,r,mid+1,b,val);
	}
	w[c]=max(w[2*c+1],w[2*c]);
}
ll query(int c,int l,int r,int a,int b){
	int mid;
	if(a==l && b==r)
		return w[c];
	if(p[c]!=0){
		w[2*c+1]+=p[c];
		p[2*c+1]+=p[c];
		w[2*c]+=p[c];
		p[2*c]+=p[c];
		p[c]=0;
	}
	mid=(l+r)>>1;
	if(a>mid)
		return query(c*2+1,mid+1,r,a,b);
	else if(b<=mid)
		return query(c*2,l,mid,a,b);
	else
		return max(query(c*2,l,mid,a,mid),query(c*2+1,mid+1,r,mid+1,b));
	w[c]=max(w[2*c+1],w[2*c]);
}
int main(){
	int i,j;
	while(scanf("%d %d",&n,&m)==2){
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(i=1;i<=m;i++)
			scanf("%d %d %lld",&item[i].l,&item[i].r,&item[i].v);
		qsort(&item[1],m,sizeof(item[1]),cmp);
		i=1;j=1;
		memset(dp,0,sizeof(dp));
		memset(w,0,sizeof(w));
		memset(p,0,sizeof(p));
		for(;i<=n;i++){
			insert(1,0,n,0,i-1,-a[i]); //这里不能在区间0,i内更新，因为i处存的是dp[i]
			while(j<=m && item[j].r<=i){
				insert(1,0,n,0,item[j].l-1,item[j].v);
				j++;
			}
			dp[i]=max(dp[i-1],query(1,0,n,0,i-1));            //dp[i]表示前i个项目的最大获利
			insert(1,0,n,i,i,dp[i]);  //线段树在i存入dp[i],即之前的最大值
		}
		printf("%lld\n",dp[n]);
	}
}

7.询问区间最大子段和（带修改）
#include<cstdio>
#include<algorithm>
using namespace std;
struct Tree{
    int l,r;
    int lm,rm,mm,sum;
}tree[200000];
int a[100010];
void build(int s,int t,int id){
    tree[id].l=s,tree[id].r=t;
    if(s==t)
        tree[id].lm=tree[id].mm=tree[id].rm=tree[id].sum=a[s];
    else{
        int mid=(tree[id].l+tree[id].r)>>1;
        build(s,mid,id<<1);
        build(mid+1,t,id<<1|1);
        tree[id].sum=tree[id<<1].sum+tree[id<<1|1].sum;
        tree[id].lm=max(tree[id<<1].sum+tree[id<<1|1].lm,tree[id<<1].lm);
        tree[id].rm=max(tree[id<<1].rm+tree[id<<1|1].sum,tree[id<<1|1].rm);
        tree[id].mm=max(max(tree[id<<1].mm,tree[id<<1|1].mm),tree[id<<1].rm+tree[id<<1|1].lm);
    }
}
void insert(int pos,int num,int id){
    if(tree[id].l==tree[id].r){
        tree[id].lm=tree[id].mm=tree[id].rm=tree[id].sum=num;
        return ;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(pos<=mid)insert(pos,num,id<<1);
    else insert(pos,num,id<<1|1);
    tree[id].sum=tree[id<<1].sum+tree[id<<1|1].sum;
    tree[id].lm=max(tree[id<<1].sum+tree[id<<1|1].lm,tree[id<<1].lm);
    tree[id].rm=max(tree[id<<1].rm+tree[id<<1|1].sum,tree[id<<1|1].rm);
    tree[id].mm=max(max(tree[id<<1].mm,tree[id<<1|1].mm),tree[id<<1].rm+tree[id<<1|1].lm);
}
struct Tree query(int s,int t,int id){
    struct Tree tem,tem1,tem2;
    if(tree[id].l==s && tree[id].r==t){
        tem.lm=tree[id].lm;
        tem.rm=tree[id].rm;
        tem.mm=tree[id].mm;
        tem.sum=tree[id].sum;
        return tem;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(mid>=t)return query(s,t,id<<1);
    else if(mid<s)return query(s,t,id<<1|1);
    else{
        tem1=query(s,mid,id<<1);
        tem2=query(mid+1,t,id<<1|1);
        tem.sum=tem1.sum+tem2.sum;
        tem.lm=max(tem1.sum+tem2.lm,tem1.lm);
        tem.rm=max(tem2.sum+tem1.rm,tem2.rm);
        tem.mm=max(max(tem1.mm,tem2.mm),tem1.rm+tem2.lm);
        return tem;
    }
}
int main(){
    int i,m,l,r,n,sel;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,n,1);
    scanf("%d",&m);
    for(i=1;i<=m;i++){
        scanf("%d",&sel);
        if(sel==1){
            scanf("%d%d",&l,&r);
            printf("%d\n",query(l,r,1).mm);
        }
        else{
            scanf("%d%d",&l,&r);
            insert(l,r,1);
        }
    }
    return 0;
}

