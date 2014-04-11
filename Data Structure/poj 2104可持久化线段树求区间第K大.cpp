#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100100
using namespace std;

int tot,root[N];

struct Tree{
	int l,r;
	int ls,rs; //ls,rs保存左右子树的ID
	int sum;
}tree[N*25];

int build(int l,int r){
	int id=++tot;
	tree[id].l=l;
	tree[id].r=r;
	tree[id].sum=0;
	if(l==r) return id;
	int mid=(l+r)>>1;
	tree[id].ls=build(l,mid);
	tree[id].rs=build(mid+1,r);
	return id;
}

int insert(int ids,int pos){
	int id=++tot;
	tree[id]=tree[ids];
	tree[id].sum++;
	if(tree[id].l==tree[id].r) return id;
	int mid=(tree[id].l+tree[id].r)>>1;
	if(mid<pos) tree[id].rs=insert(tree[id].rs,pos);
	else tree[id].ls=insert(tree[id].ls,pos);
	return id;
}

int query(int ids,int sta,int k){
	if(tree[ids].l==tree[ids].r) return tree[ids].l;
	if(tree[tree[ids].ls].sum-tree[tree[sta].ls].sum>=k) return query(tree[ids].ls,tree[sta].ls,k);
	else return query(tree[ids].rs,tree[sta].rs,k-(tree[tree[ids].ls].sum-tree[tree[sta].ls].sum));
}

int main(){
	int n,m;
	int a[N],b[N];
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b,b+n);
	int nn=unique(b,b+n)-b;
	//printf("%d\n",nn);
	//for(int i=0;i<nn;i++) printf("%d ",b[i]);
	//puts("");
	tot=0;
	root[0]=build(1,nn);
	for(int i=0;i<n;i++){
		int tmp=lower_bound(b,b+nn,a[i])-b+1;
		//printf("%d %d\n",a[i],tmp);
		root[i+1]=insert(root[i],tmp);
	}
	for(int i=0;i<m;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		printf("%d\n",b[query(root[v],root[u-1],w)-1]);
	}
}
