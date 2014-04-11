2013年四川省赛题目，AC自动机维护fail树
insert输入字符串，ask查询一个串有多少个字串出现了
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 1000100
using namespace std;

char S[N*2];//所以串读入S中
int n,str[N],type[N],mp[N];//记录读入串的最后一个位置下标，mp[i]表示第i个单词的自动机编号，
int pos;
int next[N][26],fail[N];

int newnode(){
    memset(next[pos],0,sizeof(next[pos]));
    fail[pos]=0;
    return pos++;
}

void insert(char * s,int id){
    int p=0,i=0;
    for(;s[i];i++){
        int k=s[i]-'a';
        p=next[p][k]?next[p][k]:next[p][k]=newnode();
    }
    mp[id]=p;
}

void makefail(){
    queue<int>q;
    q.push(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            int v=next[u][i];
            if(v==0) next[u][i]=next[fail[u]][i];
            else q.push(v);
            if(v && u)fail[v]=next[fail[u]][i];
        }
    }
}

struct Tree{
    int l,r;
    int add;
    int sum;
}tree[N<<2];

void build(int s,int t,int id){
    tree[id].l=s;
    tree[id].r=t;
    tree[id].add=tree[id].sum=0;
    if(s!=t){
        int mid=(s+t)>>1;
        build(s,mid,id<<1);
        build(mid+1,t,id<<1|1);
    }
}

void update(int s,int t,int add,int id){
    if(tree[id].l==s && tree[id].r==t){
        tree[id].add+=add;
        tree[id].sum+=add;
        return ;
    }
    if(tree[id].add!=0){
        tree[id<<1].add+=tree[id].add;
        tree[id<<1|1].add+=tree[id].add;
        tree[id<<1].sum+=tree[id].add;
        tree[id<<1|1].sum+=tree[id].add;
        tree[id].add=0;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(t<=mid) update(s,t,add,id<<1);
    else if(mid<s) update(s,t,add,id<<1|1);
    else{
        update(s,mid,add,id<<1);
        update(mid+1,t,add,id<<1|1);
    }
}

int query(int POS,int id){
    if(tree[id].l==tree[id].r){
        return tree[id].sum;
    }
    if(tree[id].add!=0){
        tree[id<<1].add+=tree[id].add;
        tree[id<<1|1].add+=tree[id].add;
        tree[id<<1].sum+=tree[id].add;
        tree[id<<1|1].sum+=tree[id].add;
        tree[id].add=0;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(POS<=mid) return query(POS,id<<1);
    else return query(POS,id<<1|1);
}

struct Edge{
    int v,next;
}edge[N*2];
int head[N],cnt;
int tim[N],son[N],dep;//tim[i]为自动机i个节点的dfs序

void init(){
    memset(head,-1,sizeof(head));
    cnt=dep=0;
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
    tim[u]=++dep;
    son[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        dfs(v,u);
        son[u]+=son[v];
    }
}

void build_failtree(){
    for(int i=1;i<pos;i++) addedge(fail[i],i);
    dfs(0,-1);
    build(1,pos,1);
}

void solve(){
	for(int i=1;i<=n;i++){
		if(type[i]==1){
			update(tim[mp[i]],tim[mp[i]]+son[mp[i]]-1,1,1);
		}
		else{
			int p=0;
			long long ans=0;
			for(int j=str[i-1]+1;j<=str[i];j++){
				p=next[p][S[j]-'a'];
				ans+=(long long)query(tim[p],1);
			}
			printf("%lld\n",ans);
		}
	}
}

int main(){
	int t,T;
    char ss[10];
    scanf("%d",&T);
    for(t=1;t<=T;t++){
		pos=0;newnode();
		str[0]=0;
		scanf("%d %d",&n);
		memset(mp,0,sizeof(mp));
		for(int i=1;i<=n;i++){
			scanf("%s %s",ss,&S[str[i-1]+1]);
			str[i]=str[i-1]+strlen(&S[str[i-1]+1]);
			if(!strcmp(ss,"ask")) type[i]=2;
			else type[i]=1;
			if(type[i]==1) insert(&S[str[i-1]+1],i);
		}
		makefail();
		init();
		build_failtree();
		solve();
    }
    return 0;
}
HDU 4117 按顺序输入n个串和权值，删去一些单词，剩余单词相邻之间前者为后者字串，求最大价值
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 300100
using namespace std;

char S[N];//所以串读入S中
int n,str[N],dp[N];//str[i]记录读入串的最后一个位置下标
int pos;
int next[N][26],fail[N];

int newnode(){
    memset(next[pos],0,sizeof(next[pos]));
    fail[pos]=0;
    return pos++;
}

void insert(char * s,int id){
    int p=0,i=0;
    for(;s[i];i++){
        int k=s[i]-'a';
        p=next[p][k]?next[p][k]:next[p][k]=newnode();
    }
}

void makefail(){
    queue<int>q;
    q.push(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            int v=next[u][i];
            if(v==0) next[u][i]=next[fail[u]][i];
            else q.push(v);
            if(v && u)fail[v]=next[fail[u]][i];
        }
    }
}

struct Tree{
    int l,r;
    int lazy;
    int MAX;
}tree[N<<2];

void build(int s,int t,int id){
    tree[id].l=s;
    tree[id].r=t;
    tree[id].MAX=tree[id].lazy=0;
    if(s!=t){
        int mid=(s+t)>>1;
        build(s,mid,id<<1);
        build(mid+1,t,id<<1|1);
    }
}

void update(int s,int t,int lazy,int id){
    //printf("%d %d %d\n",s,t,id);
    if(tree[id].l==s && tree[id].r==t){
        tree[id].lazy=max(tree[id].lazy,lazy);
        tree[id].MAX=max(tree[id].MAX,lazy);
        return ;
    }
    if(tree[id].lazy!=0){
        tree[id<<1].lazy=max(tree[id<<1].lazy,tree[id].lazy);
        tree[id<<1|1].lazy=max(tree[id<<1|1].lazy,tree[id].lazy);
        tree[id<<1].MAX=max(tree[id<<1].MAX,tree[id].lazy);
        tree[id<<1|1].MAX=max(tree[id<<1|1].MAX,tree[id].lazy);
        tree[id].lazy=0;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(t<=mid) update(s,t,lazy,id<<1);
    else if(mid<s) update(s,t,lazy,id<<1|1);
    else{
        update(s,mid,lazy,id<<1);
        update(mid+1,t,lazy,id<<1|1);
    }
}

int query(int POS,int id){
    if(tree[id].l==tree[id].r){
        return tree[id].MAX;
    }
    if(tree[id].lazy!=0){
        tree[id<<1].lazy=max(tree[id<<1].lazy,tree[id].lazy);
        tree[id<<1|1].lazy=max(tree[id<<1|1].lazy,tree[id].lazy);
        tree[id<<1].MAX=max(tree[id<<1].MAX,tree[id].lazy);
        tree[id<<1|1].MAX=max(tree[id<<1|1].MAX,tree[id].lazy);
        tree[id].lazy=0;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(POS<=mid) return query(POS,id<<1);
    else return query(POS,id<<1|1);
}

struct Edge{
    int v,next;
}edge[N*2];
int head[N],cnt;
int tim[N],son[N],dep;//tim[i]为自动机i个节点的dfs序

void init(){
    memset(head,-1,sizeof(head));
    cnt=dep=0;
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
    tim[u]=++dep;
    son[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==fa)continue;
        dfs(v,u);
        son[u]+=son[v];
    }
}

void build_failtree(){
    for(int i=1;i<pos;i++) addedge(fail[i],i);
    dfs(0,-1);
    build(1,pos,1);
}

void solve(){
    for(int i=1;i<=n;i++){
        if(dp[i]>0){
            int p=0,tem=0;
            for(int j=str[i-1]+1;j<=str[i];j++){
                p=next[p][S[j]-'a'];
                tem=max(tem,query(tim[p],1));
            }
            dp[i]+=tem;
            if(dp[i]>0) update(tim[p],tim[p]+son[p]-1,dp[i],1);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        pos=0;newnode();
        str[0]=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s %d",&S[str[i-1]+1],&dp[i]);
            str[i]=str[i-1]+strlen(&S[str[i-1]+1]);
            if(dp[i]>0)insert(&S[str[i-1]+1],i);
        }
        makefail();
        init();
        build_failtree();
        solve();
        int ans=0;
        for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
        printf("Case #%d: %d\n",t,ans);
    }
    return 0;
}

