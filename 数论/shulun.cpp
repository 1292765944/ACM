#include <cstdio>
#include <cstring>
#include <cmath>
#define N 1010
using namespace std;

int c[N][N];
int vis[N];
int prime[N];

void init(){
	memset(c,0,sizeof(c));
	for(int i=0;i<=N-10;i++){
		c[i][0]=c[i][i]=1;
	}
	for(int i=0;i<=N-10;i++){
		for(int j=1;j<i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j]);
	}
}

int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}

void sieve(int n){
	memset(vis,0,sizeof(vis));
	int m=(int)sqrt(n+0.5);
	for(int i=2;i<=m;i++)if(!vis[i])
		for(int j=i*i;j<=n;j+=i) vis[j]=1;
}

int get_primes(int n){
	sieve(n);
	int c=0;
	for(int i=2;i<=n;i++)if(!vis[i])
		prime[c++]=i;
	return c;
}

void gcd(int a,int b,int &d,int &x,int &y){
	if(!b){
		d=a;
		x=1;
		y=0;
	}
	else{
		gcd(b,a%b,d,y,x);
		y-=x*(a/b);
	}
}

int main(){
	int u,v;
	init();

	/*while(scanf("%d %d",&u,&v)){
		printf("c[%d][%d]=%d\n",u,v,c[u][v]);
		printf("gcd(%d,%d)=%d\n",u,v,gcd(u,v));
	}*/

	/*int tot=get_primes(N-10);
	printf("%d\n",tot);
	for(int i=0;i<tot;i++) printf("%d ",prime[i]);*/

	/*int a,b,d,x,y;
	while(scanf("%d %d",&a,&b)){
		gcd(a,b,d,x,y);
		printf("(%d)*(%d)+(%d)*(%d)=%d\n",a,x,b,y,d);
	}*/

	return 0;
}

