#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define N 55
#define M 55*55
int U[M],D[M],L[M],R[M],C[M],X[M];//x代表M所属的行，c代表M所属的列，U，D，L，R为一个元素的上下左右指针
int H[N],S[N];//H是水平循环链表的头指针，S代表每一列的元素个数，Q存储一个可能结果
int size,n,m,k;
double city[N][2];
double radar[N][2];
double dis[N][N];       //dis[i][j]表示雷达i到cityj的距离
int mx[N][N];
bool vis[N];

void remove(int c)
{
    for(int i = D[c]; i != c; i = D[i])
        R[L[i]] = R[i], L[R[i]] = L[i];
}

void resume(int c)
{
    for(int i = D[c]; i != c; i = D[i])
        R[L[i]] = L[R[i]] = i;
}

int h()
{
    int i,j,c;
    memset(vis,0,sizeof(vis));
    int ans = 0;
    for(c = R[0] ; c ; c = R[c])
    {
        if(!vis[c])
        {
            ans++;
            for(i = D[c]; i != c; i = D[i])
                for(j = R[i]; j != i; j = R[j])
                    vis[C[j]] = true;
        }
    }
    return ans;
}

bool Dance(int dep)
{
	if(R[0] == 0)
        return true;
    if(dep + h() > k)       //A_Star剪枝
        return false;

    int i,j,tmp,c;

    for(tmp=100000,i=R[0]; i; i=R[i])
        if(S[i]<tmp)tmp=S[c=i];
    
    for(i=D[c]; i!=c; i=D[i])
    {
		remove(i);
        for(j=R[i]; j!=i; j=R[j])remove(j);
        if(Dance(dep+1))return 1;
        for(j=L[i]; j!=i; j=L[j])resume(j);//在这里我遵循的原则是先删除的后还原，后删除的先还原。
		resume(i);
    }

    return 0;
}
void Link(int r,int c)
{
    ++S[C[size]=c];
    D[size]=D[c];
    U[D[c]]=size;
    U[size]=c;
    D[c]=size;
    if(H[r]<0)H[r]=L[size]=R[size]=size;
    else
    {
        R[size]=R[H[r]];
        L[R[H[r]]]=size;
        L[size]=H[r];
        R[H[r]]=size;
    }
    X[size++]=r;
}

bool build(double mid){
	memset(mx,0,sizeof(mx));
	for(int i=1;i<=n;i++){
		int flag=0;
		for(int j=1;j<=m;j++){
			if(dis[j][i] - mid < 1e-8){
				mx[j][i] = 1;
				flag=1;
			}
		}
		if(!flag)
			return 0;
	}

	for(int i=0; i<=n; ++i)
    {
		S[i]=0;
		D[i]=U[i]=i;
		L[i+1]=i;
		R[i]=i+1;
    }
    R[n]=0;
	size=n+1;
	for(int i=1; i<=m; ++i)
		H[i]=-1;

	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(mx[i][j])
				Link(i,j);
		}
	}
	return 1;
}
bool OK(double mid)
{
    if(build(mid))
        return Dance(0);
    else
        return false;
}

double solve()
{
    double low = 0;
    double high = 1500;
    while(low+1e-8<high)
    {
        double mid = (low+high)/2.0;
        if(OK(mid))
            high = mid;
        else
            low = mid;
    }
    return high;
}
double Dis(int i, int j)
{
    return sqrt((double)(radar[i][0]-city[j][0])*(radar[i][0]-city[j][0])+(radar[i][1]-city[j][1])*(radar[i][1]-city[j][1]));
}

void Init()
{
    int i,j;
    for(i = 1; i <= m; i++)
        for(j = 1; j <= n; j++)
            dis[i][j] = Dis(i,j);
}
int main()
{
    int i,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d %d",&n,&m,&k);
        for(i = 1; i <= n; i++)
            scanf("%lf %lf",&city[i][0],&city[i][1]);
        for(i = 1; i <= m; i++)
            scanf("%lf %lf",&radar[i][0],&radar[i][1]);
        Init();
        printf("%.6lf\n",solve());
    }
    return 0;
}
